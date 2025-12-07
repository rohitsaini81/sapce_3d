#ifndef GLOBAL_VAR
#define GLOBAL_VAR

#include <string>
#include "raylib.h"
#include <btBulletDynamicsCommon.h>
#include "Controls/Controller.h"

extern std::string project_dir;
extern float yaw;
extern float minPitch,maxPitch;

extern Controller* control;
extern Model plane;
extern Vector3 playerPos;
extern float playerMoveSpeed;
extern void INIT_BEFORE();
// global_var.h
extern Color g_scriptColor;
extern float health;
    
btBvhTriangleMeshShape* CreateStaticCollisionShapeFromModel(const Model& model);


#endif

