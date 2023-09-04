#pragma once

class Texture {
public:
    Texture(const char* textureFile);
    void Use();

private:
    unsigned int _texture;
};