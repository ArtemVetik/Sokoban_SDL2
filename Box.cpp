#include "Box.h"

Box::Box(SDL_Renderer* renderer, char* imagePath, int x, int y, int size, int weight) : Image(renderer), MovableObject(&xPos, &yPos, (weight == 1 ? 6 : weight == 2 ? 4 : 2))
{
    Load(imagePath);

    xInd = x;
    yInd = y;
    this->weight = weight;
    boxClip.x = boxClip.y = 0;
    boxClip.w = mWidth/2;
    boxClip.h = mHeight;

    mWidth = mHeight = size;
}

void Box::Shift(Direction dir){
    switch (dir){
        case Left:
            xInd--;
            break;
        case Right:
            xInd++;
            break;
        case Up:
            yInd--;
            break;
        case Down:
            yInd++;
            break;
    }
}

void Box::GreenBox(bool green){
    if (green ) boxClip.x = boxClip.w;
    else boxClip.x = 0;
}

void Box::Render(int xOffcet, int yOffcet){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { xPos + xOffcet, yPos + yOffcet, mWidth, mHeight };

    //Render to screen
    SDL_RenderCopy( renderer, mTexture, &boxClip, &renderQuad );
}

Box::~Box()
{
    free();
}
