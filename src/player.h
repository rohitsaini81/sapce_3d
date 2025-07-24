#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <bullet/btBulletDynamicsCommon.h>

// Player physics components
extern btCollisionShape* playerShape;
extern btTransform startTransform;
extern btDefaultMotionState* motionState;
extern btRigidBody* playerBody;

// Position tracking
extern float playerX;
extern float playerY;
extern float playerZ;

// External access to player position
float getPlayerX();
float getPlayerY();
float getPlayerZ();

void setPlayerX(float X);
void setPlayerY(float Y);
void setPlayerZ(float Z);

// Initialization and update
void Player_Init(btDiscreteDynamicsWorld* world);
void Player_Update(float deltaTime);
void Player_Render();

#endif
