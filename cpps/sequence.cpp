#include "sequence.h"
#include "renderer.h"
#include <iostream>
#include "raylib.h"
#include "game.h"
#include "map_display.h" // Added so the return button can actually route back to the map
#include <cmath>
#include <algorithm>

Sequence::Sequence(Game& game, InteractionObject* interaction_object): game(game), interaction_object(interaction_object) {
    notes = interaction_object -> get_notes();
    durations = interaction_object -> get_durations();
    std::cout << "post notes";

    for (size_t i = 0; i < notes.size(); i++) {
        volumes[i] = 0;
    }
    current = 0;
    end = 0;
    offset = 20;
    compleation_level = 0.0f;
    C = game.get_sound("C.wav");
    D = game.get_sound("D.wav");
    E = game.get_sound("E.wav");
    F = game.get_sound("F.wav");
    G = game.get_sound("G.wav");
    A = game.get_sound("A.wav");
    B = game.get_sound("B.wav");
    C2 = game.get_sound("C2.wav");
    plays = {
        {0, C},
        {1, D},
        {2, E},
        {3, F},
        {4, G},
        {5, A},
        {6, B},
        {7, C2}
    };
    length = notes.size();
    level = 0;
    current_note = -1;
    completed = 0;
    timer = 0;

    next_note_to_hit = 0;
    perfect_count = 0;
    great_count = 0;
    good_count = 0;
    miss_count = 0;
    ratings.clear();
    note_results.assign(notes.size(), 0);

    global_timer = 0;
    int acc = 120; // start later
    for (int d : durations) {
        target_times.push_back(acc);
        acc += d;
    }
}

void Sequence::spawn_rating(const std::string& text, Color color, float x, float y) {
    const float scale = static_cast<float>(game.height) / 1080.0f;

    FloatingRating r;
    r.text = text;
    r.color = color;
    r.pos = { x, y };
    r.vel = { 0.0f, -1.5f * scale };
    r.alpha = 1.0f;
    r.scale = 1.0f;
    r.life = 1.0f;
    ratings.push_back(r);
}

void Sequence::test() {}

void Sequence::add_level() {
    level += 1;
}

void Sequence::get_key() {
    int a = 0;
    for (auto& pair : keys) {
        if (Renderer::is_key_pressed(pair.first)) {
            int index = pair.second;
            std::cout << "Key index " << index << " pressed\n";
            a = 1;
            current_note = index;
        }
    }
    if (Renderer::is_key_pressed(KEY_BACKSPACE)) {
        a = 1;
        current_note = -2;
    }

    if (a == 0) {
        current_note = -1;
    }
}

