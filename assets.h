#pragma once
#include <string>
#include <vector>
#include "raylib.h"


std::vector<LoadedTex> load_all_images(const char* folder);
void unload_all_images(std::vector<LoadedTex>& imgs);