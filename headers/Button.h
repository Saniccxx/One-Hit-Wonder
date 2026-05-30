#pragma once

#include "renderer.h"
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string_view text, int textSize, Color textColor, Color buttonColor, Color hoverColor, Color clickColor);
    // Accept optional Camera2D pointer; if null, use screen coordinates
    void Update(const Camera2D* camera);
    void Draw() const;
    bool IsClicked() const;
    void SetText(const std::string_view newText);

private:
    Rectangle rect;
    std::string text;
    int textSize;
    Color textColor;
    Color buttonColor;
    Color hoverColor;
    Color clickColor;
    bool isHovered;
    bool isClicked;
};