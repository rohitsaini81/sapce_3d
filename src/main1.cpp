// main.cpp
#include <raylib.h>
#include <thread>
#include <atomic>
#include <GLFW/glfw3.h>
#include "iostream"

std::atomic<int> sharedValue = 0;

void ToolWindow() {
    if (!glfwInit()) return;

    GLFWwindow* window = glfwCreateWindow(300, 200, "Tool Panel", nullptr, nullptr);
    if (!window) return;

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Just an example: update sharedValue with arrow keys
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) sharedValue++;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) sharedValue--;

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main() {
    InitWindow(800, 450, "Raylib Main Window");
    SetTargetFPS(60);

    std::thread toolThread(ToolWindow);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("Shared Value: %d", sharedValue.load()), 20, 20, 20, DARKGRAY);

        DrawText("Main Game Window", 20, 20, 20, DARKGRAY);
        DrawCircle(400, 225, circleRadius.load(), SKYBLUE);

        std::lock_guard<std::mutex> lock(textMutex);
        EndDrawing();
    }

    if (toolThread.joinable()) toolThread.join();

    CloseWindow();
    return 0;
}
