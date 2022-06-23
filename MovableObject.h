#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

// базовый класс для движущихся объектов (таких как игрок или ящик)
class MovableObject
{
    public:
        MovableObject(int* xPos, int* yPos, int defaultSpeed);
        ~MovableObject();

        void Move(int xTo, int yTo);

        int GetSpeed() { return speed; }
        bool IsMoving(){ return isMoving; }
    protected:
        int *x, *y;
        int speed, defaultSpeed;

        bool isMoving;
};

#endif // MOVABLEOBJECT_H
