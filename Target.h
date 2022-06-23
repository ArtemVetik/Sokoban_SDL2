#ifndef TARGET_H
#define TARGET_H

#include "Image.h"

class Target : public Image
{
    public:
        Target(SDL_Renderer* renderer, char* imagePath, int x, int y, int size);
        ~Target();

        int GetXind() { return xInd; }
        int GetYind() { return yInd; }
    private:
        int xInd, yInd;
};

#endif // TARGET_H
