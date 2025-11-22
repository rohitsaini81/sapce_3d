#include "elements.h"
#include "vector"
#include "LinearMath/btAlignedObjectArray.h"
#include "time.h"
#include "raylib.h"
#include "Models.h"

MyModel::MyModel(btRigidBody* rigidBody, const Model& model)
    : rigibBodyofModel(rigidBody), onlyModel(model) {
            std::cout << "MyModel constructed!" << std::endl;
    }

std::vector<MyModel> models;
