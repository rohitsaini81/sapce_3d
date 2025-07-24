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
        Vector3 startPos = { btPos.getX(), btPos.getY(), btPos.getZ() };
        Vector3 endPos   = { btPos.getX() + halfHeight + 10.0f, btPos.getY(), btPos.getZ() };

        RayCastPerson(startPos, endPos);
    }

    // std::cout << "check this " << isPlayerAround << "\n";

    if (GetTypeName() == "Enemy") {
        static float memoryTime = 3.0f; // seconds to remember player
        static float memoryTimer = 0.0f;

        if (isPlayerAround == 1) {
            memoryTimer = memoryTime;  // Reset memory when player seen
        } else {
            memoryTimer -= deltaTime;
            if (memoryTimer < 0.0f) memoryTimer = 0.0f;
        }

        if (memoryTimer > 0.0f) {
            Vector3 toPlayer = {
                lastSeenPlayerPos.x - position.x,
                lastSeenPlayerPos.y - position.y,
                lastSeenPlayerPos.z - position.z
            };

            float length = sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y + toPlayer.z * toPlayer.z);
            if (length > 0.1f) {
                toPlayer.x /= length;
                toPlayer.y /= length;
                toPlayer.z /= length;
            }

            const float speed = 3.0f;
            btVector3 velocity(toPlayer.x * speed, 0, toPlayer.z * speed);
            body->setLinearVelocity(velocity);
        }else if(GetBodyPosition(body).x>1.0f){
Vector3 destination = {1.0f, 0.0f, 5.0f};
MoveToPosition(destination, deltaTime);


        }
         else {
            body->setLinearVelocity(btVector3(0, 0, 0));
        }
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


void Person::RayCastPerson(Vector3 origin, Vector3 /*unused*/) {
    isPlayerAround = 0;

    const int numRays = 100;
    const float visionAngle = 3.14159f; // 180 degrees
    const float maxDistance = 20.0f;

    auto castRaySet = [&](float baseAngleOffset) {
        for (int i = 0; i < numRays; ++i) {
            float angle = -visionAngle / 2 + (visionAngle * i / (numRays - 1));
            angle += baseAngleOffset; // offset for direction

            float dx = cos(angle);
            float dz = sin(angle);
            float distance = maxDistance * (0.5f + 0.5f * fabs(dz)); // shorter in center, longer on sides

            Vector3 end = {
                origin.x + dx * distance,
                origin.y,
                origin.z + dz * distance
            };

            btCollisionWorld::ClosestRayResultCallback rayCallback(
                btVector3(origin.x, origin.y, origin.z),
                btVector3(end.x, end.y, end.z)
            );

            dynamicsWorld->rayTest(
                btVector3(origin.x, origin.y, origin.z),
                btVector3(end.x, end.y, end.z),
                rayCallback
            );

            DrawRayLine(origin, end); // for debugging

            if (rayCallback.hasHit()) {
                btCollisionObject* hitObject = const_cast<btCollisionObject*>(rayCallback.m_collisionObject);
                // if (hitObject == playerBody) {
                //     isPlayerAround = 1;
                //     lastSeenPlayerPos = { end.x, end.y, end.z };
                //     return;
                // }
            }
        }
    };

    // 🔄 Cast forward
    castRaySet(0.0f);

    // 🔄 Cast backward (add 180° offset)
    // if (!isPlayerAround) {
    //     castRaySet(3.14159f); // 180° in radians
    // }
}

void Person::MoveToPosition(Vector3 targetPos, float deltaTime) {
    Vector3 toTarget = {
        targetPos.x - position.x,
        0.0f,
        targetPos.z - position.z
    };

    float distSq = toTarget.x * toTarget.x + toTarget.z * toTarget.z;

    const float stopDistance = 0.2f; // How close is "close enough"
    if (distSq < stopDistance * stopDistance) {
        // Close enough, stop
        body->setLinearVelocity(btVector3(0, 0, 0));
        return;
    }

    // Normalize direction
    float length = sqrt(distSq);
    toTarget.x /= length;
    toTarget.z /= length;

    const float speed = 3.0f;
    btVector3 velocity(toTarget.x * speed, 0, toTarget.z * speed);
    body->setLinearVelocity(velocity);
}


Vector3 Person::GetBodyPosition(btRigidBody* body) {
    if (!body) return {0.0f, 0.0f, 0.0f};

    btTransform trans;
    body->getMotionState()->getWorldTransform(trans);
    btVector3 origin = trans.getOrigin();

    return { origin.getX(), origin.getY(), origin.getZ() };
}
