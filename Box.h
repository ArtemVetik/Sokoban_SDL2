#ifndef BOX_H
#define BOX_H

#include "Image.h"
#include "MovableObject.h"

class Box : public Image, public MovableObject
{
    public:
        Box(SDL_Renderer* renderer, char* imagePath, int x, int y, int size, int weight);
        ~Box();

        void Render(int xOffcet = 0, int yOffcet = 0 ) override;

        int GetWeight(){ return weight; }
        void GreenBox(bool green);

        void Shift(Direction dir);

        int GetXind() { return xInd; }
        int GetYind() { return yInd; }
    private:
        int xInd, yInd;

        SDL_Rect boxClip;
        int weight;
};

#endif // BOX_H
