#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include <btBulletDynamicsCommon.h>

class Player
{
public:
    Player(btDiscreteDynamicsWorld* world, const std::string& modelPath, const Vector3& startPos);
    ~Player();

    void Update(float deltaTime);
    void Render();

    Vector3 GetPosition() const;
    btRigidBody* GetBody() const { return body; }

private:
    void CreatePhysicsBody(const Vector3& startPos);
    void SyncRotation();
    void CalculateModelHeight();

private:
    btDiscreteDynamicsWorld* world;

    btRigidBody* body;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;

    Model model;

    float modelHeight = 0.0f;
};


extern Player* player;

#endif

