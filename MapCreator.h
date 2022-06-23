#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "Window.h"
#include "GameObject.h"
#include "FilePaths.h"
#include "MapCreatorUI.h"
#include "InputDialogWindow.h"
#include "CompleteLevelInfo.h"

class MapCreator
{
    public:
        MapCreator(Window* window);
        ~MapCreator();

        void Show();
        bool EventHandler(SDL_Event e);

        void Redact (char* level = NULL);
    private:
        struct Point{
            int x, y;
            Point(int x, int y){
                this->x = x;
                this->y = y;
            }
        };
        void SetMapOffcet(int mouseX, int mouseY);

        void InitButtons();
        void MainInit();
        void MapLoad(char* path);

        void InitGameField();

        bool InputFileName();
        void SaveLevel(char* fName);

        void AddItem(Point p, bool mouseMotion);
        void AddItem(GameObject item, Point p);

        void DeleteItem(Point p);
        void DeleteItem(MapCreatorUI::Tool t);

        bool PointOnMap(Point p);

        MapCreatorUI *creatorUI;

        GameObject **map;

        Panel *gameField;
        int cellSize;

        Point *pressedPoint;

        int maxWidth, maxHeight;
        int mapOffcetX, mapOffcetY;

        char* redactLevel;
        Window* window;
};

#endif // MAPCREATOR_H
