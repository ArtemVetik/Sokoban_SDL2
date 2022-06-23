#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <cmath>
#include "Window.h"
#include "Image.h"
#include "FilePaths.h"
#include "RendererObject.h"

enum ScrollType{
    S_Horizntal,
    S_Vertical,
};

class Scrollbar : public RendererObject
{
    public:
        Scrollbar(Window* window, ScrollType type, int* val, SDL_Rect rectPos);
        ~Scrollbar();

        void SetScrollRange(int min, int max);

        void Show();
        void EventHandler(SDL_Event e);

    private:
        void MoveSlider(int dx, int dy);

        ScrollType sType;

        int* value;
        int maxVal, minVal;
        SDL_Rect sliderPos;

        Image *background, *slider;

        SDL_Point *pressedPoint;

        Window *window;
};

#endif // SCROLLBAR_H
