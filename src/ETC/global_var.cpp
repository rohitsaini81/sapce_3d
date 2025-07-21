#include "global_var.h"
#include <iostream>
#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactShape.h>
#include "raylib.h"
const std::string project_dir = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/";
float yaw = 0.0f;
Vector3 playerPos = {0.0f, 0.0f, 0.0f};
float playerMoveSpeed=20.0f;
Model plane = {0};

Color g_scriptColor = {0};

void INIT_BEFORE (){
    Color g_scriptColor = {255, 0, 0, 255};
    std::cout<<"path"<<project_dir;
    plane = LoadModel((project_dir+"src/assets/cube.glb").c_str());
    if (plane.meshCount == 0) {std::cerr << "Failed to load plane model!" << std::endl;}

}

btBvhTriangleMeshShape* CreateStaticCollisionShapeFromModel(const Model& model)
{
    btTriangleMesh* triangleMesh = new btTriangleMesh();

    for (int m = 0; m < model.meshCount; ++m)
    {
        Mesh mesh = model.meshes[m];
        float* vertices = mesh.vertices; // 3 floats per vertex
        unsigned short* indices = mesh.indices; // 3 indices per triangle

        for (int i = 0; i < mesh.triangleCount; ++i)
        {
            int index0 = indices[i * 3 + 0];
            int index1 = indices[i * 3 + 1];
            int index2 = indices[i * 3 + 2];

            btVector3 v0(vertices[index0 * 3], vertices[index0 * 3 + 1], vertices[index0 * 3 + 2]);
            btVector3 v1(vertices[index1 * 3], vertices[index1 * 3 + 1], vertices[index1 * 3 + 2]);
            btVector3 v2(vertices[index2 * 3], vertices[index2 * 3 + 1], vertices[index2 * 3 + 2]);

            triangleMesh->addTriangle(v0, v1, v2);
        }
    }

    btBvhTriangleMeshShape* staticShape = new btBvhTriangleMeshShape(triangleMesh, true);
    return staticShape;
}

