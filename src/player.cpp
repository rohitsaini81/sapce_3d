#include "player.h"
#include "Controls/camera.h"
#include <iostream>
#include "raymath.h"
#include "ETC/global_var.h"
// Player position
float playerX = 0.0f;
float playerY = 0.0f;
float playerZ = 0.0f;

// Bullet physics player components
btCollisionShape* playerShape = nullptr;
btTransform startTransform;
btDefaultMotionState* motionState = nullptr;
btRigidBody* playerBody = nullptr;

btVector3 inertia(0, 0, 0);

void setPlayerX(float X) { playerX = X; }
void setPlayerY(float Y) { playerY = Y; }
void setPlayerZ(float Z) { playerZ = Z; }
float getPlayerX() { return playerX; }
float getPlayerY() { return playerY; }
float getPlayerZ() { return playerZ; }

void Player_Init(btDiscreteDynamicsWorld* world) {
    btScalar mass = 1.0f;
    btVector3 halfExtents(0.2f, 0.95f, 0.2f);  // Approx. 1.9m height box
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
}

void Player_Update(float deltaTime) {
    if (!playerBody || !playerBody->getMotionState()) return;

    btTransform trans;
    playerBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    setPlayerX(pos.getX());
    setPlayerY(pos.getY());
    setPlayerZ(pos.getZ());

    if (playerBody->getLinearVelocity()) {
        btVector3 vel(0, playerBody->getLinearVelocity().getY(), 0);

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
            playerMoveSpeed = 10;

        btVector3 currentVel = playerBody->getLinearVelocity();
        if (moveDir.length2() > 0.0001f)
            moveDir = moveDir.normalized() * playerMoveSpeed;
        else
            moveDir = btVector3(0, 0, 0);

        moveDir.setY(currentVel.getY());
        playerBody->setLinearVelocity(moveDir);

        if (IsKeyPressed(KEY_SPACE))
            playerBody->applyCentralImpulse(btVector3(0, 5, 0));
    }
}

void Player_Render() {
    if (!playerBody || !playerBody->getMotionState()) return;

    btTransform trans;
    playerBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();

    DrawCube({ pos.getX(), pos.getY(), pos.getZ() }, 0.5f, 1.9f, 0.5f, GREEN);
}
