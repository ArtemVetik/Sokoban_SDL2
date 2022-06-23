#ifndef LEVELCOMPLETEMENU_H
#define LEVELCOMPLETEMENU_H

#include "Window.h"
#include "Button.h"
#include "Image.h"
#include "Panel.h"
#include "GameState.h"
#include "FilePaths.h"
#include "CompleteLevelInfo.h"
#include "BaseMenu.h"

class LevelCompleteMenu : public BaseMenu
{
    public:
        LevelCompleteMenu(Window* window);
        ~LevelCompleteMenu();

        void Show() override;
        void EventHandler(SDL_Event e);
        void AddLevelInfo(LevelInfo info);
    private:
        Button *nextLevelButton, *homeButton, *repeatButton;
        Image *panel;
        Text *oldStatsText, *newStatsText, *statsInfo, *title;
};

#endif // LEVELCOMPLETEMENU_H
