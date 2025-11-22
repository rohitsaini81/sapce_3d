#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <bullet/btBulletDynamicsCommon.h>


struct PlayerModel {
    btRigidBody* rigibBodyofModel;
    // btCollisionShape* playerShape;
<<<<<<< HEAD
    // btTransform startTransform;
=======
// btTransform startTransform;
>>>>>>> main
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

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> main
