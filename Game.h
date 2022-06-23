#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "GameUI.h"
#include "Moves.h"
#include "Timer.h"

class Game
{
    public:
        Game(Window* window, const char* levelFilePath, L_Type type = L_Type::L_Main);
        ~Game();

        void Show();
        void Update();
        void EventHandler(SDL_Event e);
        void CancelMove();

        bool CompleteLevel() { return map.Complete(); }
        LevelInfo GetLevelInfo();
        char* LevelFilePath() { return levelFilePath; }
    private:
        struct PlayerDirection{
            PlayerDirection(){ dir = None;}
            void SetDirection(SDL_Event e);
            Direction GetDir(){return dir;}

            private:
                Direction dir;
        } playerDir;

        Map map;
        GameUI hud;
        Moves moves;

        Timer timer;

        Image* background;
        //Panel* background;


        char *levelFilePath;
};

#endif // GAME_H
