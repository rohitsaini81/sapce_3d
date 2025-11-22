#include "physics.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "3dObjects/objects.h"
#include "Controls/camera.h"
#include "ETC/global_var.h"
#include <iostream>
#include <string>
<<<<<<< HEAD
#include "global_var.h"
#include "camera.h"
#include "objects.h"
=======

#include "iostream"
>>>>>>> main
#include "raylib.h"
#include <atomic>
#include <chrono>
#include <thread>

extern "C" {
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"
}
#include "script/script.h"
#include <filesystem>

#include "player.h"
#include "related/file.h"
// #include "imgui.h"
// #include "rlImGui.h"

void LoadResources(std::atomic<bool>& loadingDone) {
    // INIT_BEFORE();
    // InitPhysics();
    // CAM_INIT();
    // Player_Init(dynamicsWorld);


<<<<<<< HEAD



void LoadResources(std::atomic<bool>& loadingDone) {
    // INIT_BEFORE();
    // InitPhysics();
    // CAM_INIT();
    // Player_Init(dynamicsWorld);


    loadingDone = true;
}



int main() {





   



    // Initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(800, 600, "Rick and Morty Baby");
    INIT_BEFORE();
    InitPhysics();
    CAM_INIT();
    Player_Init(dynamicsWorld);
        //--->
const std::string scriptPath = project_dir+"src/script/config.lua";
const std::string Path= "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/";
const char* modelPath = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/rick/rick.glb";
    Model model = LoadModel(modelPath);
 
    int animCount = 0;
    ModelAnimation* anims = LoadModelAnimations(modelPath, &animCount);
    float animFrameCounter = 0.0f;


    // Player state
    Vector3 planePos = {2.0f, 0.0f, 2.0f};


    SetTargetFPS(60);
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
    std::atomic<bool> loadingDone = false;
=======
}
int main() {
    // Initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT); // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(1080, 700, "Rick and Morty Baby");
    SetTargetFPS(60);
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);



        std::atomic<bool> loadingDone = false;
>>>>>>> main
    std::thread loadingThread(LoadResources, std::ref(loadingDone));
    int dotCounter = 0;
    float timer = 0.0f;
    bool open = false;
<<<<<<< HEAD
=======
    std::string loadingText = "Loading";

            BeginDrawing();
            ClearBackground(RAYWHITE);
            loadingText += ".";
            DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);
            EndDrawing();


>>>>>>> main


   INIT_BEFORE();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    loadingText += ".";
    DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);
    EndDrawing();

    InitPhysics();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    loadingText += ".";
    DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);
    EndDrawing();

    CAM_INIT();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    loadingText += ".";
    DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);
    EndDrawing();

    Player_Init(dynamicsWorld);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    loadingText += ".";
    DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);
    EndDrawing();
    std::string path = getExecutableDir();

    //--->
    std::string assetsDir = pathJoin(getExecutableDir(), "assets");
    std::string scriptDir = pathJoin(getExecutableDir(), "script");
    const std::string modelPath = assetsDir+"/rick/rick.glb";
    // if (plane.meshCount == 0) {
    //     std::cerr << "Failed to load plane model!" << std::endl;
    // }
    Model model = LoadModel(modelPath.c_str());
    // int animCount = 0;
    // ModelAnimation* anims = LoadModelAnimations(modelPath, &animCount);
    // float animFrameCounter = 0.0f;


    /***************************Lua script loading****************************/
    // Lua is here
    const std::string scriptPath = scriptDir+ "/config.lua";
    std::cout<<scriptPath;
    lua_State* L = luaL_newstate();
    // luaL_openlibs(L);
    luaL_dostring(L, "print('Hello from Lua 5.1.5')");
    run_lua_script(scriptPath.c_str());
    load_config(scriptPath.c_str());
    time_t lastModified = getFileLastModifiedTime(scriptPath);


    // end lua here
    /*********************************************************************/


