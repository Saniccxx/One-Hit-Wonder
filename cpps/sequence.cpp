#include "../headers/sequence.h"
#include "../headers/renderer.h"
#include <iostream>
#include "raylib.h"
#include "../headers/game.h"
#include <cmath>

Sequence::Sequence(Game& game, InteractionObject* interaction_object): game(game), interaction_object(interaction_object) {
    notes = interaction_object -> get_notes();
    durations = interaction_object -> get_durations();
    std::cout << "post notes";

    for (i=0; i<notes.size(); i++) {
        volumes[i]=0;
    }
    current=0;
    end=0;
    offset=20;
    compleation_level=0.0f;
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
    length=notes.size();
    level=0;
    current_note=-1;
    completed=0;
    timer=0;

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
    FloatingRating r;
    r.text = text;
    r.color = color;
    r.pos = { x, y };
    r.vel = { 0.0f, -1.5f };
    r.alpha = 1.0f;
    r.scale = 1.0f;
    r.life = 1.0f;
    ratings.push_back(r);
}

void Sequence::test() {


}
void Sequence::add_level() {
    level+=1;
}


void Sequence::get_key() {
    int a=0;
    for (auto& pair : keys) {
        if (Renderer::is_key_pressed(pair.first)) {
            int index = pair.second;
            std::cout << "Key index " << index << " pressed\n";
            a=1;
            current_note=index;
        }
    }
    if (Renderer::is_key_pressed(KEY_BACKSPACE)) {
        a=1;
        current_note=-2;
    }


    if (a==0) {
        current_note=-1;
    }

}
void Sequence::progress() {
    static const std::array<int,8> kc = { KEY_A, KEY_S, KEY_D, KEY_F, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON };

    while (next_note_to_hit < target_times.size() && global_timer > target_times[next_note_to_hit] + 18) {
        int nv = notes[next_note_to_hit];
        int nk = (nv >= 0 && nv < 8) ? kc[nv] : -1;
        if (nk >= 0 && Renderer::is_key_down(nk)) break;

        const int key_width = 80;
        const int start_x = 1000 - (8 * key_width) / 2;
        float missed_x = start_x + (nv * key_width) + key_width / 2.0f;
        const int hit_y = 800;

        note_results[next_note_to_hit] = -1;
        spawn_rating("MISS", RED, missed_x, hit_y - 40);
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

        const int key_width = 80;
        const int start_x = 1000 - (8 * key_width) / 2;
        float note_center_x = start_x + (target_note * key_width) + key_width / 2.0f;
        const int hit_y = 800;

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
                spawn_rating(rating_str, rating_color, note_center_x, hit_y - 40);
                next_note_to_hit++;

            } else if (diff < -18 && diff >= -45) {
                spawn_rating("MISS", RED, note_center_x, hit_y - 40);
                combo = 0;
                miss_count++;
                next_note_to_hit++;
            }
        } else {
            if (std::abs(diff) <= 18) {
                float wrong_note_center_x = start_x + (current_note * key_width) + key_width / 2.0f;
                note_results[next_note_to_hit] = -1;
                spawn_rating("MISS", RED, wrong_note_center_x, hit_y - 40);
                combo = 0;
                miss_count++;
                next_note_to_hit++;
            }
        }
    }

    level = next_note_to_hit;
    compleation_level = (float)level / length;

    if (next_note_to_hit >= length && completed == 0) {
        completed = 1;
        game.player_speed = 20.0f * 0.01;

        if (score >= interaction_object->minimum_score) {
            interaction_object->beaten = true;
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
    float step = GetFrameTime() * 60.0f;
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

void Sequence::draw_progress_bar() {

    if (std::abs(bar_progress-compleation_level)>0.01 and bar_changing==0) {
        bar_changing=1;
        d_bar=(compleation_level-bar_progress)/bar_change_speed;
        if (compleation_level==0) {
            bar_color=RED;
        }

    }
    if (bar_changing>0) {
        bar_progress+=d_bar;
        bar_changing++;
        if (bar_changing>=bar_change_speed+1) {
            bar_changing=0;
            if (compleation_level==1) {
                bar_progress=1;
            }
            else if (compleation_level==0) {
                bar_progress=0;
                bar_color=GREEN;
            }

        }
    }
    std::cout<<bar_progress<<" "<<bar_changing<<std::endl;
    DrawRectangle(100,100,bar_width,bar_height,LIGHTGRAY);
    DrawRectangle(100,100,bar_width*bar_progress,bar_height,bar_color);

}
void Sequence::draw_progress_bar_chords(int x,int y,int w,int h) {
    if (std::abs(bar_progress-compleation_level)>0.01 and bar_changing==0) {
        bar_changing=1;
        d_bar=(compleation_level-bar_progress)/bar_change_speed;
        if (compleation_level==0) {
            bar_color=RED;
        }

    }
    if (bar_changing>0) {
        bar_progress+=d_bar;
        bar_changing++;
        if (bar_changing>=bar_change_speed+1) {
            bar_changing=0;
            if (compleation_level==1) {
                bar_progress=1;
            }
            else if (compleation_level==0) {
                bar_progress=0;
                bar_color=GREEN;
            }

        }
    }

    int panel_x = x;
    int panel_y = y;
    int panel_w = w;
    int panel_h = 600;

    DrawRectangleRounded(Rectangle{(float)panel_x, (float)panel_y, (float)panel_w, (float)panel_h}, 0.05f, 4, Color{ 25, 25, 35, 200 });
    DrawRectangleRoundedLines(Rectangle{(float)panel_x, (float)panel_y, (float)panel_w, (float)panel_h}, 0.05f, 4, Color{ 80, 80, 120, 120 });

    DrawText("RHYTHM COMBAT", panel_x + 30, panel_y + 30, 28, GOLD);
    DrawLine(panel_x + 30, panel_y + 70, panel_x + panel_w - 30, panel_y + 70, Color{ 80, 80, 100, 100 });

    DrawText("SONG PROGRESS", panel_x + 30, panel_y + 90, 16, Color{ 180, 180, 200, 255 });

    int bar_y = panel_y + 115;
    int bar_w = panel_w - 60;
    int bar_h = h;
    DrawRectangleRounded(Rectangle{(float)(panel_x + 30), (float)bar_y, (float)bar_w, (float)bar_h}, 0.3f, 4, Color{ 40, 40, 50, 255 });

    Color fill_color = ColorFromHSV(bar_progress * 120.0f, 0.9f, 0.9f); // dynamic color from red (0) to green (120)
    if (bar_progress > 0) {
        DrawRectangleRounded(Rectangle{(float)(panel_x + 30), (float)bar_y, (float)(bar_w * bar_progress), (float)bar_h}, 0.3f, 4, fill_color);
    }
    DrawRectangleRoundedLines(Rectangle{(float)(panel_x + 30), (float)bar_y, (float)bar_w, (float)bar_h}, 0.3f, 4, Color{ 80, 80, 100, 255 });

    std::string pct_text = std::to_string((int)(bar_progress * 100)) + "%";
    DrawText(pct_text.c_str(), panel_x + panel_w - 30 - MeasureText(pct_text.c_str(), 16), panel_y + 90, 16, WHITE);

    DrawText("SCORE", panel_x + 30, panel_y + 170, 18, Color{ 180, 180, 200, 255 });
    std::string score_str = std::to_string(score);
    DrawText(score_str.c_str(), panel_x + 30, panel_y + 195, 36, WHITE);

    if (combo > 0) {
        float combo_scale = 1.0f + 0.15f * sinf(global_timer * 0.1f);
        int combo_font_size = 32 * combo_scale;
        std::string combo_str = std::to_string(combo);

        DrawText("COMBO", panel_x + panel_w - 150, panel_y + 170, 18, Color{ 180, 180, 200, 255 });
        DrawText(combo_str.c_str(), panel_x + panel_w - 150, panel_y + 195, combo_font_size, GOLD);
    }

    DrawLine(panel_x + 30, panel_y + 260, panel_x + panel_w - 30, panel_y + 260, Color{ 80, 80, 100, 100 });

    DrawText("PERFORMANCE", panel_x + 30, panel_y + 280, 20, GOLD);

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

    int row_y = panel_y + 320;
    for (const auto& s : stats) {
        DrawText(s.label.c_str(), panel_x + 40, row_y, 18, s.col);
        std::string val_str = std::to_string(s.val);
        int val_w = MeasureText(val_str.c_str(), 18);
        DrawText(val_str.c_str(), panel_x + panel_w - 40 - val_w, row_y, 18, WHITE);
        row_y += 35;
    }

    DrawLine(panel_x + 30, panel_y + 480, panel_x + panel_w - 30, panel_y + 480, Color{ 80, 80, 100, 100 });

    if (completed) {
        DrawText("SONG COMPLETE!", panel_x + 30, panel_y + 510, 24, GREEN);
        DrawText("Press backspace or exit button.", panel_x + 30, panel_y + 545, 16, LIGHTGRAY);
    } else {
        DrawText("Reset song: BACKSPACE", panel_x + 30, panel_y + 510, 16, GRAY);
        DrawText("Press keys as they cross the line!", panel_x + 30, panel_y + 540, 16, GRAY);
    }
}
void Sequence::draw_falling_keys() {
    const int hit_y = 800;
    const int start_x = 680;
    const int key_width = 80;
    const float speed = 4.0f;

    DrawRectangle(start_x, 50, 8 * key_width, hit_y - 50, Color{ 15, 15, 20, 220 });

    for (int col = 0; col <= 8; col++) {
        DrawLine(start_x + col * key_width, 50, start_x + col * key_width, hit_y + 40, Color{ 60, 60, 80, 100 });
    }

    std::array<std::pair<int, std::string>, 8> key_bindings = {{
        { KEY_A, "A" }, { KEY_S, "S" }, { KEY_D, "D" }, { KEY_F, "F" },
        { KEY_J, "J" }, { KEY_K, "K" }, { KEY_L, "L" }, { KEY_SEMICOLON, ";" }
    }};

    for (int col = 0; col < 8; col++) {
        int x = start_x + col * key_width;
        bool is_down = Renderer::is_key_down(key_bindings[col].first);

        if (is_down) {
            DrawRectangle(x, 50, key_width, hit_y - 50, Color{ 255, 255, 255, 20 });
        }

        Rectangle target_rec = { (float)x + 6, (float)hit_y - 20, (float)key_width - 12, 40.0f };
        if (is_down) {
            DrawRectangleRounded(target_rec, 0.2f, 4, Color{ 80, 80, 120, 150 });
            DrawRectangleRoundedLines(target_rec, 0.2f, 4, WHITE);
        } else {
            DrawRectangleRounded(target_rec, 0.2f, 4, Color{ 30, 30, 45, 150 });
            DrawRectangleRoundedLines(target_rec, 0.2f, 4, Color{ 100, 100, 150, 150 });
        }

        int text_w = MeasureText(key_bindings[col].second.c_str(), 18);
        DrawText(key_bindings[col].second.c_str(), x + key_width/2 - text_w/2, hit_y - 9, 18, is_down ? WHITE : Color{ 180, 180, 220, 200 });
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

        Rectangle rec = { (float)x + 6, top_y, (float)key_width - 12, draw_h };

        Color current_draw_color = note_color;
        Color current_border_color = WHITE;
        bool draw_glow = false;

        if (j < next_note_to_hit) {
            bool was_hit = (j < note_results.size() && note_results[j] == 1);
            static const std::array<int,8> hkc = { KEY_A, KEY_S, KEY_D, KEY_F, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON };
            int h_nk = (notes[j] >= 0 && notes[j] < 8) ? hkc[notes[j]] : -1;
            bool still_holding = was_hit && (h_nk >= 0) && Renderer::is_key_down(h_nk);

            current_draw_color = was_hit ? (still_holding ? note_color : ColorAlpha(note_color, 0.6f)) : Color{ 45, 45, 55, 210 };
            current_border_color = was_hit ? (still_holding ? WHITE : ColorAlpha(WHITE, 0.35f)) : Color{ 70, 70, 80, 150 };
            draw_glow = still_holding;

        } else if (j == next_note_to_hit) {
            std::array<int,8> key_codes = { KEY_A, KEY_S, KEY_D, KEY_F, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON };
            int note_key = (notes[j] >= 0 && notes[j] < 8) ? key_codes[notes[j]] : -1;
            bool holding = (note_key >= 0) && Renderer::is_key_down(note_key);

            if (holding && bottom_y >= hit_y) {
                draw_glow = true;
            }
        }

        DrawRectangleRounded(rec, 0.2f, 4, current_draw_color);
        DrawRectangleRoundedLines(rec, 0.2f, 4, current_border_color);

        if (draw_glow) {
            DrawRectangleRounded({ (float)x + 6, (float)hit_y - 4, (float)key_width - 12, 8 }, 0.4f, 4, ColorAlpha(WHITE, 0.6f));
        }
    }

    for (auto it = ratings.begin(); it != ratings.end(); ) {
        it->pos.x += it->vel.x;
        it->pos.y += it->vel.y;
        it->life -= GetFrameTime();
        it->alpha = it->life / 1.0f;
        if (it->alpha < 0) it->alpha = 0;

        int font_size = 28 * it->scale;
        int text_w = MeasureText(it->text.c_str(), font_size);

        DrawText(it->text.c_str(), it->pos.x - text_w/2 + 2, it->pos.y + 2, font_size, ColorAlpha(BLACK, it->alpha));
        DrawText(it->text.c_str(), it->pos.x - text_w/2, it->pos.y, font_size, ColorAlpha(it->color, it->alpha));

        if (it->life <= 0) {
            it = ratings.erase(it);
        } else {
            ++it;
        }
    }

}