void Sequence::progress() {
    const float scale = static_cast<float>(game.height) / 1080.0f;
    auto S = [&](float v) { return static_cast<int>(v * scale); };

    static const std::array<int,8> kc = { KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L };

    while (next_note_to_hit < target_times.size() && global_timer > target_times[next_note_to_hit] + 18) {
        int nv = notes[next_note_to_hit];
        int nk = (nv >= 0 && nv < 8) ? kc[nv] : -1;
        if (nk >= 0 && Renderer::is_key_down(nk)) break;

        const int key_width = S(80);
        const int start_x = S(680);
        float missed_x = start_x + (nv * key_width) + key_width / 2.0f;
        const int hit_y = S(800);

        note_results[next_note_to_hit] = -1;
        spawn_rating("MISS", RED, missed_x, hit_y - S(40));
        combo = 0;
        miss_count++;
        next_note_to_hit++;
    }

    if (current_note == -2) {
        level = 0;
        next_note_to_hit = 0;
        combo = 0;
        score = 0;
        compleation_level = 0.0f;
        global_timer = 0;
        completed = 0;
        end = 0;
        current = 0;
        timer = 0;
        perfect_count = 0;
        great_count = 0;
        good_count = 0;
        miss_count = 0;
        ratings.clear();
        note_results.assign(notes.size(), 0);
        return;
    }

    if (current_note >= 0 && next_note_to_hit < length) {
        int target_note = notes[next_note_to_hit];
        int target_time = target_times[next_note_to_hit];
        int diff = global_timer - target_time;

        const int key_width = S(80);
        const int start_x = S(680);
        float note_center_x = start_x + (target_note * key_width) + key_width / 2.0f;
        const int hit_y = S(800);

        if (current_note == target_note) {
            int abs_diff = std::abs(diff);
            if (abs_diff <= 18) {
                std::string rating_str = "GOOD";
                Color rating_color = ORANGE;
                int points = 100;

                if (abs_diff <= 5) {
                    rating_str = "PERFECT"; rating_color = GOLD; points = 300; perfect_count++;
                } else if (abs_diff <= 11) {
                    rating_str = "GREAT"; rating_color = SKYBLUE; points = 200; great_count++;
                } else {
                    good_count++;
                }

                combo++;
                score += points * (1 + combo / 10);
                note_results[next_note_to_hit] = 1;
                spawn_rating(rating_str, rating_color, note_center_x, hit_y - S(40));
                next_note_to_hit++;

            } else if (diff < -18 && diff >= -45) {
                spawn_rating("MISS", RED, note_center_x, hit_y - S(40));
                combo = 0;
                miss_count++;
                next_note_to_hit++;
            }
        } else {
            if (std::abs(diff) <= 18) {
                float wrong_note_center_x = start_x + (current_note * key_width) + key_width / 2.0f;
                note_results[next_note_to_hit] = -1;
                spawn_rating("MISS", RED, wrong_note_center_x, hit_y - S(40));
                combo = 0;
                miss_count++;
                next_note_to_hit++;
            }
        }
    }

    level = next_note_to_hit;
    float target_level = 0.0f;
    if (interaction_object && interaction_object->minimum_score > 0) {
        target_level = (float)score / interaction_object->minimum_score;
        if (target_level > 1.0f) target_level = 1.0f;
    }
    compleation_level = target_level;

    if (next_note_to_hit >= length && completed == 0) {
        completed = 1;
        game.player_speed = 20.0f * 0.01;

        if (score >= interaction_object->minimum_score) {
            interaction_object->beaten = true;
            interaction_object->setTexture(game.get_texture("beaten.png"));
            std::cout << "WIN: " << score << std::endl;
        } else {
            interaction_object->beaten = false;
            std::cout << "LOSE: " << score << std::endl;
        }
    }
}

void Sequence::check() {
    get_key();
    progress();
}

void Sequence::play() {
    float step = GetFrameTime() * 100.0f;
    global_timer += step;

    if (completed == 0) {
        if (notes.size() > 0 && global_timer >= target_times[0]) {
            if (current < length) {
                if (timer >= durations[current]) {
                    timer = 0.0f;
                    current += 1;
                }
                timer += step;
            }
        }
    }
}
void Sequence::play2() {


    if (end==0) {
        if (timer==0) {

            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
            Renderer::play_sound(plays[notes[current]]);

        }
        if (timer<=offset and timer>0) {
            volumes[notes[current]]+=1.0f/offset;
            //std::cout<<"change"<<std::endl;
            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
        }
        if (timer<durations[current]+offset and timer>=durations[current]-offset) {
            volumes[notes[current]]-=1.0f/offset;
            Renderer::set_sound_volume(plays[notes[current]], volumes[notes[current]]);
        }
        //std::cout<<volumes[notes[current]]<<std::endl;
        if (timer==durations[current]) {

            timer=-1;

            Renderer::stop_sound(plays[notes[current]]);

            current+=1;



            if (current>=length) {

                end=1;
            }
        }
        timer++;
    }



}
void Sequence::draw_progress_bar() {
    const float scale = static_cast<float>(game.height) / 1080.0f;
    auto S = [&](float v) { return static_cast<int>(v * scale); };

    if (std::abs(bar_progress - compleation_level) > 0.01 && bar_changing == 0) {
        bar_changing = 1;
        d_bar = (compleation_level - bar_progress) / bar_change_speed;
        if (compleation_level == 0) {
            bar_color = RED;
        }
    }
    if (bar_changing > 0) {
        bar_progress += d_bar;
        bar_changing++;
        if (bar_changing >= bar_change_speed + 1) {
            bar_changing = 0;
            if (compleation_level == 1) {
                bar_progress = 1;
            }
            else if (compleation_level == 0) {
                bar_progress = 0;
                bar_color = GREEN;
            }
        }
    }

    DrawRectangle(S(100), S(100), S(bar_width), S(bar_height), LIGHTGRAY);
    DrawRectangle(S(100), S(100), S(bar_width * bar_progress), S(bar_height), bar_color);
}

