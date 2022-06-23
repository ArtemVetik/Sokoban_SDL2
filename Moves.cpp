#include "Moves.h"

Moves::Moves(Map* board)
{
    this->board = board;
    player = board->GetPlayer();
}

bool Moves::CanMove(Direction dir){
    if (player->IsMoving()) return false;

    int playerX, playerY;
    GetPlayerPos(playerX, playerY);
    return CanShift(dir, playerX,playerY) && HaveEnoughEnergy(dir, playerX, playerY, player);
}

bool Moves::CanShift(Direction dir, int playerX, int playerY){
    GameObject p1,p2;
    switch(dir){
        case Right: // right
            p1 = board->GetObjectAt(playerX+1,playerY);
            p2 = board->GetObjectAt(playerX+2,playerY);
            break;
        case Left: // left
            p1 = board->GetObjectAt(playerX-1,playerY);
            p2 = board->GetObjectAt(playerX-2,playerY);
            break;
        case Up: // up;
            p1 = board->GetObjectAt(playerX,playerY-1);
            p2 = board->GetObjectAt(playerX,playerY-2);
            break;
        case Down: // down
            p1 = board->GetObjectAt(playerX,playerY+1);
            p2 = board->GetObjectAt(playerX,playerY+2);
            break;
    }
    return GOHelper::CanStay(p1) || GOHelper::IsBox(p1) && GOHelper::CanStay(p2);
}

bool Moves::HaveEnoughEnergy(Direction dir, int playerX, int playerY, Player* player){
    switch(dir){
        case Right: // right
            return player->GetEnergy() >= board->GetBoxWeightAt(playerX+1, playerY);
        case Left: // left
            return player->GetEnergy() >= board->GetBoxWeightAt(playerX-1, playerY);
        case Up: // up;
            return player->GetEnergy() >= board->GetBoxWeightAt(playerX, playerY-1);
        case Down: // down
            return player->GetEnergy() >= board->GetBoxWeightAt(playerX, playerY+1);
    }
    return false;
}

void Moves::GetPlayerPos(int& playerX, int& playerY){
    for(int y = 0; y < board->GetHeight(); y++){
        for(int x = 0; x < board->GetWidth(); x++){

            if(GOHelper::IsPlayer(board->GetObjectAt(x,y)))
            {
                playerX = x;
                playerY = y;
            }
        }
    }
}

Moves::~Moves()
{
    //dtor
}
