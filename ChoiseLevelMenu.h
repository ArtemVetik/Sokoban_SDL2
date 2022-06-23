#ifndef CHOISELEVELMENU_H

#include "Button.h"
#include <string>
#include <stdio.h>
#include "FilePaths.h"
#include "List.h"
#include "GameState.h"
#include "CompleteLevelInfo.h"
#include "DialogWindow.h"
#include "BaseMenu.h"

#ifdef _WIN32
#include <windows.h>
#else
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#else
#ifdef __TURBOC__
#include <dir.h>
#else
#error Unsupported Implementation
#endif
#endif
#endif


#define CHOISELEVELMENU_H


class ChoiseLevelMenu : public BaseMenu
{
    public:
        enum Event{
            PlayLevel, RedactLevel, DeleteLevel,
        };
        struct ReturnValue{
            char* path;
            Event event;
        };

        ChoiseLevelMenu(Window* window, char* lDir, bool editable);
        ~ChoiseLevelMenu();

        void Show() override;
        ReturnValue EventHandler(SDL_Event e);

        char* GetNextLevelPath(char* curLevelPath);
        void UpdateLevels(bool reload = false);

    private:
        void LoadPaths(char* dir);
        void InitButtons();
        char* GetFullPath(char* level);

        List<char*> paths;
        List<Button*> buttons;

        Button *backButton;
        Button *nextPage, *prevPage;

        int countOnPage, curPage, pageCount;

        bool editableLevels;
        char* levelDir;
};

#endif // CHOISELEVELMENU_H
