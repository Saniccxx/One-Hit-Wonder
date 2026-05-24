#include "raylib.h"
#include <vector>
#include <string>

struct LoadedTex {
    std::string path;
    Texture2D tex;
};

std::vector<LoadedTex> load_all_images(const char* folder) {
    std::vector<LoadedTex> out;

    FilePathList files = LoadDirectoryFilesEx(
        folder,
        ".png;.jpg;.jpeg;.bmp;.tga;.gif;.qoi",
        false
    );

    for (unsigned int i = 0; i < files.count; i++) {
        const char* p = files.paths[i];
        Texture2D t = LoadTexture(p);
        if (t.id != 0) {
            out.push_back({p, t});
        } else {
            TraceLog(LOG_WARNING, "Failed to load: %s", p);
        }
    }

    UnloadDirectoryFiles(files);
    return out;
}

void unload_all_images(std::vector<LoadedTex>& imgs) {
    for (auto& it : imgs) {
        if (it.tex.id != 0) UnloadTexture(it.tex);
    }
    imgs.clear();
}