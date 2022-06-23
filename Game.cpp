#include "Game.h"

Game::Game(Window* window, const char* levelFilePath, L_Type type) : map(levelFilePath, window, type), hud(window, map.GetPlayer(), map.GetLevelInfo().fileName), moves(&map)
{
    background = new Image(window->GetRenderer(), UIPaths::Background::SandBackground);
    background->ChangeHeightProportionally(window->getWidth());
    //background = new Panel(window->GetRenderer());
    //background->Create(1,1,SDL_TEXTUREACCESS_TARGET);
    //background->SetColor(207,232,123,255);
    //background->SetRenderRect(SDL_Rect{0,0,window->getWidth(), window->getHeight()});

    map.SetY0(hud.GetHeight());
    timer.Start();

    this->levelFilePath = new char[strlen(levelFilePath)+1];
    strcpy(this->levelFilePath,levelFilePath);
}

Game::~Game()
{
    SDL_Log("Game dtor\t%x",this);
    if (background){
        delete(background);
        background = nullptr;
    }
}

void Game::Show(){
    background->Render();

    map.Show();
    hud.Show();
}

void Game::Update(){
    static Uint32 time = SDL_GetTicks();
    if (SDL_GetTicks() - time < 16)
        return;
    time = SDL_GetTicks();

    map.Update();
    if (!map.Complete())
        hud.Update(timer.GetMilliseconds());
    else timer.Stop();

    if (playerDir.GetDir() != None && moves.CanMove(playerDir.GetDir())){
        map.Move(playerDir.GetDir());
    }
}

void Game::CancelMove(){
    map.CancelMove();
}

void Game::EventHandler(SDL_Event e){
    playerDir.SetDirection(e);
    hud.EventHandler(e);
}

LevelInfo Game::GetLevelInfo(){
    LevelInfo tmp = map.GetLevelInfo();
    tmp.seconds = timer.GetMilliseconds()/1000;
    return tmp;
}

void Game::PlayerDirection::SetDirection(SDL_Event e){
    if (e.type == SDL_MOUSEMOTION) return;

    switch(e.key.keysym.sym){
        case SDLK_w: // up
        case SDLK_UP:
        case 0x0446:
            if (e.type == SDL_KEYDOWN) dir = Up;
            else if (e.type == SDL_KEYUP) dir = None;
            break;
        case SDLK_a: // left
        case SDLK_LEFT:
        case 0x0444:
            if (e.type == SDL_KEYDOWN) dir = Left;
            else if (e.type == SDL_KEYUP) dir = None;
            break;
        case SDLK_s: // down
        case SDLK_DOWN:
        case 0x044b:
            if (e.type == SDL_KEYDOWN) dir = Down;
            else if (e.type == SDL_KEYUP) dir = None;
            break;
        case SDLK_d: // right
        case SDLK_RIGHT:
        case 0x0432:
            if (e.type == SDL_KEYDOWN) dir = Right;
            else if (e.type == SDL_KEYUP) dir = None;
            break;
    }
}
