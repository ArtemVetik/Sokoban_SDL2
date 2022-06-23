#ifndef MOVES_H
#define MOVES_H

#include "Map.h"

// класс, проверяющий правильность ходов
class Moves
{
    public:
        Moves(Map* board);
        ~Moves();

        bool CanMove(Direction dir);

    private:
        void GetPlayerPos(int& x, int& y);
        bool CanShift(Direction dir, int playerX, int playerY);
        bool HaveEnoughEnergy(Direction dir, int playerX, int playerY, Player* player);

        Map* board;
        Player* player;
};

#endif // MOVES_H
