#include "player.h"
#include "Controls/camera.h"
#include "ETC/global_var.h"
#include "raymath.h"
#include "raylib.h"
#include <bullet/LinearMath/btVector3.h>
#include <iostream>


PlayerModel::PlayerModel(btRigidBody* rigidBody, const Model& model)
    : rigibBodyofModel(rigidBody), onlyModel(model) {
            std::cout << "PlayerModel constructed!" << std::endl;

    }
#include "raymath.h" // for Vector3 and related functions

Vector3 PlayerModel::GetPosition() {
    if (!User || !User->rigibBodyofModel || !User->rigibBodyofModel->getMotionState()) {
        return {0, 0, 0}; // safe fallback
    }

    btTransform trans;
    User->rigibBodyofModel->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    return Vector3{pos.getX(), pos.getY(), pos.getZ()};  // ✅ correct conversion
}

PlayerModel* User;

void Player_Init(btDiscreteDynamicsWorld* world) {
    btCollisionShape* playerShape = nullptr;
    btTransform startTransform;
    btDefaultMotionState* motionState = nullptr;
    btRigidBody* playerBody = nullptr;

    btVector3 inertia(0, 0, 0);


    btScalar mass = 1.0f;
    btVector3 halfExtents(0.2f, 0.95f, 0.2f); // Approx. 1.9m height box
    playerShape = new btBoxShape(halfExtents);

    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(0, 5, 0)); // Starting position

    playerShape->calculateLocalInertia(mass, inertia);

    motionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, playerShape, inertia);
    playerBody = new btRigidBody(rbInfo);
    playerBody->setAngularFactor(btVector3(0, 1, 0));
    playerBody->setActivationState(DISABLE_DEACTIVATION);

    world->addRigidBody(playerBody);
const char* modelPath = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/rick/rick.glb";

    Model umodel = LoadModel(modelPath);
User = new PlayerModel(playerBody, umodel);
}

void Player_Update(float deltaTime) {
    if (!User || !User->rigibBodyofModel) return;
 
    if (!User->rigibBodyofModel || !User->rigibBodyofModel->getMotionState()) return;
    btTransform trans;
    User->rigibBodyofModel->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();


    if (User->rigibBodyofModel->getLinearVelocity()) {

        btVector3 vel(0, User->rigibBodyofModel->getLinearVelocity().getY(), 0);

        Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
        Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, {0, 1, 0}));
        forward.y = 0;
        right.y = 0;

        btVector3 moveDir(0, 0, 0);
// std::cout<<"player update\n";

        if (IsKeyDown(KEY_W)) {moveDir += btVector3(forward.x, 0, forward.z);}
        if (IsKeyDown(KEY_S)) {moveDir -= btVector3(forward.x, 0, forward.z);}
        if (IsKeyDown(KEY_D)) {moveDir += btVector3(right.x, 0, right.z);}
        if (IsKeyDown(KEY_A)){ moveDir -= btVector3(right.x, 0, right.z);}

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)){
            playerMoveSpeed = 50;
        }else{
            playerMoveSpeed = 10;}

        btVector3 currentVel = User->rigibBodyofModel->getLinearVelocity();
        if (moveDir.length2() > 0.0001f){
            moveDir = moveDir.normalized() * playerMoveSpeed;
        }else{
            moveDir = btVector3(0, 0, 0);}

        moveDir.setY(currentVel.getY());
        User->rigibBodyofModel->setLinearVelocity(moveDir);

        if (IsKeyPressed(KEY_SPACE)){ User->rigibBodyofModel->applyCentralImpulse(btVector3(0, 5, 0));}
    }
}

void Player_Render() {
if (!User || !User->rigibBodyofModel){ return;}


    if (!User->rigibBodyofModel || !User->rigibBodyofModel->getMotionState()) {return;}

    btTransform trans;
    User->rigibBodyofModel->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    Vector3 position = { pos.getX(), pos.getY(), pos.getZ() };
    // DrawCube({pos.getX(), pos.getY(), pos.getZ()}, 0.5f, 1.9f, 0.5f, GREEN);



    DrawModel(User->onlyModel,position , 1.0f, WHITE);
// std::cout << "Mesh count: " << User->onlyModel.meshCount << "\n";


}