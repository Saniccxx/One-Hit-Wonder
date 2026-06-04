#pragma once

#include <string>
#include <memory>
#include "Button.h"

class Camera2D;

enum class DialogResult {
    None,
    Yes,
    No
};

class Dialog {
public:
    Dialog(std::string_view text, float x, float y);
    void Update(const Camera2D* camera);
    void Draw() const;
    [[nodiscard]] DialogResult GetResult() const;
    void randomize_text();

private:
    std::string text;
    float x;
    float y;
    std::unique_ptr<Button> yes_button;
    std::unique_ptr<Button> no_button;
};

