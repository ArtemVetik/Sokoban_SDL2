#ifndef WALL_H
#define WALL_H

#include "Image.h"

class Wall : public Image
{
    public:
        Wall(SDL_Renderer* renderer, char* imagePath, int size);
        ~Wall();

    private:
};

#endif // WALL_H
