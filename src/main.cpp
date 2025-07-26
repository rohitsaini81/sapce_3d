#include "physics.h"
#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "global_var.h"
#include "camera.h"
#include "objects.h"
#include "raylib.h"
#include <atomic>
#include <chrono>
#include <thread>

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include "script/script.h"
#include <filesystem>






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
    std::thread loadingThread(LoadResources, std::ref(loadingDone));
    int dotCounter = 0;
    float timer = 0.0f;
    bool open = false;


    // Lua is here 



     lua_State* L = luaL_newstate();
    // luaL_openlibs(L);
    luaL_dostring(L, "print('Hello from Lua 5.1.5')");
    run_lua_script(scriptPath.c_str()); 
    load_config(scriptPath.c_str());
    time_t lastModified = getFileLastModifiedTime(scriptPath);



    // end lua here




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
            if(!elementList.empty()){for(int i=0;i<elementList.size();i++){elementList[i]->destroy(dynamicsWorld);}elementList.clear();}
            run_lua_script(scriptPath.c_str());
            load_config(scriptPath.c_str());

        }

        float delta = GetFrameTime();
        UpdatePhysics(delta);
 
    

        // Handle animation
        //--->
        if (animCount > 0) {
            animFrameCounter += 1.0f;
            if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
            UpdateModelAnimation(model, anims[0], (int)animFrameCounter);
        }
//        std::cout<<"what";

        // Update camera to follow player from behind and above
        Vector3 cameraOffset = {-5.0f, 4.0f, 5.0f}; // Offset behind and above
        camera.position = Vector3Add(PlayerModel::GetPosition(), cameraOffset);
        camera.target = PlayerModel::GetPosition();




    UPDATE_CAMERA();





        // Render
        BeginDrawing();
        ClearBackground(BLACK);
        // ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawCube({ 0.0f, 0.0f, 0.0f }, 20.0f, 0.1f, 20.0f, WHITE);
        
        DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);


        DrawModel(model, playerPos, 1.0f, WHITE);


      render(delta);

    //   Player_Update(delta);
    //   Player_Render();




        


        playerPos = PlayerModel::GetPosition();



        // DrawModelEx(plane, planePos, {1.0f, 0.0f, 0.0f}, -90.0f, {1.0f, 1.0f, 1.0f}, WHITE);
        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Use WASD to move, SPACE to jump", 10, 10, 20, DARKGRAY);





bool open=true;



EndDrawing();














    }


    // Cleanup
        //--->
    if (animCount > 0) UnloadModelAnimations(anims, animCount);
    UnloadModel(model);
    // UnloadModel(plane);
    CleanupPhysics();
    CloseWindow();

    return 0;
}
