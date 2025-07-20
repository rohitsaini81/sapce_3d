#ifdef
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "raylib.h"

struct UModel {

    btCollisionShape* shape = nullptr;
    btDefaultMotionState* motion = nullptr;
    btRigidBody* body = nullptr;
    float mass = 1.0f;
    std::string model_path;
    Model model;
    btVector3 inertia;


    UModel(btDiscreteDynamicsWorld* dynamicsWorld, const char* modelPath);
    Update(float delta);
    void destroy(btDiscreteDynamicsWorld* dynamicsWorld);

};


#endif