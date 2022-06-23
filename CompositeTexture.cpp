#include "CompositeTexture.h"

RendererObject::RendererObject(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    xPos = yPos = 0;
    mWidth = mHeight = 0;
}

RendererObject::~RendererObject()
{
    //dtor
}
