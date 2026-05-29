#pragma once
#include <string>
#include <vector>
#include "renderer.h"


std::vector<LoadedTex> load_all_images(const char* folder);
void unload_all_images(std::vector<LoadedTex>& imgs);