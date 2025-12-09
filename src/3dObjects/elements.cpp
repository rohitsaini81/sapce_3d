// elements.cpp
#include "elements.h"
#include "iostream"
#include "cstring"


Elements::Elements(ElementType type, btDiscreteDynamicsWorld* dynamicsWorld, Model* Umodel) {
    std::cout << "---------------------------------------\n";
    object_name = "testing 1";
    btVector3 inertia = btVector3(0, 0, 0);
    this->model = Umodel;
    if (type == ElementType::BOX) {
        std::cout << "Creating BOX" << std::endl;
        shape = new btBoxShape(btVector3(1, 1, 1));
        mass = 50.0f;
    } else if (type == ElementType::CUBE) {
        std::cout << "Creating BOX" << std::endl;
        shape = new btCapsuleShape(0.3f, 1.2f); // radius, height
        mass = 45.0f;  
    }

    motion = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    shape->calculateLocalInertia(mass, inertia);

    btRigidBody::btRigidBodyConstructionInfo info(mass, motion, shape, inertia);
    body = new btRigidBody(info);
}

void Elements::destroy(btDiscreteDynamicsWorld* dynamicsWorld) {
    if (body) {
        dynamicsWorld->removeRigidBody(body);

        delete body->getMotionState();  // delete motion state
        delete body;
        delete shape;

        body = nullptr;
        shape = nullptr;
    }
}

