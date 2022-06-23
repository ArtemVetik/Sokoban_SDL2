#ifndef PLAYER_H
#define PLAYER_H

#include "Image.h"
#include "MovableObject.h"
#include "Box.h"
#include "Energy.h"
#include "SpriteSheet.h"
#include "GameObject.h"
#include "FilePaths.h"

class Player : public RendererObject, public MovableObject
{
    public:
        Player(SDL_Renderer* renderer, int size);
        Player(const Player& player);
        ~Player();

        void Copy(const Player& player);

        void Render( int xOffcet = 0, int yOffcet = 0);

        void Move(int xTo, int yTo);
        void UpdateEnergy() { energy.Update(); }

        void SetObstacle(Texture* object);

        int GetEnergy() { return energy.GetEnergy(); }
    private:
        SpriteSheet rightSide, leftSide, faceSide, backSide;
        SpriteSheet* curSide;

        Energy energy;
        int size;
};

#endif // PLAYER_H
