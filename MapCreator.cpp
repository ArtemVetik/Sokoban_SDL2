#include "MapCreator.h"

MapCreator::MapCreator(Window* window) : maxWidth(20), maxHeight(20)
{
    this->window = window;
    creatorUI = nullptr;
    map = nullptr;
    MainInit();
    redactLevel = NULL;
}

void MapCreator::Redact(char* level){
    if (level) {
        MapLoad(level);
        redactLevel = level;
    }
    else redactLevel = NULL;
}

void MapCreator::MapLoad(char* path){
    SDL_RWops* reader = SDL_RWFromFile(path,"r+b");

    char sym;
    for (int y = 0; y < maxHeight; y++){
        for (int x = 0; x < maxWidth; x++){
            do SDL_RWread(reader,&sym,sizeof(sym),1); while (sym == '\n');
            AddItem((GameObject)sym, Point(x*cellSize,y*cellSize));
        }
    }

    SDL_RWclose(reader);
}

void MapCreator::MainInit(){
    pressedPoint = nullptr;
    if (creatorUI)
        delete(creatorUI);
    creatorUI = new MapCreatorUI(window);
    InitGameField();

    map = new GameObject*[maxHeight];
    for (int i = 0; i < maxHeight; i++){
        map[i] = new GameObject[maxWidth];
        for (int j = 0; j < maxWidth; j++)
            map[i][j] = EmptyCh;
    }

    mapOffcetX = (window->getWidth() > maxWidth*cellSize) ? ((-1)*(window->getWidth() - maxWidth*cellSize)/2) : 0;
    mapOffcetY = (window->getHeight() > maxHeight*cellSize) ? ((-1)*(window->getHeight() - maxHeight*cellSize)/2) : 0;
}

void MapCreator::InitGameField(){
    cellSize = 0.05*window->getWidth();

    gameField = new Panel(window->GetRenderer());
    gameField->Create(cellSize*maxWidth, cellSize*maxHeight, SDL_TEXTUREACCESS_TARGET);

    Image stone(window->GetRenderer(), GameObjectsPath::SandGroundImage);
    gameField->setRenderTarget(true);
    for(int y = 0; y < maxHeight; y++){
        for (int x = 0; x < maxWidth; x++){
            stone.RenderCopy(window->GetRenderer(), NULL, new SDL_Rect{x*cellSize, y*cellSize, cellSize, cellSize});
        }
    }
    gameField->setRenderTarget(false);
}

void MapCreator::Show(){
    gameField->Render(-mapOffcetX, -mapOffcetY);
    creatorUI->Show();
}

bool MapCreator::InputFileName(){
    char* path = NULL;
    if (redactLevel){
        SaveLevel(redactLevel);
        redactLevel = NULL;
    }
    else{
        DlgButton *b = new DlgButton[2];
        b[0] = DlgButton{0,"Сохранить"};
        b[1] = DlgButton{1,"Отмена"};

        InputDialogWindow inputDlg(window, b, 2, 0.5*window->getWidth());
        int id = inputDlg.Work("Введите название уровня", 1);

        delete[]b;
        b = nullptr;

        if (id == 1){
            return false;
        }

        const char* dir = "CustomLevels/";
        const char* lvlName = inputDlg.GetInputText();

        path = new char[SDL_utf8strlen(dir) + SDL_utf8strlen(lvlName) + 1];
        path[0] = '\0';
        strcat(path, dir);
        strcat(path,lvlName);
        SaveLevel(path);
        delete[]path;
    }

    MainInit();
    GameState::curState = GameState::MainMenuStatus;
    return true;
}

bool MapCreator::EventHandler(SDL_Event e){
    MapCreatorUI::State st = creatorUI->EventHandler(e); // UI events
    if (st == MapCreatorUI::State::ExitState){
        MainInit();
        redactLevel = NULL;
        GameState::curState = GameState::MainMenuStatus;
    }
    else if (st == MapCreatorUI::State::SaveState){
        return InputFileName();
    }

    if ((e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && creatorUI->PointOnTheToolsPanel(e.button.x, e.button.y) == false) ||
            (e.type == SDL_MOUSEMOTION && creatorUI->PointOnTheToolsPanel(e.button.x, e.button.y) == false && e.button.button == SDL_BUTTON_LEFT))
        AddItem(Point{e.button.x + mapOffcetX, e.button.y + mapOffcetY}, e.type == SDL_MOUSEMOTION); // Add item

    // change map offcet
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_RIGHT){
        pressedPoint = new Point(e.button.x + mapOffcetX, e.button.y + mapOffcetY);
    }
    else if ((e.type == SDL_MOUSEMOTION) && pressedPoint){
        SetMapOffcet(e.button.x, e.button.y);
    }
    else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT)
        pressedPoint = NULL;

    return false;
}

