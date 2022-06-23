#include "Target.h"

Target::Target(SDL_Renderer* renderer, char* imagePath, int x, int y, int size) : Image(renderer)
{
    Load(imagePath);

    xInd = x;
    yInd = y;

    mWidth = mHeight = size;
}

Target::~Target()
{
    //dtor
}
