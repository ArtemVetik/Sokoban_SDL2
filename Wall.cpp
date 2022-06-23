#include "Wall.h"


Wall::Wall(SDL_Renderer* renderer, char* imagePath, int size) : Image(renderer)
{
    Load(imagePath);
    mWidth = mHeight = size;
}

Wall::~Wall()
{

}
