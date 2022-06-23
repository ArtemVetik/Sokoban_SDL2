#include "GameUI.h"

GameUI::GameUI(Window* win, Player* player, const char* lvlNameText) : BaseMenu(window)
{
    Uint32 start = SDL_GetTicks();

    this->window = win;
    this->player = player;
    font = TTF_OpenFont(FontsPath::FreeMonoFont, 72);
    if (!font) throw  UILoadException("Font load error");

    numberColor = SDL_Color{136,40,158,255};

    try{
        panel = new Panel(window->GetRenderer());
        panel->Create(window->getWidth(), window->getHeight()*0.07f, SDL_TEXTUREACCESS_TARGET);
        panel->SetRenderPosition(0,0);
        panel->SetColor(200,202,200,128);

        timeText = new Text(window->GetRenderer());
        timeText->SetRenderRect(SDL_Rect{window->getWidth()*0.47f,0,panel->getHeight(),panel->getHeight()});

        levelText = new Text(window->GetRenderer());
        levelText->Load("Level: ", SDL_Color{20,30,100,255}, font);
        levelText->SetRenderRect(SDL_Rect{window->getWidth()*0.55f,0,panel->getWidth()*0.1,panel->getHeight()});

        lvlName = new Text(window->GetRenderer());
        lvlName->Load(lvlNameText, SDL_Color{20,30,100,255}, font);
        lvlName->ChangeHeightProportionally(panel->getHeight());
        if (lvlName->getWidth() > 0.15*window->getWidth()) lvlNameRect = new SDL_Rect{0,0,0.15*window->getWidth(), lvlName->getHeight()};
        else lvlNameRect = nullptr;
        lvlName->SetScrollRect(lvlNameRect);
        lvlName->SetRenderPosition(0.65*panel->getWidth(), 0);

        energyImage = new Image(window->GetRenderer(), UIPaths::StatusBar::LightingImage);
        energyImage->SetRenderRect(SDL_Rect{0,0,panel->getHeight(),panel->getHeight()});

        energyBar = new StatusBar(window->GetRenderer(),0,20);
        energyBar->Load(UIPaths::StatusBar::Back, UIPaths::StatusBar::Filled);
        energyBar->SetRenderRect(SDL_Rect{panel->getHeight(),0.3*panel->getHeight(),0.2*panel->getWidth(),0.45*panel->getHeight()});

        energyText = new Text(window->GetRenderer());

        clock = new SpriteSheet(window->GetRenderer(), 6, 0.8*panel->getHeight(), panel->getHeight(), 5);
        clock->Load(SpriteSheetPaths::Clock);
        clock->SetRenderPosition(timeText->GetPosX() - clock->GetFrameWidth(), 0);

        homeButton = new Button(window->GetRenderer(), SDL_Rect{panel->getWidth() - panel->getHeight(),0,panel->getHeight(), panel->getHeight()});
        homeButton->LoadBackImages(UIPaths::Buttons::Home::Normal, UIPaths::Buttons::Home::Pressed, UIPaths::Buttons::Home::Highlited);

        repeatLevel = new Button(window->GetRenderer(),SDL_Rect{homeButton->GetPosX() - panel->getHeight(),0,panel->getHeight(), panel->getHeight()});
        repeatLevel->LoadBackImages(UIPaths::Buttons::Repeat::Normal,UIPaths::Buttons::Repeat::Pressed, UIPaths::Buttons::Repeat::Highlited);

        prevButton = new Button(window->GetRenderer(),SDL_Rect{repeatLevel->GetPosX() - panel->getHeight(),0,panel->getHeight(), panel->getHeight()});
        prevButton->LoadBackImages(UIPaths::Buttons::Prev::Normal,UIPaths::Buttons::Prev::Pressed, UIPaths::Buttons::Prev::Highlited);
    }
    catch(::std::bad_alloc const &ex){
        throw UILoadException("UI LOAD ERROR");
    }

    SDL_Log("GameUI load time: %d ms",SDL_GetTicks() - start);

}

void GameUI::Update(Uint32 timeMs){
    energyBar->SetValue(player->GetEnergy());

    energyText->Load((char*)(std::to_string(player->GetEnergy()).c_str()),numberColor,font);
    energyText->SetRenderRect(SDL_Rect{energyBar->GetPosX()+energyBar->getWidth()*0.4,energyBar->GetPosY(),energyBar->getHeight(),energyBar->getHeight()});

    timeText->Load((char*)(std::to_string(timeMs/1000).c_str()),numberColor,font);
    timeText->SetRenderRect(SDL_Rect{window->getWidth()*0.47f,0,panel->getHeight(),panel->getHeight()});

    clock->NextFrame();
}

void GameUI::EventHandler(SDL_Event e){
    if (homeButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::MainMenuStatus;
    if (repeatLevel->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::RepeatState;
    if (prevButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::PrevMoveState;
}

void GameUI::Show(){
    panel->Render();

    energyImage->Render();
    energyBar->Render();
    energyText->Render();

    clock->Render();
    timeText->Render();

    homeButton->Render();
    repeatLevel->Render();
    prevButton->Render();

    levelText->Render();
    lvlName->Render();
}

GameUI::~GameUI()
{
    SDL_Log("GameUI dtor\t%x",this);

    if (panel){
        delete(panel);
        panel = nullptr;
    }
    if (energyText){
        delete(energyText);
        energyText = nullptr;
    }
    if (timeText){
        delete(timeText);
        timeText = nullptr;
    }
    if (levelText){
        delete(levelText);
        levelText = nullptr;
    }
    if (lvlName){
        delete(lvlName);
        lvlName = nullptr;
    }
    if (energyBar){
        delete(energyBar);
        energyBar = nullptr;
    }
    if (energyImage){
        delete(energyImage);
        energyImage = nullptr;
    }
    if (clock){
        delete(clock);
        clock = nullptr;
    }
    if (homeButton){
        delete(homeButton);
        homeButton = nullptr;
    }
    if (repeatLevel){
        delete(repeatLevel);
        repeatLevel = nullptr;
    }
    if (prevButton){
        delete(prevButton);
        prevButton = nullptr;
    }
}
