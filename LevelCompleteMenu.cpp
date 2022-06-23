#include "LevelCompleteMenu.h"

LevelCompleteMenu::LevelCompleteMenu(Window* window) : BaseMenu(window)
{
    this->window = window;
    font = TTF_OpenFont(FontsPath::FreeMonoFont, 64);

    panel = new Image(window->GetRenderer(), UIPaths::Panel::ResultPanel);
    panel->SetRenderRect(SDL_Rect{0.05*window->getWidth(), 0.2*window->getHeight(),0.9*window->getWidth(),0.7*window->getHeight()});

    int btnSize = 0.07*panel->getWidth();
    int x0 = panel->GetPosX();
    int y = panel->GetPosY() + panel->getHeight() - btnSize*1.1;

    homeButton = new Button(window->GetRenderer(),SDL_Rect{x0 + 0.5*panel->getWidth()-btnSize/2,y, btnSize, btnSize});
    nextLevelButton = new Button(window->GetRenderer(), SDL_Rect{x0 + 0.75*panel->getWidth()-btnSize/2,y,btnSize,btnSize});
    repeatButton = new Button(window->GetRenderer(),SDL_Rect{x0 + 0.25*panel->getWidth()-btnSize/2, y, btnSize, btnSize});

    homeButton->LoadBackImages(UIPaths::Buttons::Home::Normal, UIPaths::Buttons::Home::Pressed, UIPaths::Buttons::Home::Highlited);
    repeatButton->LoadBackImages(UIPaths::Buttons::Repeat::Normal, UIPaths::Buttons::Repeat::Pressed, UIPaths::Buttons::Repeat::Highlited);
    nextLevelButton->LoadBackImages(UIPaths::Buttons::NextRound::Normal,UIPaths::Buttons::NextRound::Pressed,UIPaths::Buttons::NextRound::Highlited);

    title = new Text(window->GetRenderer());
    title->Load("Статистика", SDL_Color{141,33,204,255},TTF_OpenFont(FontsPath::SerifGothicBold, 80));
    title->ChangeHeightProportionally(0.1*window->getHeight());
    title->SetRenderPosition(window->getWidth()/2 - title->getWidth()/2, 0.1*window->getHeight());
    oldStatsText = newStatsText = statsInfo = nullptr;
}

void LevelCompleteMenu::AddLevelInfo(LevelInfo info){
    if (oldStatsText)
        delete(oldStatsText);
    if (newStatsText)
        delete(newStatsText);
    if (statsInfo)
        delete(statsInfo);

    LevelInfo oldInfo = CompleteLevelInfo::GetInfo(info.fileName, info.type);

    SDL_Color textColor = {204,132,0,255};

    oldStatsText = new Text(window->GetRenderer());
    std::string t1 = std::string("Предыдущая\n\n   ") + std::to_string(oldInfo.movesCount) + std::string("\n\n   ") +
     std::to_string(oldInfo.pushBoxCount) + std::string("\n\n   ") + std::to_string(oldInfo.energy) + std::string("\n\n   ") + std::to_string(oldInfo.seconds);
    oldStatsText->Load(t1.data(), textColor, font, panel->getWidth());
    oldStatsText->SetRenderPosition(panel->GetPosX() + 0.47*panel->getWidth(), panel->GetPosY()+0.05*panel->getHeight());
    oldStatsText->ChangeHeightProportionally(0.7*panel->getHeight());

    newStatsText = new Text(window->GetRenderer());
    std::string t2 = std::string("Новая\n\n  ") + std::to_string(info.movesCount) + std::string("\n\n  ") +
     std::to_string(info.pushBoxCount) + std::string("\n\n  ") + std::to_string(info.energy) + std::string("\n\n  ") + std::to_string(info.seconds);
    newStatsText->Load(t2.data(), textColor, font, panel->getWidth());
    newStatsText->SetRenderPosition(panel->GetPosX() + 0.8*panel->getWidth(), panel->GetPosY()+0.05*panel->getHeight());
    newStatsText->ChangeHeightProportionally(0.7*panel->getHeight());

    statsInfo = new Text(window->GetRenderer());
    statsInfo->Load("Всего ходов\n\nСдвинуто ящиков\n\nПотрачено энергии\n\nВремя", textColor, font, panel->getWidth());
    statsInfo->SetRenderPosition(panel->GetPosX()+0.02*panel->getWidth(), panel->GetPosY() + 0.22*panel->getHeight());
    statsInfo->ChangeHeightProportionally(0.5*panel->getHeight());
}

void LevelCompleteMenu::EventHandler(SDL_Event e){
    if (homeButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::MainMenuStatus;
    if (nextLevelButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::NextLevelState;
    if (repeatButton->EventHandler(e) == Button::Event::LB_Up) GameState::curState = GameState::RepeatState;
}

void LevelCompleteMenu::Show(){
    panel->Render();
    homeButton->Render();
    repeatButton->Render();
    nextLevelButton->Render();

    title->Render();
    if (statsInfo) statsInfo->Render();
    if (oldStatsText) oldStatsText->Render();
    if (newStatsText) newStatsText->Render();
}

LevelCompleteMenu::~LevelCompleteMenu()
{
    SDL_Log("LevelCompleteMenu dtor\t%x",this);
    if (nextLevelButton){
        delete(nextLevelButton);
        nextLevelButton = nullptr;
    }
    if (homeButton){
        delete(homeButton);
        homeButton = nullptr;
    }
    if (repeatButton){
        delete(repeatButton);
        repeatButton = nullptr;
    }
    if (panel){
        delete(panel);
        panel = nullptr;
    }
    if (oldStatsText){
        delete(oldStatsText);
        oldStatsText = nullptr;
    }
    if (newStatsText){
        delete(newStatsText);
        newStatsText = nullptr;
    }
    if (statsInfo){
        delete(statsInfo);
        statsInfo = nullptr;
    }
    if (title){
        delete(title);
        title = nullptr;
    }
}
