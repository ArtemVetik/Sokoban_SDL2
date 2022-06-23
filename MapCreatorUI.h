#ifndef MAPCREATORUI_H
#define MAPCREATORUI_H

#include "Window.h"
#include "Button.h"
#include "Panel.h"
#include "FilePaths.h"
#include "GameState.h"
#include "DialogWindow.h"
#include "BaseMenu.h"

class MapCreatorUI : public BaseMenu
{
    public:
        enum Tool{
            Twall, Tbox1, Tbox2, Tbox3, Ttarget, Tplayer, Tgarbage, Tnone,
        };
        enum State{
            SaveState, ExitState, None,
        };

        MapCreatorUI(Window* window);
        ~MapCreatorUI();

        void Show() override;
        State EventHandler(SDL_Event e);

        Tool GetSelectedTool() { return selectedTool; }
        bool PointOnTheToolsPanel(int x, int y);

    private:
        void InitButtons();
        void SetTool(Tool t, SDL_Rect rect);

        Tool selectedTool;

        Image *toolsPanel;
        Image *frame;
        Button *wallGO, *targetGO, *box1GO, *box2GO, *box3GO, *playerGO, *garbageGO;
        Button *homeButton, *saveButton;
};

#endif // MAPCREATORUI_H
