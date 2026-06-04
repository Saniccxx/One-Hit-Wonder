#include "../headers/dialog.h"
#include "../headers/renderer.h"
#include "../headers/randomizer.h"
#include <iostream>

Dialog::Dialog(const std::string_view text, float x, float y) : x(x), y(y) {
    randomize_text();
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

void Dialog::randomize_text() {
        // Example of randomizing text, you can replace this with your own logic
        std::vector<std::string> possible_texts = {
            "Step back or get ready to die!",
            "Return whence you came!",
            "Stay put!",
            "Move no further or prepare to die!",
            "You shall not pass, surrender!",
            "Hippity Hoppity get out of this property!",
            "Your tomfooling shall end today!",
            "Stop right there, criminal scum!",
            "No soup for you, next!",
            "Take a walk, friend. Before things get ugly.",
            "You've got five seconds to vanish, or I'll make you vanish.",
            "I don’t get paid enough to deal with you. Exit is that way.",
            "This is a no go zone! Do you understand the words that are coming out of my mouth?",
            "Turn back, traveler. Only death awaits beyond this gate.",
            "Look, man, my shift ends in two minutes. Just go away so I can go home.",
            "Hey! You! No... wait, what was the password again? Ah, whatever, just get out!",
            "I promised my mom I wouldn't get into fights today. Please move along.",
            "My therapist told me to avoid stressful confrontations. You are a confrontation. Go away.",
            "My orders are to kill on sight. Luckily for you, I forgot my glasses today. Now walk away while I'm blinking.",

        };
        int random_index = randomizer::get_random_int(0, possible_texts.size() - 1);
        text = possible_texts[random_index];
}