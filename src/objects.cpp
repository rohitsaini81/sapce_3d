// objects.cpp
#include "objects.h"
#include "physics.h" // make sure dynamicsWorld is visible
#include "iostream"
#include "elements.h" 
#include "LinearMath/btAlignedObjectArray.h" 
#include "global_var.h"
#include "Models.h"
Elements* objectal[4]; // array of pointers
// std::vector<Elements> elementList;
std::vector<Elements*> elementList;
std::vector<btRigidBody*> rigidBodyList;
btAlignedObjectArray<btRigidBody*> rigidBodies;
btRigidBody* TerrainRegidBody;


void Init_Elems(){
   try{ 
    // Model levelModel = LoadModel("assets/american_road_intersection.glb");
    Model levelModel = LoadModel((project_dir+"src/assets/american_road_intersection.glb").c_str());

    if (levelModel.meshCount == 0) {
    std::cerr << "Warning: Loaded model has no meshes." << std::endl;
    return;
}
btCollisionShape* shape = CreateStaticCollisionShapeFromModel(levelModel);

// Create rigid body
btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1), btVector3(0,0,0)));

btRigidBody::btRigidBodyConstructionInfo rbInfo(0, motionState, shape, btVector3(0, 0, 0));
TerrainRegidBody = new btRigidBody(rbInfo);

if (shape && motionState && TerrainRegidBody) {
    dynamicsWorld->addRigidBody(TerrainRegidBody);
    // MyModel obj(TerrainRegidBody, levelModel);
    models.emplace_back(TerrainRegidBody, levelModel);
}   
}
catch (const std::exception& e) {
    std::cerr << "Error in Init_Elems(): " << e.what() << std::endl;
}
}

void CREATE_ELEM() {
    try {
        if (dynamicsWorld) {
            std::cout << "fine working ?? " << std::endl;
            Elements* newElem = new Elements(ElementType::BOX, dynamicsWorld, nullptr);
            std::cout << "Note------------------------" << newElem->mass << std::endl;
            std::cout << "dynamicsWorld ptr: " << dynamicsWorld << std::endl;
            std::cout << "newElem.body ptr: " << newElem->body << std::endl;

            if (dynamicsWorld && newElem->body) {
                std::cout << "About to add rigid body\n";
                dynamicsWorld->addRigidBody(newElem->body);
                elementList.push_back(newElem);
                // rigidBodies.push_back(newElem->body);


        

                // objectal[0]=newElem;
                // rigidBodyList.push_back(newElem->body);
                // elementList.push_back(newElem);
                
                
                
                // objectal[0] = new Elements(ElementType::BOX, dynamicsWorld);                std::cout << "Rigid body added\n";
            } else {
                std::cerr << "Invalid world or body\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught unknown exception" << std::endl;
    }
}





Color GetRandomColor()
{
    return (Color){
        (unsigned char)(rand() % 256),  // R
        (unsigned char)(rand() % 256),  // G
        (unsigned char)(rand() % 256),  // B
        255                             // A (fully opaque)
    };
}


