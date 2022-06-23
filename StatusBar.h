#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "RendererObject.h"
#include "Image.h"

class StatusBar : public RendererObject
{
    public:
        StatusBar(SDL_Renderer* renderer, int minVal, int maxVal);
        ~StatusBar();

        bool Load(char* backImage, char* filledImage);
        void Render( int xOffcet = 0, int yOffcet = 0);

        void SetValue(int value);

        void SetRenderPosition(int x, int y) override;
        void SetRenderRect(SDL_Rect rect) override;

    private:
        void UpdateFilledImageRect();

        int minValue, maxValue, curValue;
        SDL_Rect *rect;

        Image *backImage, *filledImage;
};

#endif // STATUSBAR_H
