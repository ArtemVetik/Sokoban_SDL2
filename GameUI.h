#ifndef GAMEUI_H
#define GAMEUI_H

#include "Image.h"
#include "Panel.h"
#include "Text.h"
#include "Window.h"
#include "Player.h"
#include "SpriteSheet.h"
#include "StatusBar.h"
#include "Button.h"
#include "GameState.h"
#include "GameExceptions.h"
#include "BaseMenu.h"

class GameUI : public BaseMenu
{
    public:
        GameUI(Window* widow, Player* player, const char* lvlNameText);
        ~GameUI();

        void EventHandler(SDL_Event e);
        void Update(Uint32 timeMs);
        void Show() override;

        int GetHeight() { return panel->getHeight(); }

    private:
        Player* player; // ссылка на игрока (для получения информации об его энергии)

        SDL_Color numberColor;

        Panel* panel; // верхняя панель (hud), на которой распологаются элементы ui

        // ---------- TEXT --------
        Text* energyText;
        Text* timeText;
        Text* levelText;
        Text* lvlName;

        SDL_Rect* lvlNameRect;
        StatusBar* energyBar;
        Image* energyImage;

        SpriteSheet* clock;

        // ----------- BUTTONS --------------
        Button* homeButton;
        Button* repeatLevel;
        Button* prevButton;
};

#endif // GAMEUI_H
