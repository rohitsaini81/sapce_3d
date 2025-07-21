#include "raylib.h"
#include <thread>
#include <atomic>
#include <chrono>
#include "iostream"

// Simulate resource loading
void LoadResources(std::atomic<bool> &loadingDone) {
    // Simulate long loading process
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
    // TODO: Load your actual textures, sounds, etc. here using LoadTexture(), LoadSound(), etc.
    
    loadingDone = true;
}

int main() {
    InitWindow(800, 450, "raylib multithreaded loading");
    SetTargetFPS(60);

    std::atomic<bool> loadingDone = false;

    // Start resource loading in background thread
    std::thread loadingThread(LoadResources, std::ref(loadingDone));

    int dotCounter = 0;
    float timer = 0.0f;

    while (!WindowShouldClose()) {
        if (!loadingDone) {
            // Animate the dots (e.g. "Loading.", "Loading..", "Loading...")
            timer += GetFrameTime();
            if (timer >= 0.5f) {
                dotCounter = (dotCounter + 1) % 4;  // Cycle through 0 to 3
                timer = 0.0f;
            }

            BeginDrawing();
            ClearBackground(RAYWHITE);

            std::string loadingText = "Loading";
            for (int i = 0; i < dotCounter; ++i) loadingText += ".";

            DrawText(loadingText.c_str(), 350, 200, 30, DARKGRAY);

            EndDrawing();
        } else {
            // Done loading, break and show your actual scene
            break;
        }
    }

    // Make sure thread has finished
    if (loadingThread.joinable()) loadingThread.join();

    // Normally continue to your game or menu screen
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Resources Loaded!", 300, 200, 30, GREEN);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