void MapCreator::SetMapOffcet(int mouseX, int mouseY){
     if (mouseX > 0){
        if (window->getWidth() > maxWidth*cellSize) {
            mapOffcetX = ((-1)*(window->getWidth() - maxWidth*cellSize)/2);
        }
        else {
            mapOffcetX = -mouseX + pressedPoint->x;
            if (mapOffcetX < -cellSize*2) mapOffcetX = -cellSize*2;
            else if (mapOffcetX + window->getWidth() >= maxWidth * cellSize + cellSize*2)
                mapOffcetX = maxWidth * cellSize - window->getWidth() + cellSize*2;
        }
     }
     if (mouseY > 0){
        if (window->getHeight() > maxHeight*cellSize){
            mapOffcetY = ((-1)*(window->getHeight() - maxHeight*cellSize)/2);
        }
        else {
            mapOffcetY = -mouseY + pressedPoint->y;
            if (mapOffcetY < -cellSize*2) mapOffcetY = -cellSize*2;
            else if (mapOffcetY + window->getHeight() >= maxHeight * cellSize + cellSize*2)
                mapOffcetY = maxHeight * cellSize - window->getHeight() + cellSize*2;
        }
    }
}

bool MapCreator::PointOnMap(Point p){
    return p.x >= 0 && p.x  < cellSize*maxWidth &&
            p.y >= 0 && p.y < cellSize*maxHeight;
}

void MapCreator::AddItem(Point p, bool mouseMotion){
    if (creatorUI->GetSelectedTool() == MapCreatorUI::Tnone || !PointOnMap(p)) return;

    int indX = p.x / cellSize;
    int indY = p.y / cellSize;

    Image *item;

    if (map[indY][indX] == TargetCh){
        switch (creatorUI->GetSelectedTool()){
            case MapCreatorUI::Tplayer:
                item = new Image(window->GetRenderer(), GameObjectsPath::PlayerImage);
                DeleteItem(MapCreatorUI::Tplayer);
                map[indY][indX] = PlayerOnTarget;
                break;
            case MapCreatorUI::Tbox1:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box1Image);
                item->Crop(0.5,0,1,1);
                map[indY][indX] = Box1OnTarget;
                break;
            case MapCreatorUI::Tbox2:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box2Image);
                item->Crop(0.5,0,1,1);
                map[indY][indX] = Box2OnTarget;
                break;
            case MapCreatorUI::Tbox3:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box3Image);
                item->Crop(0.5,0,1,1);
                map[indY][indX] = Box3OnTarget;
                break;
            case MapCreatorUI::Tgarbage:
                DeleteItem(p);
                return;
            default:
                return;
        }
    }
    else if (map[indY][indX] == EmptyCh){
        switch(creatorUI->GetSelectedTool()){
            case MapCreatorUI::Twall:
                map[indY][indX] = WallCh;
                item = new Image(window->GetRenderer(), GameObjectsPath::WallImage);
                break;
            case MapCreatorUI::Ttarget:
                if (mouseMotion) return;
                map[indY][indX] = TargetCh;
                item = new Image(window->GetRenderer(), GameObjectsPath::TargetImage);
                break;
            case MapCreatorUI::Tbox1:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box1Image);
                item->Crop(0,0,0.5,1);
                map[indY][indX] = BoxCh1;
                break;
            case MapCreatorUI::Tbox2:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box2Image);
                item->Crop(0,0,0.5,1);
                map[indY][indX] = BoxCh2;
                break;
            case MapCreatorUI::Tbox3:
                if (mouseMotion) return;
                item = new Image(window->GetRenderer(), GameObjectsPath::Box3Image);
                item->Crop(0,0,0.5,1);
                map[indY][indX] = BoxCh3;
                break;
            case MapCreatorUI::Tplayer:
                item = new Image(window->GetRenderer(), GameObjectsPath::PlayerImage);
                DeleteItem(MapCreatorUI::Tplayer);
                map[indY][indX] = PlayerCh;
                break;
            case MapCreatorUI::Tgarbage:
                DeleteItem(p);
                return;
            default:
                return;
        }
    }
    else if (creatorUI->GetSelectedTool() == MapCreatorUI::Tgarbage){
        DeleteItem(p);
        return;
    }
    else return;

    gameField->setRenderTarget(true);
    item->SetRenderRect(SDL_Rect{0,0,cellSize,cellSize});
    item->RenderCopy(window->GetRenderer(), NULL, new SDL_Rect{indX*cellSize, indY*cellSize, cellSize, cellSize});
    gameField->setRenderTarget(false);

    delete(item);


    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            printf("%c ",(char)map[i][j]);
        }
        printf("\n");
    }
    printf("----------------------------------");
}

