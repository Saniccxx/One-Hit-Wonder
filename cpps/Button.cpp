#include "../headers/Button.h"
#include "../headers/camera.h"
#include "raylib.h"

Button::Button(float x, float y, float width, float height, const std::string& text, int textSize, Color textColor, Color buttonColor, Color hoverColor, Color clickColor)
    : rect{ x, y, width, height }, text(text), textSize(textSize), textColor(textColor), buttonColor(buttonColor), hoverColor(hoverColor), clickColor(clickColor), isHovered(false), isClicked(false) {}

void Button::Update(const GameCamera& camera) {
    Vector2 mousePoint = GetMousePosition();

    const Camera2D& cam = camera.get_camera();

    Vector2 worldMousePos = GetScreenToWorld2D(mousePoint, cam);


    isHovered = CheckCollisionPointRec(worldMousePos, rect);
    isClicked = isHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button::Draw() const {
    Color color = buttonColor;
    if (isClicked) {
        color = clickColor;
    } else if (isHovered) {
        color = hoverColor;
    }

    DrawRectangleRec(rect, color);
    int textWidth = MeasureText(text.c_str(), textSize);
    float textX = rect.x + (rect.width - textWidth) / 2;
    float textY = rect.y + (rect.height - textSize) / 2;
    DrawText(text.c_str(), static_cast<int>(textX), static_cast<int>(textY), textSize, textColor);
}

bool Button::IsClicked() const {
    return isClicked;
}

void Button::SetText(const std::string& newText) {
    text = newText;
}
