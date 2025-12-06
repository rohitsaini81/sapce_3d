#include "camera.h"
#include "raylib.h"
#include "raymath.h"
#include "../ETC/global_var.h"
#include "iostream"
#include "player.h"
Camera camera = {0};
float pitch = 15.0f;  // Slightly looking down
float cameraDistance = 10.0f;
void CAM_INIT(){
        // Camera setup
        camera.projection = CAMERA_PERSPECTIVE;
        camera.up = {0.0f, 1.0f, 0.0f};
        camera.fovy = 45.0f;
       DisableCursor(); // Hide and lock cursor

}


float cameraYaw = 0.0f;
float cameraPitch = 0.0f;
const float mouseSensitivity = 0.003f;
Vector2 mouseDelta = GetMouseDelta();
void UPDATE_CAMERA(){

// Mouse movement
Vector2 mouseDelta = GetMouseDelta();
yaw -= mouseDelta.x * 0.1f;
pitch -= mouseDelta.y * 0.1f;

// Clamp pitch to avoid flipping

if (pitch <=22.0f) pitch =22.0f;
if (pitch >=80.0f) pitch = 80.0f;
// std::cout<<"pitch"<<pitch<<std::endl;
// Convert spherical coordinates to cartesian
Vector3 cameraOffset;
cameraOffset.x = cameraDistance * cosf(DEG2RAD * pitch) * sinf(DEG2RAD * yaw);
cameraOffset.y = cameraDistance * sinf(DEG2RAD * pitch);
cameraOffset.z = cameraDistance * cosf(DEG2RAD * pitch) * cosf(DEG2RAD * yaw);



// Update camera to follow player from behind and above
        // Vector3 cameraOffset = {-5.0f, 4.0f, 5.0f}; // Offset behind and above
        camera.position = Vector3Add(PlayerModel::GetPosition(), cameraOffset);
        camera.target = PlayerModel::GetPosition();
        // std::cout<<PlayerModel::GetPosition;
        // std::cout<<"player position"<<std::endl;

camera.up = { 0.0f, 1.0f, 0.0f };
SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);



}
