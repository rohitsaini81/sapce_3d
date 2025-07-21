#include "physics.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>
#include "ETC/global_var.h"
#include "Controls/camera.h"
#include "3dObjects/objects.h"


extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include "script/script.h"
#include <filesystem>


#include "rlImGui.h"	
#include "imgui.h"


int main() {

    
    // Initialization
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    InitWindow(800, 600, "Rick and Morty Baby");
    rlImGuiSetup(true); 
    bool open=true;

    ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontDefault();

    INIT_BEFORE();
    InitPhysics();
        //--->
const std::string Path= "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/";
const char* modelPath = "/run/media/rohit/8b5b9054-ef1c-4785-aa10-f6a2608b67c8/ArchLinux/work/raylib-cpp/rohit/src/assets/rick/rick.glb";
    Model model = LoadModel(modelPath);
    Model tempModel = LoadModel((project_dir+"src/assets/american_road_intersection.glb").c_str());
    Model plane = LoadModel((project_dir+"src/assets/cube.glb").c_str());
    if (plane.meshCount == 0) {std::cerr << "Failed to load plane model!" << std::endl;}

    int animCount = 0;
    ModelAnimation* anims = LoadModelAnimations(modelPath, &animCount);
    float animFrameCounter = 0.0f;


    CAM_INIT();
    // Player state
    Vector3 planePos = {2.0f, 0.0f, 2.0f};
    float velocityY = 0.0f;
    float gravity = 0.1f;
    float speed = 5.0f;

    SetTargetFPS(60);
    SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);




    // Lua is here 
    const std::string scriptPath = project_dir+"src/script/config.lua";
     lua_State* L = luaL_newstate();
    // luaL_openlibs(L);
    luaL_dostring(L, "print('Hello from Lua 5.1.5')");
    run_lua_script(scriptPath.c_str()); 
    load_config(scriptPath.c_str());
    time_t lastModified = getFileLastModifiedTime(scriptPath);



    // end lua here

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
        camera.position = Vector3Add(playerPos, cameraOffset);
        camera.target = playerPos;



// Skip camera updates when interacting with ImGui
if (!ImGui::GetIO().WantCaptureMouse) {
    // Process camera/mouse here
    UPDATE_CAMERA();
  
}


if (IsKeyPressed(KEY_X)) {
    open = !open;
        if (open) {
        EnableCursor();   // Show and unlock the mouse for ImGui
    } else {
        DisableCursor();  // Hide and lock the mouse for game control
    }
    std::cout << "Toggled ImGui window: " << (open ? "OPEN" : "CLOSED") << std::endl;
}

           


        // Render
        BeginDrawing();
        ClearBackground(BLACK);
        // ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawCube({ 0.0f, 0.0f, 0.0f }, 20.0f, 0.1f, 20.0f, WHITE);
        
        DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);


        DrawModel(model, playerPos, 1.0f, WHITE);
        // DrawModel(tempModel,planePos,1.0f,WHITE);


        render(delta);








        playerPos.x=getPlayerX();
        playerPos.y=(getPlayerY()-1.0f);
        playerPos.z=getPlayerZ();



        // DrawModelEx(plane, planePos, {1.0f, 0.0f, 0.0f}, -90.0f, {1.0f, 1.0f, 1.0f}, WHITE);
        // DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("SPACE ENGINE / RICK AND MORTY GM", 10, 10, 20, DARKGRAY);
        
        




        rlImGuiBegin();
ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_Always);
// ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

if (open) {

if (ImGui::Begin("Menu Window", &open, ImGuiWindowFlags_AlwaysVerticalScrollbar)) {
    ImGui::TextUnformatted(ICON_FA_JEDI);
        if (ImGui::Button("Click Me")) {
        std::cout << "Button clicked!" << std::endl;
    }
    ImGui::SameLine();
    ImGui::Text("Camera Target: X %.2f Y %.2f", camera.target.x, camera.target.y);
  bool show_demo_window = true;
    static float f = 0.0f;
                static int counter = 0;
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);  
    ImGui::BeginChild("ScrollRegion", ImVec2(0, 0), true);

               if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
    for (int i = 0; i < 50; i++) {
        ImGui::Text("Move Tool %d", i);
    }
    ImGui::EndChild();

    ImGui::End();
    
}
}
rlImGuiEnd();


        EndDrawing();














    }


    // Cleanup
        //--->
    if (animCount > 0) UnloadModelAnimations(anims, animCount);
    UnloadModel(model);
    UnloadModel(plane);
    CleanupPhysics();
    CloseWindow();

    return 0;
}
