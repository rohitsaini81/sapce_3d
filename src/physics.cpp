#include "physics.h"
#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "../ETC/global_var.h"
#include "Controls/camera.h"
#include "../3dObjects/objects.h"
#include "script.h"
#include <lua.h>
#include "../NPC/person.h"
#include "../3dObjects/Models.h"


// Bullet globals
btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
btBroadphaseInterface* broadphase = nullptr;
btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
btCollisionDispatcher* dispatcher = nullptr;
btSequentialImpulseConstraintSolver* solver = nullptr;

// Physics objects
btCollisionShape* groundShape = nullptr;
btDefaultMotionState* groundMotion = nullptr;
btRigidBody* groundBody = nullptr;

btCollisionShape* boxShape = nullptr;
btDefaultMotionState* boxMotion = nullptr;
btRigidBody* boxBody = nullptr;

Level* level1 = nullptr;




// Person* PersonA =nullptr;
void InitPhysics() {
    // Bullet physics world setup
    broadphase = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);
    solver = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));

    // Ground setup
    groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    groundMotion = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundInfo(0.0f, groundMotion, groundShape, btVector3(0, 0, 0));
    groundBody = new btRigidBody(groundInfo);
    dynamicsWorld->addRigidBody(groundBody);

    // Box setup
    boxShape = new btBoxShape(btVector3(1, 1, 1));
    boxMotion = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
    btScalar boxmass = 80.0f;
    btVector3 inertia(0, 0, 0);
    boxShape->calculateLocalInertia(boxmass, inertia);
    btRigidBody::btRigidBodyConstructionInfo boxInfo(boxmass, boxMotion, boxShape, inertia);
    boxBody = new btRigidBody(boxInfo);
    dynamicsWorld->addRigidBody(boxBody);



// for(int i =0;i<5;i++){
//     CREATE_ELEM();

// }
// PersonA = new Person({getPlayerX(),getPlayerY(),getPlayerY()},PersonType::ENEMY);

// dynamicsWorld->addRigidBody(PersonA->body);
// rigidBodies.push_back(PersonA->body);

Init_Elems();

level1 = new Level(dynamicsWorld);


}


void UpdatePhysics(float deltaTime) {
    if (dynamicsWorld) {
        dynamicsWorld->stepSimulation(deltaTime);
        level1->Update(deltaTime);
    }
}

void CleanupPhysics() {
    delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;

    delete groundShape;
    delete groundMotion;
    delete groundBody;

    delete boxShape;
    delete boxMotion;
    delete boxBody;
}


void DrawRayLine(Vector3 from, Vector3 to, Color color){
    DrawLine3D(from, to, color);
}


void testRayCast(Vector3 from, Vector3 to)
{
    // Vector3 from = { x, 1.0f, 0.0f }; // Ray start
    // Vector3 to = { 0.0f, 1.0f, 10.0f };  // Ray end

    DrawRayLine(from, to);

    btCollisionWorld::ClosestRayResultCallback rayCallback(
        btVector3(from.x, from.y, from.z),
        btVector3(to.x, to.y, to.z)
    );

    dynamicsWorld->rayTest(btVector3(from.x, from.y, from.z), btVector3(to.x, to.y, to.z), rayCallback);

    if (rayCallback.hasHit()) {
        btVector3 hitPoint = rayCallback.m_hitPointWorld;
        std::cout << "Hit at: "
                  << hitPoint.getX() << ", "
                  << hitPoint.getY() << ", "
                  << hitPoint.getZ() << std::endl;
    } else {
        std::cout << "No hit detected.\n";
    }

    // if (rayCallback.hasHit()) {
    //     btCollisionObject* hitObject = const_cast<btCollisionObject*>(rayCallback.m_collisionObject);
    
    //     // Example: check if it's your box
    //     if (hitObject == boxBody) {
    //         std::cout << "Hit the box!\n";
    //     } else if (hitObject == playerBody) {
    //         std::cout << "Hit the player (yourself).\n";
    //     } else if (hitObject == PersonA->body) {
    //         std::cout << "Hit PersonA.\n";
    //     } else if (hitObject == groundBody) {
    //         std::cout << "Hit Ground surface.\n";
    //     }else {
    //         std::cout << "Hit unknown object.\n";
    //     }
    // }
    



}




        Color randomColor = GetRandomColor();


    void render(float deltaTime) {
    if (dynamicsWorld) {
        dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);
    }


    // PersonA->Update(deltaTime);
    // PersonA->Render();
    level1->Render();



    for (const MyModel& obj : models) {
    btTransform trans;
    obj.rigibBodyofModel->getMotionState()->getWorldTransform(trans);
    Vector3 pos = {
        trans.getOrigin().getX(),
        trans.getOrigin().getY(),
        trans.getOrigin().getZ()
    };

    DrawModel(obj.onlyModel, pos, 1.0f, WHITE);
    }


   for(int i=0;i<elementList.size();i++){
        btTransform trans;
        btRigidBody* body = elementList[i]->body;
        if (body->getMotionState()) {
            body->getMotionState()->getWorldTransform(trans);
        } else {
            trans = body->getCenterOfMassTransform();
        }
    
        btVector3 pos = trans.getOrigin();

    
if (elementList[i] && elementList[i]->model) {
    DrawModel(*elementList[i]->model, {pos.getX(), pos.getY(), pos.getZ()}, 1.0f, WHITE);
} else {
    DrawCube({pos.getX(), pos.getY(), pos.getZ()}, 2.0f, 2.0f, 2.0f, randomColor);
    // std::cerr << "Warning: element or model is null at index " << i << std::endl;
}



   }
   if (boxBody!=nullptr && boxBody->getMotionState() !=nullptr) {
    btTransform trans;
    boxBody->getMotionState()->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    DrawCube({pos.getX(), pos.getY(), pos.getZ()}, 2.0f, 2.0f, 2.0f, BLUE);

//   std::cout<<"rendering physics 1: " << getPlayerX() << std::endl;
}
    else {
        std::cerr << "[ERROR] boxBody or its motion state is null!" << std::endl;
    }



    // if (IsKeyPressed(KEY_R)) {
    //     LUA_Update();
    // }            DrawRectangle(200, 150, 400, 300, g_scriptColor);



    }
