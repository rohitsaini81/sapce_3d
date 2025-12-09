#ifndef PHYSICS_H
#define PHYSICS_H

#include "raylib.h"
#include <btBulletDynamicsCommon.h>
#include "level/level1/level.h"

// External declarations of Bullet components
extern btDiscreteDynamicsWorld* dynamicsWorld;
extern btBroadphaseInterface* broadphase;
extern btDefaultCollisionConfiguration* collisionConfiguration;
extern btCollisionDispatcher* dispatcher;
extern btSequentialImpulseConstraintSolver* solver;

// Box physics
extern btCollisionShape* boxShape;
extern btDefaultMotionState* boxMotion;
extern btRigidBody* boxBody;

// Ground physics
extern btCollisionShape* groundShape;
extern btDefaultMotionState* groundMotion;
extern btRigidBody* groundBody;

// player physics
extern btCollisionShape* playerShape;
extern btTransform startTransform;
extern btDefaultMotionState* motionState;
extern btRigidBody* playerBody;
// Simulation and rendering
void InitPhysics();
void UpdatePhysics(float deltaTime);
void CleanupPhysics();
void render(float deltaTime);
void testRayCast(Vector3 from, Vector3 to);
void DrawRayLine(Vector3 from, Vector3 to, Color color = RED);
// Player position tracking

extern Level* level1;





#endif

