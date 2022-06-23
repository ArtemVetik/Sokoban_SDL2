#ifndef COMPOSITETEXTURE_H
#define COMPOSITETEXTURE_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include "RendererObject.h"

#include <iostream>

class RendererObject
{
    public:
        RendererObject(SDL_Renderer* renderer);
        ~RendererObject();

        void SetRenderPosition(int x, int y);
        void SetRenderRect(SDL_Rect rect);

    protected:
        SDL_Renderer* renderer;

        //Image dimensions
        int mWidth;
        int mHeight;
        int xPos, yPos;
};

#endif // COMPOSITETEXTURE_H
