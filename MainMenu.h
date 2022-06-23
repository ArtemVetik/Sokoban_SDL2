#ifndef MAINMENU_H
#define MAINMENU_H

#include "Button.h"
#include "Window.h"
#include "FilePaths.h"
#include "Image.h"
#include "GameState.h"
#include "BaseMenu.h"

class MainMenu : public BaseMenu
{
    public:
        MainMenu(Window* window);
        ~MainMenu();

        void EventHandler(SDL_Event e);
        void Show();

    private:
        Image* title;
        Button *playButton, *customMaps, *infoButton, *exitButton, *createMapButton;

};

#endif // MAINMENU_H
