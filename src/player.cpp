#include "player.h"
#include "Controls/camera.h"
#include <cstddef>
#include <iostream>
#include "raymath.h"
#include "ETC/global_var.h"
#include <bullet/BulletDynamics/Dynamics/btRigidBody.h>
#include <raylib.h>

// Global instance definition
MyModel1* user;
Model tempModel1;

void Player_Init(btDiscreteDynamicsWorld* world) {
    const char* modelPath = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/rick/rick.glb";

    btCollisionShape* shape = new btBoxShape(btVector3(0.2f, 0.95f, 0.2f));
    btTransform transform;
    btVector3 inertia;

    transform.setIdentity();
    transform.setOrigin(btVector3(0, 5, 0));
    shape->calculateLocalInertia(1.0f,inertia);
    btDefaultMotionState* motionState =  new btDefaultMotionState(transform);;


    btRigidBody::btRigidBodyConstructionInfo rbInfo(
        1.0f, motionState, shape,inertia);

    btRigidBody* body = new btRigidBody(rbInfo);
    body->setAngularFactor(btVector3(0, 1, 0));
    body->setActivationState(DISABLE_DEACTIVATION);

    world->addRigidBody(body);





Model levelModel = LoadModel(modelPath);
tempModel1 = LoadModel(modelPath);

if (levelModel.meshCount == 0) {
    std::cerr << "Warning: Loaded model has no meshes." << std::endl;
    return;
}

// ✅ This should not be inside the `if`
user = new MyModel1(body, levelModel);

}

void Player_Update(float deltaTime) {
    if (!user || !user->playerBody || !user->playerBody->getMotionState()) return;

    btTransform trans;
    user->playerBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();


    if (user->playerBody->getLinearVelocity()) {
        btVector3 vel(0, user->playerBody->getLinearVelocity().getY(), 0);

        Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, { 0, 1, 0 }));
        forward.y = 0;
        right.y = 0;

        btVector3 moveDir(0, 0, 0);

        if (IsKeyDown(KEY_W)) moveDir += btVector3(forward.x, 0, forward.z);
        if (IsKeyDown(KEY_S)) moveDir -= btVector3(forward.x, 0, forward.z);
        if (IsKeyDown(KEY_D)) moveDir += btVector3(right.x, 0, right.z);
        if (IsKeyDown(KEY_A)) moveDir -= btVector3(right.x, 0, right.z);

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            playerMoveSpeed = 50;
        else
            playerMoveSpeed = 20;

        btVector3 currentVel = user->playerBody->getLinearVelocity();
        if (moveDir.length2() > 0.0001f)
            moveDir = moveDir.normalized() * playerMoveSpeed;
        else
            moveDir = btVector3(0, 0, 0);

        moveDir.setY(currentVel.getY());
        user->playerBody->setLinearVelocity(moveDir);

        if (IsKeyPressed(KEY_SPACE))
            user->playerBody->applyCentralImpulse(btVector3(0, 5, 0));
    }
}

void Player_Render() {
 

    if (!user || !user->playerBody || !user->playerBody->getMotionState()) return;

    btTransform trans;
    user->playerBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    DrawCube({ pos.getX(), pos.getY(), pos.getZ() }, 0.5f, 1.9f, 0.5f, GREEN);
        DrawModel(user->onlyModel, { pos.getX(), pos.getY(), pos.getZ() }, 5.0f, WHITE); // scale 5.0f


    }




MyModel1::MyModel1(btRigidBody* rigidBody, const Model& model)
    : playerBody(rigidBody), onlyModel(model) {
            std::cout << "MyModel constructed!" << std::endl;
    }