void MapCreator::AddItem(GameObject obj, Point p){
    int indX = p.x / cellSize;
    int indY = p.y / cellSize;
    if (map[indY][indX] != GameObject::EmptyCh) return;

    Image *item;

    switch(obj){
        case GameObject::PlayerCh:
        case GameObject::PlayerOnTarget:
            item = new Image(window->GetRenderer(), GameObjectsPath::PlayerImage);
            DeleteItem(MapCreatorUI::Tplayer);
            break;
        case GameObject::TargetCh:
            item = new Image(window->GetRenderer(), GameObjectsPath::TargetImage);
            break;
        case GameObject::BoxCh1:
        case GameObject::Box1OnTarget:
            item = new Image(window->GetRenderer(), GameObjectsPath::Box1Image);
            item->Crop((obj == GameObject::Box1OnTarget ? 0.5 : 0),0,0.5,1);
            break;
        case GameObject::BoxCh2:
        case GameObject::Box2OnTarget:
            item = new Image(window->GetRenderer(), GameObjectsPath::Box2Image);
            item->Crop((obj == GameObject::Box2OnTarget ? 0.5 : 0),0,0.5,1);
            break;
        case GameObject::BoxCh3:
        case GameObject::Box3OnTarget:
            item = new Image(window->GetRenderer(), GameObjectsPath::Box3Image);
            item->Crop((obj == GameObject::Box3OnTarget ? 0.5 : 0),0,0.5,1);
            break;
        case GameObject::WallCh:
            item = new Image(window->GetRenderer(), GameObjectsPath::WallImage);
            break;
        default:
            return;
    }
    map[indY][indX] = obj;

    gameField->setRenderTarget(true);
    item->SetRenderRect(SDL_Rect{0,0,cellSize,cellSize});
    item->RenderCopy(window->GetRenderer(), NULL, new SDL_Rect{indX*cellSize, indY*cellSize, cellSize, cellSize});
    gameField->setRenderTarget(false);

    delete(item);
}

void MapCreator::DeleteItem(Point p){

    int indX = p.x / cellSize;
    int indY = p.y / cellSize;

    map[indY][indX] = EmptyCh;
    Image stone(window->GetRenderer(), GameObjectsPath::SandGroundImage);
    gameField->setRenderTarget(true);
    stone.SetRenderRect(SDL_Rect{0,0,cellSize,cellSize});
    stone.RenderCopy(window->GetRenderer(), NULL, new SDL_Rect{indX*cellSize, indY*cellSize, cellSize, cellSize});
    gameField->setRenderTarget(false);
}

void MapCreator::DeleteItem(MapCreatorUI::Tool t){
    int y,x;
    for (y = 0; y < maxHeight; y++){
        for (x = 0; x < maxWidth; x++){
            if (t == MapCreatorUI::Tplayer && GOHelper::IsPlayer(map[y][x])) goto p;
            else if (t == MapCreatorUI::Twall && map[y][x] == WallCh) goto p;
            else if (t == MapCreatorUI::Tbox1 && (map[y][x] == BoxCh1 || map[y][x] == Box1OnTarget)) goto p;
            else if (t == MapCreatorUI::Tbox2 && (map[y][x] == BoxCh2 || map[y][x] == Box2OnTarget)) goto p;
            else if (t == MapCreatorUI::Tbox3 && (map[y][x] == BoxCh3 || map[y][x] == Box3OnTarget)) goto p;
        }
    }
    return;
    p:
    if (GOHelper::IsTarget(map[y][x])){
        DeleteItem(Point(x*cellSize,y*cellSize));
        AddItem(GameObject::TargetCh, Point(x*cellSize,y*cellSize));
    }
    else DeleteItem(Point(x*cellSize,y*cellSize));
}

void MapCreator::SaveLevel(char* fName){
    int i = 0, k = 0;
    while (fName[i] != '\0'){
        if (fName[i] == '/') k = i;
        i++;
    }
    if (CompleteLevelInfo::HasLevelWithName(fName + k + 1, L_Type::L_Custom)){
        CompleteLevelInfo::DeleteRecord(fName + k + 1, L_Type::L_Custom);
    }

    SDL_RWops *file = SDL_RWFromFile(fName,"w+b");

    char r = '\n';
    char s;
    for (int i = 0; i < maxHeight; i++){
        for (int j = 0; j < maxWidth; j++){
            s = map[i][j];
            SDL_RWwrite(file, &s,sizeof(s), 1);
        }
        SDL_RWwrite(file,&r,sizeof(r), 1);
    }
    SDL_RWclose(file);
}

MapCreator::~MapCreator()
{
    SDL_Log("MapCreator dtor\t%x",this);
    if (map){
        for (int i = 0; i < maxHeight; i++)
            if (map[i]){
                delete[]map[i];
                map[i] = nullptr;
            }
        delete[]map;
        map = nullptr;
    }
    if (creatorUI){
        delete(creatorUI);
        creatorUI = nullptr;
    }
    if (gameField){
        delete(gameField);
        gameField = nullptr;
    }
    if (pressedPoint){
        delete(pressedPoint);
        pressedPoint = nullptr;
    }
}
