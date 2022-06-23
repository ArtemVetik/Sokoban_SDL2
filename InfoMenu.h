#ifndef INFOMENU_H
#define INFOMENU_H

#include "Scrollbar.h"
#include "GameState.h"
#include "Text.h"
#include "Button.h"
#include "Panel.h"
#include "FilePaths.h"
#include "BaseMenu.h"

class InfoMenu : public BaseMenu
{
    public:
        InfoMenu(Window* window);
        ~InfoMenu();

        void Show() override;
        void EventHandler(SDL_Event e);
    private:
        Scrollbar vScroll;
        int vPos;

        Button *exitButton;
        Text *infoText, *title;

        Image *infoPanel;
};

#endif // INFOMENU_H
