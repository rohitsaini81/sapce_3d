#pragma once
#include "raylib.h"
#include <vector>
#include <string>

class MenuScreen {
public:
    MenuScreen(const std::vector<std::string>& items, Font font, int fontSize = 32);

    // Update menu logic (input, selection, etc.)
    void Update();

    // Render menu to screen
    void Render();

    // Returns -1 if nothing selected, otherwise index of selected item
    int GetSelected() const { return selectedIndex; }

private:
    std::vector<std::string> menuItems;
    Font menuFont;
    int fontSize;

    int highlightedIndex = 0;   // For navigating menu
    int selectedIndex = -1;     // Set when ENTER pressed
};

