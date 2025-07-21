#ifndef MODEL_OBJ
#define MODEL_OBJ



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
    Model* model;
    btVector3 inertia;
    btVector3 ModelPosition;


    UModel(btDiscreteDynamicsWorld* dynamicsWorld, Model* mod,int type);
    void Update(float delta);
    void render(float delta);
    void setPosition(btVector3 position);
    void setMass(float weight);
    void destroy(btDiscreteDynamicsWorld* dynamicsWorld);

};


#endif