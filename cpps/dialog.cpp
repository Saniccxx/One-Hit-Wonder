#include "../headers/dialog.h"
#include "../headers/renderer.h"
#include "../headers/randomizer.h"
#include <iostream>
#include <vector> // For text wrapping

// Helper function to wrap text
std::vector<std::string> wrap_text(const std::string& text, int font_size, float max_width) {
    std::vector<std::string> wrapped_lines;
    std::string current_line;
    std::string current_word;

    for (char c : text) {
        if (c == ' ' || c == '\n') {
            if (!current_word.empty()) {
                if (static_cast<float>(Renderer::measure_text((current_line + current_word).c_str(), font_size)) <= max_width) {
                    current_line += current_word;
                } else {
                    wrapped_lines.push_back(current_line);
                    current_line = current_word;
                }
                current_word.clear();
            }
            if (c == ' ') {
                if (static_cast<float>(Renderer::measure_text((current_line + " ").c_str(), font_size)) <= max_width) {
                    current_line += " ";
                } else {
                    wrapped_lines.push_back(current_line);
                    current_line = " "; // Start new line with space if needed
                }
            } else if (c == '\n') {
                wrapped_lines.push_back(current_line);
                current_line.clear();
            }
        } else {
            current_word += c;
        }
    }

    if (!current_word.empty()) {
        if (static_cast<float>(Renderer::measure_text((current_line + current_word).c_str(), font_size)) <= max_width) {
            current_line += current_word;
        } else {
            wrapped_lines.push_back(current_line);
            current_line = current_word;
        }
    }
    if (!current_line.empty()) {
        wrapped_lines.push_back(current_line);
    }
    return wrapped_lines;
}


Dialog::Dialog(const std::string_view text_view, float centerX, float centerY)
    : padding(10.0f), center_x(centerX), center_y(centerY), bounds({}) { // Initialize bounds

    randomize_text(); // This sets the 'text' member
    recalculate_layout(); // Calculate layout after text is set
}

void Dialog::recalculate_layout() {
    const int font_size = 20;
    const float text_max_width = 250.0f; // Max width for the text content

    std::vector<std::string> wrapped_lines = wrap_text(text, font_size, text_max_width);
    auto text_content_height = static_cast<float>(wrapped_lines.size() * font_size);
    float max_line_width = 0.0f;
    for (const auto& line : wrapped_lines) {
        auto line_width = static_cast<float>(Renderer::measure_text(line.c_str(), font_size));
        if (line_width > max_line_width) {
            max_line_width = line_width;
        }
    }

    // Calculate dialog dimensions based on text content only
    float dialog_width = max_line_width + 2 * padding;
    float dialog_height = text_content_height + 2 * padding;

    bounds.width = dialog_width;
    bounds.height = dialog_height;
    bounds.x = center_x - bounds.width / 2.0f;
    bounds.y = center_y - bounds.height / 2.0f;

    // Button dimensions
    float button_width = 70.0f;
    float button_height = 40.0f;
    float button_spacing = 10.0f;
    float vertical_button_offset = 10.0f; // Space between dialog and buttons

    // Position buttons below the dialog bounds
    float buttons_y = bounds.y + bounds.height + vertical_button_offset;

    yes_button = std::make_unique<Button>(
        center_x - button_width - button_spacing / 2.0f,
        buttons_y,
        button_width, button_height, "Yes", font_size, GREEN, DARKBLUE, BLUE, SKYBLUE
    );
    no_button = std::make_unique<Button>(
        center_x + button_spacing / 2.0f,
        buttons_y,
        button_width, button_height, "No", font_size, RED, DARKBLUE, BLUE, SKYBLUE
    );
}

void Dialog::Update(const Camera2D* camera) {
    if (yes_button) yes_button->Update(camera);
    if (no_button) no_button->Update(camera);
}

void Dialog::Draw() const {
    // Draw the main dialog background
    Renderer::draw_rectangle_rec(bounds, Renderer::white);

    // Draw wrapped text
    const int font_size = 20;
    // Recalculate wrapped lines for drawing, using the actual bounds width
    std::vector<std::string> wrapped_lines = wrap_text(text, font_size, bounds.width - 2 * padding);
    float current_text_y = bounds.y + padding;
    for (const auto& line : wrapped_lines) {
        // Center the text horizontally within the dialog bounds
        float text_x = bounds.x + (bounds.width - static_cast<float>(Renderer::measure_text(line.c_str(), font_size))) / 2.0f;
        Renderer::draw_text(line, static_cast<int>(text_x), static_cast<int>(current_text_y), font_size, Renderer::red);
        current_text_y += font_size;
    }

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
            "Stay put, or you'll regret it!",
            "Move no further or prepare to die!",
            "You shall not pass, surrender!",
            "Hippity Hoppity get out of this property!",
            "Your tomfooling shall end today!",
            "Stop right there, criminal scum!",
            "No soup for you, next!",
            "Take a walk. Before things get ugly.",
            "You've gotta vanish now, or I'll make you vanish.",
            "I don’t get paid enough to deal with you. Exit is that way.",
            "This is a no go zone! Do you understand the words that are coming out of my mouth?",
            "Turn back, traveler. Only death awaits beyond.",
            "Look, man, my shift ends in two minutes. Just go away so I can go home.",
            "Hey! You! No... wait, what was the password again? Ah, whatever, just get out!",
            "I promised my mom I wouldn't get into fights today. Please move along.",
            "My therapist told me to avoid stressful confrontations. You are a confrontation. Go away.",
            "My orders are to kill on sight. Luckily for you, I forgot my glasses today. Now walk away while I'm blinking.",


        };
        int random_index = randomizer::get_random_int(0, static_cast<int>(possible_texts.size() - 1));
        text = possible_texts[random_index];
        recalculate_layout(); // Recalculate layout after text changes
}