void Sequence::draw_progress_bar_chords(int x, int y, int w, int h) {
    const float scale = static_cast<float>(game.height) / 1080.0f;
    auto S = [&](float v) { return static_cast<int>(v * scale); };

    if (std::abs(bar_progress - compleation_level) > 0.01 && bar_changing == 0) {
        bar_changing = 1;
        d_bar = (compleation_level - bar_progress) / bar_change_speed;
        if (compleation_level == 0) {
            bar_color = RED;
        }
    }
    if (bar_changing > 0) {
        bar_progress += d_bar;
        bar_changing++;
        if (bar_changing >= bar_change_speed + 1) {
            bar_changing = 0;
            if (compleation_level == 1) {
                bar_progress = 1;
            }
            else if (compleation_level == 0) {
                bar_progress = 0;
                bar_color = GREEN;
            }
        }
    }

    int panel_x = S(x);
    int panel_y = S(y);
    int panel_w = S(w);
    int panel_h = S(640); // Increased from 600 to 640 to fit the button cleanly

    DrawRectangleRounded(Rectangle{(float)panel_x, (float)panel_y, (float)panel_w, (float)panel_h}, 0.05f, 4, Color{ 25, 25, 35, 200 });
    DrawRectangleRoundedLines(Rectangle{(float)panel_x, (float)panel_y, (float)panel_w, (float)panel_h}, 0.05f, 4, Color{ 80, 80, 120, 120 });

    DrawText("RHYTHM COMBAT", panel_x + S(30), panel_y + S(30), S(28), GOLD);
    DrawLine(panel_x + S(30), panel_y + S(70), panel_x + panel_w - S(30), panel_y + S(70), Color{ 80, 80, 100, 100 });

    DrawText("TARGET PROGRESS", panel_x + S(30), panel_y + S(90), S(16), Color{ 180, 180, 200, 255 });

    int bar_y = panel_y + S(115);
    int bar_w = panel_w - S(60);
    int bar_h = S(h);
    DrawRectangleRounded(Rectangle{(float)(panel_x + S(30)), (float)bar_y, (float)bar_w, (float)bar_h}, 0.3f, 4, Color{ 40, 40, 50, 255 });

    Color fill_color = ColorFromHSV(bar_progress * 120.0f, 0.9f, 0.9f);
    if (bar_progress > 0) {
        DrawRectangleRounded(Rectangle{(float)(panel_x + S(30)), (float)bar_y, (float)(bar_w * bar_progress), (float)bar_h}, 0.3f, 4, fill_color);
    }
    DrawRectangleRoundedLines(Rectangle{(float)(panel_x + S(30)), (float)bar_y, (float)bar_w, (float)bar_h}, 0.3f, 4, Color{ 80, 80, 100, 255 });

    std::string pct_text = std::to_string((int)(bar_progress * 100)) + "%";
    DrawText(pct_text.c_str(), panel_x + panel_w - S(30) - MeasureText(pct_text.c_str(), S(16)), panel_y + S(90), S(16), WHITE);

    DrawText("SCORE", panel_x + S(30), panel_y + S(170), S(18), Color{ 180, 180, 200, 255 });
    if (interaction_object) {
        std::string target_str = "TARGET: " + std::to_string(interaction_object->minimum_score);
        DrawText(target_str.c_str(), panel_x + S(130), panel_y + S(195), S(16), GOLD);
    }
    std::string score_str = std::to_string(score);
    Color score_color = (interaction_object && score >= interaction_object->minimum_score) ? GREEN : WHITE;
    DrawText(score_str.c_str(), panel_x + S(30), panel_y + S(195), S(36), score_color);

    if (combo > 0) {
        float combo_scale = 1.0f + 0.15f * sinf(global_timer * 0.1f);
        int combo_font_size = S(32) * combo_scale;
        std::string combo_str = std::to_string(combo);

        DrawText("COMBO", panel_x + panel_w - S(150), panel_y + S(170), S(18), Color{ 180, 180, 200, 255 });
        DrawText(combo_str.c_str(), panel_x + panel_w - S(150), panel_y + S(195), combo_font_size, GOLD);
    }

    DrawLine(panel_x + S(30), panel_y + S(260), panel_x + panel_w - S(30), panel_y + S(260), Color{ 80, 80, 100, 100 });

    DrawText("PERFORMANCE", panel_x + S(30), panel_y + S(280), S(20), GOLD);

    struct StatRow {
        std::string label;
        int val;
        Color col;
    };
    std::vector<StatRow> stats = {
        { "Perfect", perfect_count, GOLD },
        { "Great", great_count, SKYBLUE },
        { "Good", good_count, ORANGE },
        { "Miss", miss_count, RED }
    };

    int row_y = panel_y + S(320);
    for (const auto& s : stats) {
        DrawText(s.label.c_str(), panel_x + S(40), row_y, S(18), s.col);
        std::string val_str = std::to_string(s.val);
        int val_w = MeasureText(val_str.c_str(), S(18));
        DrawText(val_str.c_str(), panel_x + panel_w - S(40) - val_w, row_y, S(18), WHITE);
        row_y += S(35);
    }

    DrawLine(panel_x + S(30), panel_y + S(465), panel_x + panel_w - S(30), panel_y + S(465), Color{ 80, 80, 100, 100 });

    if (completed) {
        if (!interaction_object->beaten) {
            DrawText("YOU FAILED!", panel_x + S(30), panel_y + S(485), S(28), RED);
            DrawText("Press BACKSPACE to restart", panel_x + S(30), panel_y + S(520), S(16), WHITE);
        }
        else {
            DrawText("SONG COMPLETE!", panel_x + S(30), panel_y + S(490), S(24), GREEN);
        }
    } else {
        DrawText("Reset song: BACKSPACE", panel_x + S(30), panel_y + S(485), S(16), GRAY);
        DrawText("Press keys as they cross the line!", panel_x + S(30), panel_y + S(515), S(16), GRAY);
    }

    int btn_w = S(220);
    int btn_h = S(45);
    int btn_x = panel_x + (panel_w / 2) - (btn_w / 2);
    int btn_y = panel_y + panel_h - btn_h - S(25);

    Rectangle btn_rec = { (float)btn_x, (float)btn_y, (float)btn_w, (float)btn_h };
    Vector2 mouse = GetMousePosition();
    bool is_hovered = CheckCollisionPointRec(mouse, btn_rec);

    Color btn_fill = is_hovered ? Color{ 72, 172, 239, 255 } : Color{ 52, 152, 219, 255 };
    DrawRectangleRounded(btn_rec, 0.3f, 4, btn_fill);
    DrawRectangleRoundedLines(btn_rec, 0.3f, 4, WHITE);

    std::string btn_text = "Return to Map";
    int text_w = MeasureText(btn_text.c_str(), S(18));
    DrawText(btn_text.c_str(), btn_x + (btn_w / 2) - (text_w / 2), btn_y + (btn_h / 2) - S(9), S(18), WHITE);

    if (is_hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        game.revert_display();
    }
}

