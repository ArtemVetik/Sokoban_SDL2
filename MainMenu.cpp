#include "MainMenu.h"

MainMenu::MainMenu(Window* window) : BaseMenu(window)
{
    this->window = window;
    SDL_Color normal = SDL_Color{100,0,100,255};
    SDL_Color pressed = SDL_Color{50,50,200,255};
    SDL_Color highlited = SDL_Color{255,255,255,255};
    font = TTF_OpenFont(FontsPath::FreeMonoFont, 64);

    int x = 0.4*window->getWidth();
    int y = 0.25*window->getHeight();
    int w = 0.2*window->getWidth();
    int h = 0.1*window->getHeight();
    int distanceBetween = 0.05*window->getHeight();

    title = new Image(window->GetRenderer(), "Images/sokoban.bmp");
    title->ChangeHeightProportionally(0.15*window->getHeight());
    title->SetRenderPosition(window->getWidth()/2 - title->getWidth()/2, 0.07*window->getHeight());

    playButton = new Button(window->GetRenderer(), SDL_Rect{x,y,w, h});
    playButton->LoadBackImages(UIPaths::Buttons::Round::Normal, UIPaths::Buttons::Round::Pressed, UIPaths::Buttons::Round::Highlited);
    playButton->LoadText(normal, pressed, highlited,"Играть",font);
    y += h + distanceBetween;

    customMaps = new Button(window->GetRenderer(), SDL_Rect{x,y,w, h});
    customMaps->LoadBackImages(UIPaths::Buttons::Round::Normal, UIPaths::Buttons::Round::Pressed, UIPaths::Buttons::Round::Highlited);
    customMaps->LoadText(normal, pressed, highlited,"Мои уровни",font);
    y += h + distanceBetween;

    createMapButton = new Button(window->GetRenderer(), SDL_Rect{x,y,w,h});
    createMapButton->LoadBackImages(UIPaths::Buttons::Round::Normal, UIPaths::Buttons::Round::Pressed, UIPaths::Buttons::Round::Highlited);
    createMapButton->LoadText(normal, pressed, highlited,"Редактор уровней",font);
    y += h + distanceBetween;

    infoButton = new Button(window->GetRenderer(), SDL_Rect{x,y,w, h});
    infoButton->LoadBackImages(UIPaths::Buttons::Round::Normal, UIPaths::Buttons::Round::Pressed, UIPaths::Buttons::Round::Highlited);
    infoButton->LoadText(normal, pressed, highlited,"Информация",font);
    y += h + distanceBetween;

    exitButton = new Button(window->GetRenderer(), SDL_Rect{x,y,w, h});
    exitButton->LoadBackImages(UIPaths::Buttons::Round::Normal, UIPaths::Buttons::Round::Pressed, UIPaths::Buttons::Round::Highlited);
    exitButton->LoadText(normal, pressed, highlited,"Выход",font);
}

void MainMenu::EventHandler(SDL_Event e){
    if (playButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::States::ChoiseLevelStatus;
    if (customMaps->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::States::ChoiseCustomLevels;
    if (infoButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::InfoStatus;
    if (createMapButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::MapCreatorState;
    if (exitButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::ExitStatus;
}
void MainMenu::Show(){
    title->Render();

    playButton->Render();
    customMaps->Render();
    infoButton->Render();
    createMapButton->Render();
    exitButton->Render();
}

MainMenu::~MainMenu()
{
    SDL_Log("MainMenu dtor\t%x",this);
    if (title){
        delete(title);
        title = nullptr;
    }
    if (playButton){
        delete(playButton);
        playButton = nullptr;
    }
    if (customMaps){
        delete(customMaps);
        customMaps = nullptr;
    }
    if (infoButton){
        delete(infoButton);
        infoButton = nullptr;
    }
    if (exitButton){
        delete(exitButton);
        exitButton = nullptr;
    }
    if (createMapButton){
        delete(createMapButton);
        createMapButton = nullptr;
    }
}
