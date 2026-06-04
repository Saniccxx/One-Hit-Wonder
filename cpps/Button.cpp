#include "Button.h"
#include "renderer.h"

Button::Button(float x, float y, float width, float height, const std::string_view text, int textSize, Color textColor, Color buttonColor, Color hoverColor, Color clickColor)
    : rect{ x, y, width, height }, text(text), textSize(textSize), textColor(textColor), buttonColor(buttonColor), hoverColor(hoverColor), clickColor(clickColor), isHovered(false), isClicked(false) {}

void Button::Update(const Camera2D* camera) {
    Vector2 mousePoint = Renderer::get_mouse_pos();

    Vector2 worldMousePos = mousePoint;
    if (camera) {
        worldMousePos = Renderer::get_screen_to_world_2d(mousePoint, *camera);
    }

    isHovered = Renderer::check_collision_point_rec(worldMousePos, rect);
    isClicked = isHovered && Renderer::is_mouse_button_clicked(MOUSE_BUTTON_LEFT);
}

void Button::Draw() const {
    Color color = buttonColor;
    if (isClicked) {
        color = clickColor;
    } else if (isHovered) {
        color = hoverColor;
    }

    Renderer::draw_rectangle_rec(rect, color);
    int textWidth = Renderer::measure_text(text.c_str(), textSize);
    float textX = rect.x + (rect.width - textWidth) / 2;
    float textY = rect.y + (rect.height - textSize) / 2;
    Renderer::draw_text(text, static_cast<int>(textX), static_cast<int>(textY), textSize, textColor);
}

bool Button::IsClicked() const {
    return isClicked;
}

void Button::SetText(const std::string_view newText) {
    text = newText;
}
