#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <bullet/btBulletDynamicsCommon.h>
#include <cstddef>
#include <memory>



struct MyModel1 {
    btRigidBody* playerBody = nullptr;
    Model onlyModel;


    MyModel1(btRigidBody* rigidBody, const Model& model);  // constructor declared
};
extern MyModel1* user;
extern Model tempModel1;
void Player_Init(btDiscreteDynamicsWorld* world);
void Player_Update(float deltaTime);
void Player_Render();

#endif // PLAYER_H
