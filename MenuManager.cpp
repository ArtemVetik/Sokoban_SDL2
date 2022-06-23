#include "MenuManager.h"

MenuManager::MenuManager(Window* win)
{
    GameState::curState = GameState::MainMenuStatus;
    window = win;

    mainMenu = new MainMenu(window);
    currentChoise = nullptr;
    choiseLevelMenu = new ChoiseLevelMenu(window, "Levels/", false);
    choiseCustomLevel = new ChoiseLevelMenu(window, "CustomLevels/", true);
    levelCompleteMenu = new LevelCompleteMenu(window);
    mapCreator = new MapCreator(window);
    infoMenu = new InfoMenu(window);

    exceptionMenu = nullptr;
    game = nullptr;
}

void MenuManager::Update(){
    switch(GameState::curState){
        case GameState::MainMenuStatus:
            if (game) {
                delete(game);
                game = nullptr;
            }
            break;
        case GameState::PlayState:
            game->Update();

            if (game->CompleteLevel()) {
                LevelInfo lInfo = game->GetLevelInfo();
                levelCompleteMenu->AddLevelInfo(lInfo);
                CompleteLevelInfo::AddRecord(lInfo);

                currentChoise->UpdateLevels();
                GameState::curState = GameState::LevelCompleteState;
            }
            break;
        case GameState::LevelCompleteState:
            game->Update();
            break;
    }
}
void MenuManager::Draw(){
    switch(GameState::curState){
        case GameState::MainMenuStatus:
            mainMenu->Show();
            break;
        case GameState::ChoiseLevelStatus:
            choiseLevelMenu->Show();
            break;
        case GameState::ChoiseCustomLevels:
            choiseCustomLevel->Show();
            break;
        case GameState::PrevMoveState:
        case GameState::PlayState:
            game->Show();
            break;
        case GameState::RepeatState:
            LoadGame(game->LevelFilePath());
            break;
        case GameState::LevelCompleteState:
            game->Show();
            levelCompleteMenu->Show();
            break;
        case GameState::ExceptionState:
            exceptionMenu->Show();
            break;
        case GameState::MapCreatorState:
            mapCreator->Show();
            break;
        case GameState::InfoStatus:
            infoMenu->Show();
            break;
    }
}

void MenuManager::EventHandler(SDL_Event e){
    switch(GameState::curState){
        case GameState::MainMenuStatus:
            mainMenu->EventHandler(e);
            break;
        case GameState::ChoiseLevelStatus:
            ChoiseLevelHandler((currentChoise = choiseLevelMenu)->EventHandler(e));
            break;
        case GameState::ChoiseCustomLevels:
            ChoiseLevelHandler((currentChoise = choiseCustomLevel)->EventHandler(e));
            break;
        case GameState::PlayState:
            game->EventHandler(e);
            break;
        case GameState::ExitStatus:
            window->hide();
            break;
        case GameState::LevelCompleteState:
            levelCompleteMenu->EventHandler(e);
            break;
        case GameState::NextLevelState:
            LoadGame(currentChoise->GetNextLevelPath(game->LevelFilePath()));
            break;
        case GameState::PrevMoveState:
            game->CancelMove();
            GameState::curState = GameState::PlayState;
            break;
        case GameState::ExceptionState:
            if (exceptionMenu->EventHandler(e)){
                delete(exceptionMenu);
                exceptionMenu = nullptr;
                GameState::curState = GameState::MainMenuStatus;
            }
            break;
        case GameState::MapCreatorState:
            if (mapCreator->EventHandler(e))
                choiseCustomLevel->UpdateLevels(true);
            break;
        case GameState::InfoStatus:
            infoMenu->EventHandler(e);
            break;
    }
}

void MenuManager::ChoiseLevelHandler(ChoiseLevelMenu::ReturnValue rv){
    char* path = rv.path;
    ChoiseLevelMenu::Event event = rv.event;

    if (!path) return;


    Uint32 start = SDL_GetTicks();
    switch (event){
        case ChoiseLevelMenu::Event::PlayLevel:
            LoadGame(path);
            break;
        case ChoiseLevelMenu::Event::RedactLevel:
            mapCreator->Redact(path);
            GameState::curState = GameState::MapCreatorState;
            break;
        case ChoiseLevelMenu::Event::DeleteLevel:
            remove(path);
            CompleteLevelInfo::DeleteRecord(path, L_Type::L_Custom);
            choiseCustomLevel->UpdateLevels(true);
            break;
    }

    SDL_Log("All load time: %d ms", SDL_GetTicks() - start );
}

void MenuManager::LoadGame(const char* level){
    if (game) delete(game);
    game = nullptr;

    try{
        game = new Game(window, level, currentChoise == choiseCustomLevel ? L_Type::L_Custom : L_Type::L_Main);
        GameState::curState = GameState::PlayState;
    }
    catch(MapLoadException &mapErr){
        game = nullptr;
        if (exceptionMenu) delete(exceptionMenu);
        exceptionMenu = new ExceptionMenu(window, mapErr);
        GameState::curState = GameState::ExceptionState;
    }
    catch (UILoadException &uiErr){
        game = nullptr;
        if (exceptionMenu) delete(exceptionMenu);
        exceptionMenu = new ExceptionMenu(window, uiErr);
        GameState::curState = GameState::ExceptionState;
    }
}

MenuManager::~MenuManager()
{
    SDL_Log("MenuManager dtor\t%x",this);
    if (game){
        delete(game);
        game = nullptr;
    }
    if (mainMenu){
        delete(mainMenu);
        mainMenu = nullptr;
    }
    if (choiseLevelMenu){
        delete(choiseLevelMenu);
        choiseLevelMenu = nullptr;
    }
    if (choiseCustomLevel){
        delete(choiseCustomLevel);
        choiseCustomLevel = nullptr;
    }
    currentChoise = nullptr;
    if (levelCompleteMenu){
        delete(levelCompleteMenu);
        levelCompleteMenu = nullptr;
    }
    if (exceptionMenu){
        delete(exceptionMenu);
        exceptionMenu = nullptr;
    }
    if (mapCreator){
        delete(mapCreator);
        mapCreator = nullptr;
    }
    if (infoMenu){
        delete(infoMenu);
        infoMenu = nullptr;
    }
}
