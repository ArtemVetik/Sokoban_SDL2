#include "MovableObject.h"
#include <SDL2/SDL.h>
MovableObject::MovableObject(int* xPos, int* yPos, int speed)
{
    x = xPos;
    y = yPos;
    this->defaultSpeed = this->speed = speed;
}

MovableObject::~MovableObject()
{
    //dtor
}

void MovableObject::Move(int xTo, int yTo){
    char sign;
    isMoving = true;
    if (*x != xTo){
        sign = xTo - *x > 0 ? 1 : -1;
        if ((xTo - *x)*sign < speed) {
            *x = xTo;
            isMoving = false;
        }
        else *x += speed*sign;
    }
    else if (*y != yTo){
        sign = yTo - *y > 0 ? 1 : -1;
        if ((yTo - *y)*sign < speed) {
            *y = yTo;
            isMoving = false;
        }
        else *y += speed*sign;
    }
    else {
        isMoving = false;
    }
}
