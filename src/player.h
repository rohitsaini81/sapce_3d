#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <btBulletDynamicsCommon.h>


struct PlayerModel {
    btRigidBody* rigibBodyofModel;
    // btCollisionShape* playerShape;
// btTransform startTransform;
    // btDefaultMotionState* motionState;
    Model onlyModel;
    static Vector3 GetPosition();
    PlayerModel(btRigidBody* rigidBody, const Model& model);  // constructor declared
};

// Initialization and update
void Player_Init(btDiscreteDynamicsWorld* world);
void Player_Update(float deltaTime);
void Player_Render();

extern PlayerModel* User;






class Player
{
public:
    Player(btDiscreteDynamicsWorld* world, const Model& model, const Vector3& startPos);
    ~Player();

    void Update(float deltaTime);
    void Render();

    Vector3 GetPosition() const;
    btRigidBody* GetRigidBody() const { return rigidBody; }

private:
    btDiscreteDynamicsWorld* world;
    btRigidBody* rigidBody;
    btCollisionShape* shape;
    btDefaultMotionState* motionState;

    Model model;

    float modelHeight;
    void CalculateBoundingBoxHeight();
};



#endif
