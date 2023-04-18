#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Constant.h"

class Texture
{
    public:
        Texture();
        ~Texture();

        void RenderTexture(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL);
        void Free();
        void LoadText(SDL_Renderer* renderer, string text, SDL_Color textColor, TTF_Font* font);

    private:
        SDL_Texture* texture;
        int width;
        int height;
};

#endif // TEXTURE_HPP
