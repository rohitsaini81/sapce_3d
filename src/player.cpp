#include "player.h"
#include "Controls/camera.h"
#include <iostream>
#include "raymath.h"
#include "ETC/global_var.h"
#include <raylib.h>

// Global instance definition

void Player_Init(btDiscreteDynamicsWorld* world) {
    const char* modelPath = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/rick/rick.glb";

    // player->shape = new btBoxShape(btVector3(0.2f, 0.95f, 0.2f));
    // player->transform.setIdentity();
    // player->transform.setOrigin(btVector3(0, 5, 0));
    // player->shape->calculateLocalInertia(1.0f, player->inertia);

    // player->motionState = new btDefaultMotionState(player->transform);

    // btRigidBody::btRigidBodyConstructionInfo rbInfo(
    //     1.0f, player->motionState, player->shape, player->inertia);

    // player->body = new btRigidBody(rbInfo);
    // player->body->setAngularFactor(btVector3(0, 1, 0));
    // player->body->setActivationState(DISABLE_DEACTIVATION);

    // world->addRigidBody(player->body);
}

// void Player_Update(float deltaTime) {
//     if (!UPLAYER || !UPLAYER->body || !UPLAYER->body->getMotionState()) return;

//     btTransform trans;
//     UPLAYER->body->getMotionState()->getWorldTransform(trans);
//     btVector3 pos = trans.getOrigin();

//     UPLAYER->setPosition(pos.getX(), pos.getY(), pos.getZ());

//     if (UPLAYER->body->getLinearVelocity()) {
//         btVector3 vel(0, UPLAYER->body->getLinearVelocity().getY(), 0);

//         Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
//         Vector3 right = Vector3Normalize(Vector3CrossProduct(forward, { 0, 1, 0 }));
//         forward.y = 0;
//         right.y = 0;

//         btVector3 moveDir(0, 0, 0);

//         if (IsKeyDown(KEY_W)) moveDir += btVector3(forward.x, 0, forward.z);
//         if (IsKeyDown(KEY_S)) moveDir -= btVector3(forward.x, 0, forward.z);
//         if (IsKeyDown(KEY_D)) moveDir += btVector3(right.x, 0, right.z);
//         if (IsKeyDown(KEY_A)) moveDir -= btVector3(right.x, 0, right.z);

//         if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
//             playerMoveSpeed = 50;
//         else
//             playerMoveSpeed = 20;

//         btVector3 currentVel = UPLAYER->body->getLinearVelocity();
//         if (moveDir.length2() > 0.0001f)
//             moveDir = moveDir.normalized() * playerMoveSpeed;
//         else
//             moveDir = btVector3(0, 0, 0);

//         moveDir.setY(currentVel.getY());
//         UPLAYER->body->setLinearVelocity(moveDir);

//         if (IsKeyPressed(KEY_SPACE))
//             UPLAYER->body->applyCentralImpulse(btVector3(0, 5, 0));
//     }
// }

// void Player_Render() {
//     if (UPLAYER->model.meshCount == 0) {
//     std::cerr << "Failed to load model: " <<  "\n";
// }

//     if (!UPLAYER || !UPLAYER->body || !UPLAYER->body->getMotionState()) return;

//     btTransform trans;
//     UPLAYER->body->getMotionState()->getWorldTransform(trans);
//     btVector3 pos = trans.getOrigin();
//         // DrawModel(model, playerPos, 1.0f, WHITE);

//         DrawModel(UPLAYER->model, { pos.getX(), pos.getY(), pos.getZ() }, 5.0f, WHITE); // scale 5.0f
// DrawCube({ pos.getX(), pos.getY(), pos.getZ() }, 0.5f, 1.9f, 0.5f, GREEN);

//     DrawModel(UPLAYER->model, { pos.getX(), pos.getY(), pos.getZ() }, 1.0f, WHITE);
//     // Alternatively, use a debug box:
//     DrawCube({ pos.getX(), pos.getY(), pos.getZ() }, 0.5f, 1.9f, 0.5f, GREEN);
// }
