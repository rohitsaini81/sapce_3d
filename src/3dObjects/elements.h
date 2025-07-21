// elements.h
#pragma once

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include "raylib.h"
enum class ElementType {
    BOX,
    CUBE
};


extern btVector3 inertia;





class Elements {
public:
    btCollisionShape* shape = nullptr;
    btDefaultMotionState* motion = nullptr;
    btRigidBody* body = nullptr;
    float mass = 1.0f;
    std::string object_name;
    Model* model;

    Elements(ElementType type, btDiscreteDynamicsWorld* dynamicsWorld, Model* Umodel);
    void destroy(btDiscreteDynamicsWorld* dynamicsWorld);
};
