#include "../headers/renderer.h"
#include <vector>
#include <string>
#include <iostream>

struct LoadedTex {
    std::string path;
    Texture2D tex;
};

struct LoadedSound {
    std::string path;
    Sound sound;
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

std::vector<LoadedSound> load_all_sounds(const char* folder) {
    std::vector<LoadedSound> out;
    FilePathList files = Renderer::load_directory_files_ex(
        folder,
        ".wav;.ogg;.mp3",
        false
    );

    for (unsigned int i = 0; i < files.count; i++) {
        const char* p = files.paths[i];
        Sound s = Renderer::load_sound(p);
        if (s.stream.buffer != nullptr) {
            out.push_back({p, s});
        } else {
            std::cout << "WARNING: Failed to load sound: " << p << std::endl;
        }
    }

    Renderer::unload_directory_files(files);
    return out;
}

void unload_all_sounds(std::vector<LoadedSound>& sounds) {
    for (auto& it : sounds) {
        if (it.sound.stream.buffer != nullptr) Renderer::unload_sound(it.sound);
    }
    sounds.clear();
}
