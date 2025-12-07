#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>

class Controller {
public:
    Controller();

    // Update controller logic
    void update(float dt);

    // Render / debug print
    void render() const;

private:
    float playerX;
    float playerY;
    float playerZ;
};

#endif // CONTROLLER_H
