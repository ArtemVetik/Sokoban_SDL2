#include "Player.h"

Player::Player(SDL_Renderer* renderer, int size) : RendererObject(renderer), MovableObject(&xPos, &yPos, 7), energy(20),
                                                                leftSide(renderer,3,size,size, 3), rightSide(renderer,3,size,size, 3),
                                                                faceSide(renderer,3,size,size, 3), backSide(renderer,3,size,size, 3)
{
    this->size = size;
    rightSide.Load(SpriteSheetPaths::Player::RightSide);
    leftSide.Load(SpriteSheetPaths::Player::LeftSide);
    faceSide.Load(SpriteSheetPaths::Player::FaceSide);
    backSide.Load(SpriteSheetPaths::Player::BackSide);

    curSide = &faceSide;
    isMoving = false;

    speed = defaultSpeed;
}

Player::Player(const Player& player) : RendererObject(player.renderer), MovableObject(&xPos, &yPos, 7),
                                            leftSide(player.renderer,3,player.size,player.size, 3), rightSide(player.renderer,3,player.size,player.size, 3),
                                            faceSide(player.renderer,3,player.size,player.size, 3), backSide(player.renderer,3,player.size,player.size, 3), energy(player.energy)
{
    rightSide.Load(SpriteSheetPaths::Player::RightSide);
    leftSide.Load(SpriteSheetPaths::Player::LeftSide);
    faceSide.Load(SpriteSheetPaths::Player::FaceSide);
    backSide.Load(SpriteSheetPaths::Player::BackSide);

    if (player.curSide == &player.leftSide) curSide = &leftSide;
    else if (player.curSide == &player.rightSide) curSide = &rightSide;
    else if (player.curSide == &player.faceSide) curSide = &faceSide;
    else if (player.curSide == &player.backSide) curSide = &backSide;

    mWidth = player.mWidth;
    mHeight = player.mHeight;
    xPos = player.xPos;
    yPos = player.yPos;

    defaultSpeed = player.defaultSpeed;
    speed = player.speed;
    isMoving = player.isMoving;
}

void Player::Copy(const Player& player){
    if (player.curSide == &player.leftSide) curSide = &leftSide;
    else if (player.curSide == &player.rightSide) curSide = &rightSide;
    else if (player.curSide == &player.faceSide) curSide = &faceSide;
    else if (player.curSide == &player.backSide) curSide = &backSide;

    mWidth = player.mWidth;
    mHeight = player.mHeight;
    xPos = player.xPos;
    yPos = player.yPos;

    defaultSpeed = player.defaultSpeed;
    speed = player.speed;
    isMoving = player.isMoving;

}

void Player::SetObstacle(Texture* object){

    if (object && typeid(*object) == typeid(Box))
    {
        speed = ((Box*)object)->GetSpeed();
        energy.Spend(((Box*)object)->GetWeight());
    }
    else
        speed = defaultSpeed;
}

void Player::Move(int xTo, int yTo){

    if (xTo != xPos){
        (xTo - xPos > 0) ? curSide = &rightSide : curSide = &leftSide;
        curSide->NextFrame();
    }
    else if (yTo != yPos){
        (yTo - yPos > 0) ? curSide = &faceSide : curSide = &backSide;
        curSide->NextFrame();
    }
    else{
        curSide->Reset();
    }

    MovableObject::Move(xTo, yTo);
}

void Player::Render( int xOffcet, int yOffcet){
    curSide->SetRenderPosition(xPos, yPos);
    curSide->Render(xOffcet, yOffcet);
}

Player::~Player()
{
    SDL_Log("Player dtor\t%x",this);
}
