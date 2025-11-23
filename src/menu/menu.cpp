#include "menu.h"

MenuScreen::MenuScreen(const std::vector<std::string>& items, Font font, int fontSize)
    : menuItems(items), menuFont(font), fontSize(fontSize) {}

void MenuScreen::Update() {
    selectedIndex = -1;

    if (IsKeyPressed(KEY_DOWN))
        highlightedIndex = (highlightedIndex + 1) % menuItems.size();
    if (IsKeyPressed(KEY_UP))
        highlightedIndex = (highlightedIndex - 1 + menuItems.size()) % menuItems.size();

    if (IsKeyPressed(KEY_ENTER))
        selectedIndex = highlightedIndex;
}

void MenuScreen::Render() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    for (int i = 0; i < menuItems.size(); i++) {
        Color color = (i == highlightedIndex) ? YELLOW : WHITE;
        Vector2 textSize = MeasureTextEx(menuFont, menuItems[i].c_str(), fontSize, 2);

        DrawTextEx(
            menuFont,
            menuItems[i].c_str(),
            { screenWidth / 2.0f - textSize.x / 2, screenHeight / 2.0f + i * (fontSize + 15) },
            fontSize,
            2,
            color
        );
    }
}

