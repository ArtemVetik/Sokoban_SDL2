#include "StatusBar.h"

StatusBar::StatusBar(SDL_Renderer* renderer, int minVal, int maxVal) : RendererObject(renderer)
{
    this->minValue = minVal;
    this->maxValue = maxVal;
    curValue = maxVal;

    rect = new SDL_Rect{0,0,mWidth,mHeight};

    backImage = filledImage = NULL;
}

bool StatusBar::Load(char* backImagePath, char* filledImagePath){
    backImage = new Image(renderer,backImagePath);
    filledImage = new Image(renderer, filledImagePath);

    backImage->SetRenderRect(SDL_Rect{xPos,yPos,mWidth,mHeight});
    filledImage->SetRenderRect(backImage->GetRect());
}

void StatusBar::Render( int xOffcet, int yOffcet){
    filledImage->RenderClip(rect);
    backImage->Render();
}

void StatusBar::SetRenderPosition(int x, int y){
    xPos = x;
    yPos = y;
    backImage->SetRenderPosition(x,y);
    filledImage->SetRenderPosition(x,y);
}
void StatusBar::SetRenderRect(SDL_Rect rect){
    xPos = rect.x;
    yPos = rect.y;
    mWidth = rect.w;
    mHeight = rect.h;

    this->rect->w = mWidth;
    this->rect->h = mHeight;

    backImage->SetRenderRect(rect);
    filledImage->SetRenderRect(rect);

    UpdateFilledImageRect();
}

void StatusBar::UpdateFilledImageRect(){
    float curPercent = (float)curValue/(maxValue-minValue);
    rect->w = curPercent*mWidth;
    filledImage->SetRenderRect(SDL_Rect{xPos,yPos,rect->w,rect->h});
}

void StatusBar::SetValue(int value){
    if (curValue == value) return;

    if (value > maxValue) curValue = maxValue;
    else if (value < minValue) curValue = minValue;
    else curValue = value;

    UpdateFilledImageRect();
}

StatusBar::~StatusBar()
{
    SDL_Log("StatusBar dtor\t%x",this);
    if (backImage){
        delete backImage;
        backImage = NULL;
    }
    if (filledImage){
        delete filledImage;
        filledImage = NULL;
    }
}
