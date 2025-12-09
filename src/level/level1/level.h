#ifndef LEVEL_H
#define LEVEL_H

#include "raylib.h"
#include <btBulletDynamicsCommon.h>
#include <vector>
#include <string>

struct Player;

class Level {
public:
    Level(btDiscreteDynamicsWorld* world, Player* player = nullptr);
    ~Level();

    void Load();
    void Update(float dt);
    void Render();
    void Unload();

    void AddBox(const Vector3 &pos, const Vector3 &size, const std::string &modelPath = "");
    void AddGround(const Vector3 &pos, const Vector3 &size, const std::string &modelPath = "");

private:
    btDiscreteDynamicsWorld* dynamicsWorld;
    Player* player;

    struct PhysObject {
        btCollisionShape* shape = nullptr;
        btDefaultMotionState* motion = nullptr;
        btRigidBody* body = nullptr;
        Model model;
        bool modelLoaded = false;
        Vector3 modelScale = {1,1,1};
        Matrix modelTransform = MatrixIdentity();
    };

    std::vector<PhysObject> objects;

    static Matrix BtTransformToMatrix(const btTransform &t);
};

#endif
