#include "person.h"
#include <iostream>
#include "physics.h"
// Bullet mass for dynamic body
static const float PERSON_MASS = 1.0f;

Person::Person(Vector3 pos, PersonType t) : position(pos), type(t) {
    InitPhysics(pos);
}

Person::~Person() {
    CleanupPhysics();
}

void Person::InitPhysics(Vector3 pos) {
    // Create a simple capsule shape or box shape for the character
    shape = new btCapsuleShape(0.3f, 1.2f); // radius, height
    isPlayerAround=0;

    // Set Bullet transform
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(pos.x, pos.y, pos.z));

    motionState = new btDefaultMotionState(startTransform);

    btVector3 inertia(0, 0, 0);
    shape->calculateLocalInertia(PERSON_MASS, inertia);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(PERSON_MASS, motionState, shape, inertia);
    body = new btRigidBody(rbInfo);

    // Optional: make the body not rotate (like a character controller)
    body->setAngularFactor(0);
          body->setActivationState(DISABLE_DEACTIVATION);
    

    // Note: You must add `body` to the Bullet dynamics world externally!
}

void Person::CleanupPhysics() {
    if (body) {
        delete body;
        body = nullptr;
    }

    if (motionState) {
        delete motionState;
        motionState = nullptr;
    }

    if (shape) {
        delete shape;
        shape = nullptr;
    }
}

void Person::Update(float deltaTime) {
    // Sync position from physics body
    if (body) {
        btTransform trans;
        body->getMotionState()->getWorldTransform(trans);
        btVector3 btPos = trans.getOrigin();
        position = { (float)btPos.getX(), (float)btPos.getY(), (float)btPos.getZ() };

        float capsuleVisualHeight = 1.5f + 2 * 0.2f; // total 1.9
        float halfHeight = capsuleVisualHeight / 1.0f;
        Vector3 startPos = { btPos.getX(), btPos.getY() , btPos.getZ() };
        Vector3 endPos   = { btPos.getX() + halfHeight+10.0f, btPos.getY() , btPos.getZ() };

        RayCastPerson(startPos, endPos);

                    



    }

    std::cout<<"check this "<<isPlayerAround<<"\n";
    if(Person::GetTypeName()=="Enemy"){
        // std::cout<<"enemy is ahead\n";
        




if (isPlayerAround == 1) {
    Vector3 toPlayer = {
        lastSeenPlayerPos.x - position.x,
        lastSeenPlayerPos.y - position.y,
        lastSeenPlayerPos.z - position.z
    };

    // Normalize direction
    float length = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y + toPlayer.z * toPlayer.z);
    if (length > 0.1f) {
        toPlayer.x /= length;
        toPlayer.y /= length;
        toPlayer.z /= length;
    }

    // Set velocity toward player
    const float speed = 3.0f;
    btVector3 velocity(toPlayer.x * speed, 0, toPlayer.z * speed);
    body->setLinearVelocity(velocity);
} else {
    body->setLinearVelocity(btVector3(0, 0, 0));
}





// AI or behavior logic could go here

    }

}

void Person::Render() const {
    Color color;

    switch (type) {
        case PersonType::ENEMY: color = RED; break;
        case PersonType::ALLY: color = GREEN; break;
        case PersonType::NEUTRAL: color = BLUE; break;
    }

    // Draw as a capsule or cylinder (fake capsule with two spheres)
    DrawCylinder(position, 0.3f, 0.3f, 1.2f, 12, color);
    DrawSphere({ position.x, position.y + 0.6f, position.z }, 0.3f, color);
    DrawSphere({ position.x, position.y - 0.6f, position.z }, 0.3f, color);
    float detectionRadius = 1.0f;





}

Vector3 Person::GetPosition() const {
    return position;
}

void Person::SetPosition(Vector3 pos) {
    position = pos;
    if (body) {
        btTransform trans;
        trans.setIdentity();
        trans.setOrigin(btVector3(pos.x, pos.y, pos.z));
        body->setWorldTransform(trans);
        body->getMotionState()->setWorldTransform(trans);
    }
}

btRigidBody* Person::GetRigidBody() {
    return body;
}

PersonType Person::GetType() const {
    return type;
}

std::string Person::GetTypeName() const {
    switch (type) {
        case PersonType::ENEMY: return "Enemy";
        case PersonType::ALLY: return "Ally";
        case PersonType::NEUTRAL: return "Neutral";
        default: return "Unknown";
    }
}


void Person::RayCastPerson(Vector3 from, Vector3 to){
    isPlayerAround = 0;

    for(float i=0.0f; i<50; i++) {
        Vector3 end = { to.x, to.y , to.z + i / 2 };
        btCollisionWorld::ClosestRayResultCallback rayCallback1(
            btVector3(from.x, from.y, from.z),
            btVector3(end.x, end.y, end.z)
        );

        dynamicsWorld->rayTest(btVector3(from.x, from.y, from.z), btVector3(end.x, end.y, end.z), rayCallback1);

        if (rayCallback1.hasHit()) {
            btCollisionObject* hitObject1 = const_cast<btCollisionObject*>(rayCallback1.m_collisionObject);
            if (hitObject1 == playerBody) {
                isPlayerAround = 1;
                lastSeenPlayerPos = { end.x, end.y, end.z }; // remember where the player is
                DrawRayLine(from, end);
                return;
            }
        }

        DrawRayLine(from, end);
    }
}
