#ifndef MODELS
#define MODELS
#include "elements.h"
#include "vector"
#include "LinearMath/btAlignedObjectArray.h"
#include "time.h"
#include "raylib.h"



struct MyModel {
    btRigidBody* rigibBodyofModel;
    Model onlyModel;

    MyModel(btRigidBody* rigidBody, const Model& model);  // constructor declared
};


extern std::vector<MyModel> models;



#endif