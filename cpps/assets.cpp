#include "../headers/renderer.h"
#include <vector>
#include <string>
#include <iostream>

struct LoadedTex {
    std::string path;
    Texture2D tex;
};

std::vector<LoadedTex> load_all_images(const char* folder) {
    std::vector<LoadedTex> out;

    FilePathList files = Renderer::load_directory_files_ex(
        folder,
        ".png;.jpg;.jpeg;.bmp;.tga;.gif;.qoi",
        false
    );

    for (unsigned int i = 0; i < files.count; i++) {
        const char* p = files.paths[i];
        Texture2D t = Renderer::load_texture(p);
        if (t.id != 0) {
            out.push_back({p, t});
        } else {
            std::cout << "WARNING: Failed to load: " << p << std::endl;
        }
    }

    Renderer::unload_directory_files(files);
    return out;
}

void unload_all_images(std::vector<LoadedTex>& imgs) {
    for (auto& it : imgs) {
        if (it.tex.id != 0) Renderer::unload_texture(it.tex);
    }
    imgs.clear();
}