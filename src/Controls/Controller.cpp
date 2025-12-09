#include "Controller.h"
#include <iostream>

Controller::Controller()
    : playerX(0.0f), playerY(0.0f), playerZ(0.0f)
{
    std::cout << "Controller initialized.\n";
}

void Controller::update(float dt)
{
    // Example movement logic
    playerX += 0.1f * dt;
    playerY += 0.0f;
    playerZ += 0.0f;
}

void Controller::render() const
{
    // std::cout << "Player Position: "
    //           << "(" << playerX << ", " 
    //           << playerY << ", " 
    //           << playerZ << ")\n";
}
