#include "../headers/dialog.h"
#include "../headers/renderer.h"

Dialog::Dialog(const std::string_view text, float x, float y) : text(text), x(x), y(y) {
    yes_button = std::make_unique<Button>(
        x - 80, y + 20, 70, 40, "Yes", 20, GREEN, DARKBLUE, BLUE, SKYBLUE
    );
    no_button = std::make_unique<Button>(
        x + 10, y + 20, 70, 40, "No", 20, RED, DARKBLUE, BLUE, SKYBLUE
    );
}

void Dialog::Update(const Camera2D* camera) {
    if (yes_button) yes_button->Update(camera);
    if (no_button) no_button->Update(camera);
}

void Dialog::Draw() const {
    Renderer::draw_rectangle(x - 100, y - 40, 670-420+67+69, 120, Renderer::white);
    Renderer::draw_text(text, x - 90, y - 30, 20, Renderer::red);
    if (yes_button) yes_button->Draw();
    if (no_button) no_button->Draw();
}

DialogResult Dialog::GetResult() const {
    if (yes_button && yes_button->IsClicked()) return DialogResult::Yes;
    if (no_button && no_button->IsClicked()) return DialogResult::No;
    return DialogResult::None;
}
