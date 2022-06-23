#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, int frameCount,int w, int h, int frameDelay) : Image(renderer)
{
    this->frameCount = frameCount;
    this->frameWidth = w;
    this->frameHeight = h;
    clip.x = clip.y = 0;

    curDelay = 0;
    this->frameDelay = frameDelay;
}

SpriteSheet::SpriteSheet(const SpriteSheet& obj) : Image(obj.renderer){
    clip = obj.clip;
    frameCount = obj.frameCount;
    frameWidth = obj.frameWidth;
    frameHeight = obj.frameHeight;
    frameDelay = obj.frameDelay;
    curDelay = obj.curDelay;

    startWidth = obj.startWidth;
    startHeight = obj.startHeight;
}

bool SpriteSheet::Load(char* path){
    Image::Load(path);
    clip.w = mWidth/frameCount;
    clip.h = mHeight;
}

void SpriteSheet::NextFrame(){
    if (curDelay--) return;
    else curDelay = frameDelay;

    clip.x += clip.w;
    if (clip.x >= mWidth) clip.x = 0;
}

void SpriteSheet::Render(int xOffcet, int yOffcet )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { xPos+xOffcet, yPos+yOffcet, frameWidth, frameHeight };

    //Render to screen
    SDL_RenderCopy( renderer, mTexture, &clip, &renderQuad);
}

SpriteSheet::~SpriteSheet()
{
    //dtor
}
