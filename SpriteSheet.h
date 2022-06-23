#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "Image.h"

class SpriteSheet : public Image
{
    public:
        SpriteSheet(SDL_Renderer* renderer, int frameCount, int frameW, int frameH, int frameDelay = 0);
        SpriteSheet(const SpriteSheet& obj);
        ~SpriteSheet();

        bool Load(char* path);
        void Render(int offcetX = 0, int offcetY = 0 ) override;

        void NextFrame();
        void Reset() { clip.x = 0; };

        int GetFrameWidth() { return frameWidth; }
        int GetFrameHeight() { return frameHeight; }
    private:
        SDL_Rect clip;
        int frameCount, frameWidth, frameHeight;
        int frameDelay, curDelay;
};

#endif // SPRITESHEET_H