void Sequence::draw_falling_keys() {
    const float scale = static_cast<float>(game.height) / 1080.0f;
    auto S = [&](float v) { return static_cast<int>(v * scale); };
    auto Sf = [&](float v) { return v * scale; };

    const int hit_y = S(800);
    const int start_x = S(680);
    const int key_width = S(80);
    const float speed = Sf(4.0f);

    DrawRectangle(start_x, S(50), 8 * key_width, hit_y - S(50), Color{ 15, 15, 20, 220 });

    for (int col = 0; col <= 8; col++) {
        DrawLine(start_x + col * key_width, S(50), start_x + col * key_width, hit_y + S(40), Color{ 60, 60, 80, 100 });
    }

    std::array<std::pair<int, std::string>, 8> key_bindings = {{
        { KEY_S, "S" }, { KEY_D, "D" }, { KEY_F, "F" }, { KEY_G, "G" },
        { KEY_H, "H" }, { KEY_J, "J" }, { KEY_K, "K" }, { KEY_L, "L" }
    }};

    for (int col = 0; col < 8; col++) {
        int x = start_x + col * key_width;
        bool is_down = Renderer::is_key_down(key_bindings[col].first);

        if (is_down) {
            DrawRectangle(x, S(50), key_width, hit_y - S(50), Color{ 255, 255, 255, 20 });
        }

        Rectangle target_rec = { (float)x + Sf(6), (float)hit_y - Sf(20), (float)key_width - Sf(12), Sf(40.0f) };
        if (is_down) {
            DrawRectangleRounded(target_rec, 0.2f, 4, Color{ 80, 80, 120, 150 });
            DrawRectangleRoundedLines(target_rec, 0.2f, 4, WHITE);
        } else {
            DrawRectangleRounded(target_rec, 0.2f, 4, Color{ 30, 30, 45, 150 });
            DrawRectangleRoundedLines(target_rec, 0.2f, 4, Color{ 100, 100, 150, 150 });
        }

        int text_w = MeasureText(key_bindings[col].second.c_str(), S(18));
        DrawText(key_bindings[col].second.c_str(), x + key_width/2 - text_w/2, hit_y - S(9), S(18), is_down ? WHITE : Color{ 180, 180, 220, 200 });
    }

    DrawLine(start_x, hit_y, start_x + 8 * key_width, hit_y, ColorAlpha(WHITE, 0.4f));

    size_t draw_start = 0;
    if (next_note_to_hit > 0) {
        size_t back = next_note_to_hit;
        while (back > 0) {
            back--;
            if (global_timer >= (float)(target_times[back] + durations[back])) {
                draw_start = back + 1;
                break;
            }
        }
    }

    for (size_t j = draw_start; j < notes.size(); j++) {
        float time_diff = target_times[j] - global_timer;
        float key_height = durations[j] * speed;
        float bottom_y = hit_y - (time_diff * speed);
        float top_y = bottom_y - key_height;

        if (time_diff >= 750) continue;
        if (top_y > hit_y) continue;

        int x = start_x + (notes[j] * key_width);

        Color note_color = SKYBLUE;
        if (notes[j] == 0 || notes[j] == 7) note_color = PINK;
        else if (notes[j] == 1 || notes[j] == 6) note_color = PURPLE;
        else if (notes[j] == 2 || notes[j] == 5) note_color = LIME;
        else note_color = GOLD;

        float draw_bottom = std::min(bottom_y, (float)hit_y);
        float draw_h = draw_bottom - top_y;
        if (draw_h <= 0) continue;

        Rectangle rec = { (float)x + Sf(6), top_y, (float)key_width - Sf(12), draw_h };

        Color current_draw_color = note_color;
        Color current_border_color = WHITE;
        bool draw_glow = false;

        if (j < next_note_to_hit) {
            bool was_hit = (j < note_results.size() && note_results[j] == 1);
            static const std::array<int,8> hkc = { KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L };
            int h_nk = (notes[j] >= 0 && notes[j] < 8) ? hkc[notes[j]] : -1;
            bool still_holding = was_hit && (h_nk >= 0) && Renderer::is_key_down(h_nk);

            current_draw_color = was_hit ? (still_holding ? note_color : ColorAlpha(note_color, 0.6f)) : Color{ 45, 45, 55, 210 };
            current_border_color = was_hit ? (still_holding ? WHITE : ColorAlpha(WHITE, 0.35f)) : Color{ 70, 70, 80, 150 };
            draw_glow = still_holding;

        } else if (j == next_note_to_hit) {
            std::array<int,8> key_codes = { KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L };
            int note_key = (notes[j] >= 0 && notes[j] < 8) ? key_codes[notes[j]] : -1;
            bool holding = (note_key >= 0) && Renderer::is_key_down(note_key);

            if (holding && bottom_y >= hit_y) {
                draw_glow = true;
            }
        }

        DrawRectangleRounded(rec, 0.2f, 4, current_draw_color);
        DrawRectangleRoundedLines(rec, 0.2f, 4, current_border_color);

        if (draw_glow) {
            DrawRectangleRounded({ (float)x + Sf(6), (float)hit_y - Sf(4), (float)key_width - Sf(12), Sf(8) }, 0.4f, 4, ColorAlpha(WHITE, 0.6f));
        }
    }

    for (auto it = ratings.begin(); it != ratings.end(); ) {
        it->pos.x += it->vel.x;
        it->pos.y += it->vel.y;
        it->life -= GetFrameTime();
        it->alpha = it->life / 1.0f;
        if (it->alpha < 0) it->alpha = 0;

        int font_size = S(28) * it->scale;
        int text_w = MeasureText(it->text.c_str(), font_size);

        DrawText(it->text.c_str(), it->pos.x - text_w/2 + S(2), it->pos.y + S(2), font_size, ColorAlpha(BLACK, it->alpha));
        DrawText(it->text.c_str(), it->pos.x - text_w/2, it->pos.y, font_size, ColorAlpha(it->color, it->alpha));

        if (it->life <= 0) {
            it = ratings.erase(it);
        } else {
            ++it;
        }
    }
}