#pragma once
#include <string>
#include <vector>
#include "renderer.h"

struct LoadedTex;
struct LoadedSound;

std::vector<LoadedTex> load_all_images(const char* folder);
void unload_all_images(std::vector<LoadedTex>& imgs);

std::vector<LoadedSound> load_all_sounds(const char* folder);
void unload_all_sounds(std::vector<LoadedSound>& sounds);
