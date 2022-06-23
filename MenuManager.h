#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include "Game.h"
#include "MainMenu.h"
#include "GameState.h"
#include "ChoiseLevelMenu.h"
#include "CompleteLevelInfo.h"
#include "LevelCompleteMenu.h"
#include "GameExceptions.h"
#include "ExceptionMenu.h"
#include "MapCreator.h"
#include "InfoMenu.h"

// "мозги" программы
// тут все отображается и обрабатывается в зависимости от текущено состояния
class MenuManager
{
    public:

        MenuManager(Window* window);
        ~MenuManager();

        void Update();
        void EventHandler(SDL_Event e);
        void Draw();

    private:
        void ChoiseLevelHandler(ChoiseLevelMenu::ReturnValue rv);
        void LoadGame(const char* level);

        Game* game;
        MainMenu* mainMenu;
        ChoiseLevelMenu* choiseLevelMenu, *choiseCustomLevel, *currentChoise;
        LevelCompleteMenu *levelCompleteMenu;
        ExceptionMenu *exceptionMenu;
        MapCreator *mapCreator;
        InfoMenu *infoMenu;

        CompleteLevelInfo saveInfo;

        Window* window;
};

#endif // MENUMANAGER_H
