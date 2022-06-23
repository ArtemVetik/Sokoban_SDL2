#ifndef EXCEPTIONMENU_H
#define EXCEPTIONMENU_H

#include "Window.h"
#include "Text.h"
#include "Button.h"
#include "FilePaths.h"
#include "GameState.h"
#include "BaseMenu.h"

// отображает меню при ошибке
class ExceptionMenu : public BaseMenu
{
    public:
        ExceptionMenu(Window* window, std::exception& exceptionInfo);
        ~ExceptionMenu();

        void Show() override;
        bool EventHandler(SDL_Event e);

    private:
        Button* returnButton;
        Text* exceptionText, *title;
};

#endif // EXCEPTIONMENU_H
