#include "Cell.h"

Cell::Cell(){
    x = y = 0;
}

Cell::Cell(int x, int y)
{
    this->x = x;
    this->y = y;
}

Cell::~Cell()
{
    //dtor
}
