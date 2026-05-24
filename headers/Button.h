#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"
#include <string>

class Button {
public:
    Button(float x, float y, float width, float height, const std::string& text, int textSize, Color textColor, Color buttonColor, Color hoverColor, Color clickColor);
    void Update();
    void Draw() const;
    bool IsClicked() const;
    void SetText(const std::string& newText);

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

#endif