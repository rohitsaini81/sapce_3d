#include "model_obj.h"
#include "raylib.h"

UModel::UModel(btDiscreteDynamicsWorld* dynamicsWorld, Model* mod,int type){
    shape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    motion = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundInfo(0.0f, motion, shape, btVector3(0, 0, 0));
    body = new btRigidBody(groundInfo);
    dynamicsWorld->addRigidBody(body);
    model=mod;
}
