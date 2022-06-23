#ifndef MAP_H
#define MAP_H

#include "Wall.h"
#include "Box.h"
#include "Window.h"
#include "Player.h"
#include "Cell.h"
#include "Target.h"
#include "Panel.h"
#include "List.h"
#include "GameObject.h"
#include "FilePaths.h"
#include "LevelInfo.h"
#include "GameExceptions.h"

class Map
{
    public:
        Map(const char* filePath, Window* window, L_Type type);
        ~Map();

        void Move(Direction dir);
        void Show();
        void Update();
        void CancelMove();

        GameObject GetObjectAt(int x, int y);
        GameObject GetObjectAt(Cell cell);
        int GetBoxWeightAt(int x, int y);

        int GetWidth(){return mapWidth;}
        int GetHeight(){return mapHeight;}
        Player* GetPlayer() { return player;}

        void SetX0(int x0) { this->x0 = x0; }
        void SetY0(int y0) { this->y0 = y0; }

        bool Complete() { return complete; }
        LevelInfo GetLevelInfo() { return levelInfo; }

    private:
        void InitMapFromFile(const char* filePath);
        Box* GetBoxAt(int x, int y);
        Box* GetBoxAt(Cell cell);
        void UpdateBoxesState();
        void FillingGround();
        void FillingCell(bool** matrixOfVisitedCells, Cell cell);
        void PushMapInBuffer();

        GameObject** board; // матрица символов игрового поля
        Panel* playingField;

        List<Target*> targets; // указатели на цели для ящиков
        List<Box*> boxes;
        Player* player;

        LevelInfo levelInfo;

        Window* window; // окно, на котором отрисовывается карта
        Cell playerPos; // позиция игрока

        int mapWidth, mapHeight;
        int cellSize;

        int mapOffcetX, mapOffcetY, x0, y0;

        bool complete;

        //---------- buffer --------------
        struct Buffer{
            Player* player;
            GameObject** board;
            LevelInfo lInfo;
        };
        List<Buffer> buffer;
};

#endif // MAP_H
