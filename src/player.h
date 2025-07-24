#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <memory>

struct PLAYER {
    Model model;

    btRigidBody* body = nullptr;
    btCollisionShape* shape = nullptr;
    btTransform transform;
    btDefaultMotionState* motionState = nullptr;
    btVector3 inertia;

    float x = 0.0f, y = 0.0f, z = 0.0f;

    // Direct loading constructor
    PLAYER(const char* modelPath)
        : model(LoadModel(modelPath)), inertia(0, 0, 0) {}




};


void Player_Init(btDiscreteDynamicsWorld* world);
void Player_Update(float deltaTime);
void Player_Render();

#endif // PLAYER_H
