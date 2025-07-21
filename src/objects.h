#ifndef OBJECTS
#define OBJECTS
#include "elements.h"
#include "vector"
#include "LinearMath/btAlignedObjectArray.h"
#include "time.h"
#include "raylib.h"



void Init_Elems();
void CREATE_ELEM();

extern Elements* objectal[4];
// extern std::vector<Elements> elementList;

extern std::vector<Elements*> elementList;
extern std::vector<btRigidBody*> rigidBodyList;
extern btAlignedObjectArray<btRigidBody*> rigidBodies;
extern btRigidBody* TerrainRegidBody;

extern Color GetRandomColor();
std::vector<btRigidBody*> FindObjectsInRange(btDynamicsWorld* world, btVector3 center, float radius);
#endif