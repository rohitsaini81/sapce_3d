#include "level/level1/level.h"
#include <cmath>
#include <cstring>
#include <stdexcept>
// #include <iostream>

Level::Level(btDiscreteDynamicsWorld* world)
    : dynamicsWorld(world)
{
}

Level::~Level()
{
    Unload();
}

void Level::Load()
{
    AddGround({0.0f, -1.0f, 0.0f}, {50.0f, 1.0f, 50.0f});
    AddBox({0.0f, 2.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
    AddBox({2.0f, 4.0f, 0.0f}, {0.6f, 0.6f, 0.6f});
}

void Level::Update(float dt)
{
    for (auto &o : objects) {
        if (!o.body) continue;
        btTransform trans;
        o.body->getMotionState()->getWorldTransform(trans);
        o.modelTransform = BtTransformToMatrix(trans);
    }
}

void Level::Render()
{
    // std::cout<<"rendering"<<std::endl;
    for (auto &o : objects) {
        if (!o.modelLoaded) continue;

        Matrix &m = o.modelTransform;
        Vector3 pos = { m.m12, m.m13, m.m14 };

        float m00 = m.m0, m01 = m.m4, m02 = m.m8;
        float m10 = m.m1, m11 = m.m5, m12 = m.m9;
        float m20 = m.m2, m21 = m.m6, m22 = m.m10;

        float trace = m00 + m11 + m22;
        float qw, qx, qy, qz;
        if (trace > 0.0f) {
            float s = sqrtf(trace + 1.0f) * 2.0f;
            qw = 0.25f * s;
            qx = (m21 - m12) / s;
            qy = (m02 - m20) / s;
            qz = (m10 - m01) / s;
        } else if ((m00 > m11) && (m00 > m22)) {
            float s = sqrtf(1.0f + m00 - m11 - m22) * 2.0f;
            qw = (m21 - m12) / s;
            qx = 0.25f * s;
            qy = (m01 + m10) / s;
            qz = (m02 + m20) / s;
        } else if (m11 > m22) {
            float s = sqrtf(1.0f + m11 - m00 - m22) * 2.0f;
            qw = (m02 - m20) / s;
            qx = (m01 + m10) / s;
            qy = 0.25f * s;
            qz = (m12 + m21) / s;
        } else {
            float s = sqrtf(1.0f + m22 - m00 - m11) * 2.0f;
            qw = (m10 - m01) / s;
            qx = (m02 + m20) / s;
            qy = (m12 + m21) / s;
            qz = 0.25f * s;
        }

        float qlen = sqrtf(qw*qw + qx*qx + qy*qy + qz*qz);
        if (qlen < 1e-6f) { qw = 1; qx = qy = qz = 0; qlen = 1.0f; }
        qw /= qlen; qx /= qlen; qy /= qlen; qz /= qlen;

        float angle = 2.0f * acosf(qw) * (180.0f/PI);
        float sinHalf = sqrtf(1.0f - qw*qw);

        Vector3 axis = {1,0,0};
        if (sinHalf > 0.0001f) {
            axis.x = qx / sinHalf;
            axis.y = qy / sinHalf;
            axis.z = qz / sinHalf;
        }

        float scale = o.modelScale.x;
        DrawModelEx(o.model, pos, axis, angle, {scale, scale, scale}, WHITE);
    }

  
}

void Level::Unload()
{
    for (auto &o : objects) {
        if (o.body && dynamicsWorld) dynamicsWorld->removeRigidBody(o.body);
        delete o.body;
        delete o.motion;
        delete o.shape;
        if (o.modelLoaded) UnloadModel(o.model);
    }
    objects.clear();
}

void Level::AddBox(const Vector3 &pos, const Vector3 &size, const std::string &modelPath)
{
    PhysObject o;

    btVector3 half(size.x*0.5f, size.y*0.5f, size.z*0.5f);
    o.shape = new btBoxShape(half);

    btTransform t;
    t.setIdentity();
    t.setOrigin({pos.x, pos.y, pos.z});

    btScalar mass = 1.0f;
    btVector3 inertia(0,0,0);
    o.shape->calculateLocalInertia(mass, inertia);

    o.motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass, o.motion, o.shape, inertia);
    o.body = new btRigidBody(info);

    dynamicsWorld->addRigidBody(o.body);

    if (!modelPath.empty()) {
        o.model = LoadModel(modelPath.c_str());
        o.modelLoaded = true;
    } else {
        Mesh cube = GenMeshCube(size.x, size.y, size.z);
        o.model = LoadModelFromMesh(cube);
        o.modelLoaded = true;
    }

    o.modelTransform = BtTransformToMatrix(t);
    objects.push_back(o);
}

void Level::AddGround(const Vector3 &pos, const Vector3 &size, const std::string &modelPath)
{
    PhysObject o;

    btVector3 half(size.x*0.5f, size.y*0.5f, size.z*0.5f);
    o.shape = new btBoxShape(half);

    btTransform t;
    t.setIdentity();
    t.setOrigin({pos.x, pos.y, pos.z});

    btScalar mass = 0.0f;
    btVector3 inertia(0,0,0);

    o.motion = new btDefaultMotionState(t);
    btRigidBody::btRigidBodyConstructionInfo info(mass, o.motion, o.shape, inertia);
    o.body = new btRigidBody(info);

    dynamicsWorld->addRigidBody(o.body);

    if (!modelPath.empty()) {
        o.model = LoadModel(modelPath.c_str());
        o.modelLoaded = true;
    } else {
        Mesh cube = GenMeshCube(size.x, size.y, size.z);
        o.model = LoadModelFromMesh(cube);
        o.modelLoaded = true;
    }

    o.modelTransform = BtTransformToMatrix(t);
    objects.push_back(o);
}

Matrix Level::BtTransformToMatrix(const btTransform &t)
{
    Matrix m = MatrixIdentity();

    btQuaternion q = t.getRotation();
    btVector3 o = t.getOrigin();

    float x = q.getX(), y = q.getY(), z = q.getZ(), w = q.getW();
    float xx = x*x, yy = y*y, zz = z*z;
    float xy = x*y, xz = x*z, yz = y*z;
    float wx = w*x, wy = w*y, wz = w*z;

    m.m0 = 1 - 2*(yy + zz);
    m.m1 = 2*(xy + wz);
    m.m2 = 2*(xz - wy);
    m.m3 = 0;

    m.m4 = 2*(xy - wz);
    m.m5 = 1 - 2*(xx + zz);
    m.m6 = 2*(yz + wx);
    m.m7 = 0;

    m.m8  = 2*(xz + wy);
    m.m9  = 2*(yz - wx);
    m.m10 = 1 - 2*(xx + yy);
    m.m11 = 0;

    m.m12 = o.getX();
    m.m13 = o.getY();
    m.m14 = o.getZ();
    m.m15 = 1;

    return m;
}