/*
    while (!WindowShouldClose()) {
        if (!loadingDone) {
            // Animate the dots (e.g. "Loading.", "Loading..", "Loading...")
            timer += GetFrameTime();
            if (timer >= 0.5f) {
                dotCounter = (dotCounter + 1) % 4; // Cycle through 0 to 3
                timer = 0.0f;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            std::string loadingText = "Loading";
            for (int i = 0; i < dotCounter; ++i) loadingText += ".";

            DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);

            EndDrawing();
        }
        else {
            // Done loading, break and show your actual scene
            break;
        }
    }
*/
    // Make sure thread has finished
    if (loadingThread.joinable()) loadingThread.join();





 while (!WindowShouldClose()) {
        if (!loadingDone) {
            // Animate the dots (e.g. "Loading.", "Loading..", "Loading...")
            timer += GetFrameTime();
            if (timer >= 0.5f) {
                dotCounter = (dotCounter + 1) % 4; // Cycle through 0 to 3
                timer = 0.0f;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            std::string loadingText = "Loading";
            for (int i = 0; i < dotCounter; ++i) loadingText += ".";

            DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);

            EndDrawing();
        }
        else {
            // Done loading, break and show your actual scene
            break;
        }
    }
    if (loadingThread.joinable()) loadingThread.join();





    while (!WindowShouldClose()) {
        time_t currentModified = getFileLastModifiedTime(scriptPath);
        if (currentModified != lastModified) {
            lastModified = currentModified;
            std::cout << "Reloading Lua script..." << std::endl;
            if (!elementList.empty()) {
                for (int i = 0; i < elementList.size(); i++) {
                    elementList[i]->destroy(dynamicsWorld);
                }
                elementList.clear();
            }
            run_lua_script(scriptPath.c_str());
            load_config(scriptPath.c_str());
        }

        float delta = GetFrameTime();
<<<<<<< HEAD
        UpdatePhysics(delta);
 
    
=======

>>>>>>> main

        // Handle animation
        //--->
        // if (animCount > 0) {
        //     animFrameCounter += 1.0f;
        //     if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
        //     UpdateModelAnimation(model, anims[0], (int)animFrameCounter);
        // }





            UPDATE_CAMERA();



        if (IsKeyPressed(KEY_X)) {
            open = !open;
            if (open) {
                EnableCursor(); // Show and unlock the mouse for ImGui
            }
            else {
                DisableCursor(); // Hide and lock the mouse for game control
            }
            std::cout << "Toggled ImGui window: " << (open ? "OPEN" : "CLOSED") << std::endl;
        }
<<<<<<< HEAD
//        std::cout<<"what";

        // Update camera to follow player from behind and above
        Vector3 cameraOffset = {-5.0f, 4.0f, 5.0f}; // Offset behind and above
        camera.position = Vector3Add(PlayerModel::GetPosition(), cameraOffset);
        camera.target = PlayerModel::GetPosition();




    UPDATE_CAMERA();



=======
>>>>>>> main


        // Render
        BeginDrawing();
        ClearBackground(BLACK);
        // ClearBackground(RAYWHITE);
        BeginMode3D(camera);
<<<<<<< HEAD
        DrawCube({ 0.0f, 0.0f, 0.0f }, 20.0f, 0.1f, 20.0f, WHITE);
        
        DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
=======
>>>>>>> main

        // DrawCube({0.0f, 0.0f, 0.0f}, 20.0f, 0.1f, 20.0f, WHITE);

<<<<<<< HEAD
        // DrawModel(model, playerPos, 1.0f, WHITE);
=======
        DrawPlane(Vector3Zero(), (Vector2){10.0, 10.0}, WHITE);
        Player_Update(delta);
        Player_Render();
>>>>>>> main

        // DrawModel(model,{0,0,0},1.0f,WHITE);

<<<<<<< HEAD
      Player_Update(delta);
      Player_Render();




        


        playerPos = PlayerModel::GetPosition();



        // DrawModelEx(plane, planePos, {1.0f, 0.0f, 0.0f}, -90.0f, {1.0f, 1.0f, 1.0f}, WHITE);
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Use WASD to move, SPACE to jump", 10, 10, 20, DARKGRAY);





bool open=true;



EndDrawing();














=======




        render(delta);

        EndMode3D();

        DrawText("SPACE ENGINE / RICK AND MORTY GM", 10, 10, 20, DARKGRAY);
        EndDrawing();
>>>>>>> main
    }


    // Cleanup
<<<<<<< HEAD
        //--->
    if (animCount > 0) UnloadModelAnimations(anims, animCount);
    UnloadModel(model);
    // UnloadModel(plane);
=======
    //--->
    // if (animCount > 0) UnloadModelAnimations(anims, animCount);
>>>>>>> main
    CleanupPhysics();
    CloseWindow();

    return 0;
}
