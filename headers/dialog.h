#pragma once

#include <string>
#include <memory>
#include "Button.h"
#include <raylib.h> // For Rectangle

class Camera2D;

enum class DialogResult {
    None,
    Yes,
    No
};

class Dialog {
public:
    Dialog(std::string_view text, float centerX, float centerY);
    void Update(const Camera2D* camera);
    void Draw() const;
    [[nodiscard]] DialogResult GetResult() const;
    void randomize_text();

private:
    std::string text;
    Rectangle bounds;
    float padding;
    float center_x; // Store center_x and center_y for recalculation
    float center_y;
    std::unique_ptr<Button> yes_button;
    std::unique_ptr<Button> no_button;

    void recalculate_layout(); // New method to adjust bounds and button positions
};