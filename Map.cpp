#include "Map.h"

Map::Map(const char* filePath, Window* window, L_Type type) : complete(false), mapOffcetX(0), mapOffcetY(0), x0(0), y0(0)
{
    Uint32 start = SDL_GetTicks();
    this->window = window;
    player = nullptr;

    InitMapFromFile(filePath);
    FillingGround();

    UpdateBoxesState();

    int i = 0, s = 0;
    while (filePath[i] != '\0'){
        if (filePath[i] == '/') s = i;
        i++;
    }

    strcpy(levelInfo.fileName,filePath + s + 1);
    levelInfo.type = type;

    SDL_Log("Map load time: %d ms", SDL_GetTicks() - start );
}

void Map::Show(){
    playingField->Render(-mapOffcetX, -mapOffcetY);

    for (int i = 0; i < targets.Size(); i++)
        targets[i]->Render(-mapOffcetX, -mapOffcetY);

    for( int i = 0; i < boxes.Size(); i++)
        boxes[i]->Render(-mapOffcetX, -mapOffcetY);

    player->Render(-mapOffcetX, -mapOffcetY);
}

// ----------------------- MOVE ------------------

void Map::Move(Direction dir){
    if (complete) return;

    PushMapInBuffer();

    Cell second, third;
    switch (dir){
        case Left: // left
            second = playerPos.Left();
            third = playerPos.Left(2);
            break;
        case Right: // right
            second = playerPos.Right();
            third = playerPos.Right(2);
            break;
        case Up: // up
            second = playerPos.Up();
            third = playerPos.Up(2);
            break;
        case Down: // down
            second = playerPos.Down();
            third = playerPos.Down(2);
            break;
    }

    GameObject* firstCh = &board[playerPos.Y()][playerPos.X()];
    GameObject* secondCh = &board[second.Y()][second.X()];
    GameObject* thirdCh = &board[third.Y()][third.X()];

    if (GOHelper::IsBox(*secondCh)) {
        Box* box = GetBoxAt(second);
        box->Shift(dir);
        player->SetObstacle(box);

        levelInfo.pushBoxCount++;
    }
    else player->SetObstacle(NULL);
    playerPos = second;

    levelInfo.energy += GOHelper::GetBoxWeight(board[second.Y()][second.X()]);
    GOHelper::Displace(firstCh, secondCh, thirdCh);

    UpdateBoxesState();
    levelInfo.movesCount++;
}

void Map::Update(){
    for(int i = 0; i < boxes.Size(); i++){
        boxes[i]->Move(boxes[i]->GetXind()*cellSize,boxes[i]->GetYind()*cellSize);
    }
    player->Move(playerPos.X()*cellSize, playerPos.Y()*cellSize);
    player->UpdateEnergy();
    mapOffcetX = player->GetPosX() + x0 - window->getWidth()*0.5;
    mapOffcetY = player->GetPosY() - window->getHeight()*0.5;

    if (mapOffcetX + window->getWidth() > cellSize*mapWidth) mapOffcetX = cellSize*mapWidth - window->getWidth();
    if (mapOffcetX < -x0) mapOffcetX = -x0;

    if (mapOffcetY + window->getHeight() > cellSize*mapHeight) mapOffcetY = cellSize*mapHeight - window->getHeight();
    if (mapOffcetY < -y0) mapOffcetY = -y0;
}

void Map::UpdateBoxesState(){
    complete = true;

    for (int i = 0; i < boxes.Size(); i++)
        boxes[i]->GreenBox(false);

    int tX, tY;
    char obj;
    for (int i = 0; i < targets.Size(); i++)
    {
        tX = targets[i]->GetXind();
        tY = targets[i]->GetYind();
        obj = GetObjectAt(tX,tY);
        if (obj >= Box1OnTarget && obj <= Box3OnTarget){
            GetBoxAt(tX,tY)->GreenBox(true);
        }
        else complete = false;
    }
}

GameObject Map::GetObjectAt(int x, int y){
    if (x >= mapWidth || y >= mapHeight || x < 0 || y < 0){
        return (GameObject)0;
    }

    return board[y][x];
}

int Map::GetBoxWeightAt(int x, int y){
    Box* box;

    return (box = GetBoxAt(x,y)) ? box->GetWeight() : 0;
}

GameObject Map::GetObjectAt(Cell cell){
    return GetObjectAt(cell.X(), cell.Y());
}

Box* Map::GetBoxAt(int x, int y){
    for (int i = 0; i < boxes.Size(); i++){
        if (boxes[i]->GetXind() == x && boxes[i]->GetYind() == y)
            return boxes[i];
    }
    return NULL;
}

Box* Map::GetBoxAt(Cell cell){
    return GetBoxAt(cell.X(), cell.Y());
}

Map::~Map()
{
    SDL_Log("Map dtor\t%x",this);

    for (int i = 0; i < boxes.Size(); i++){
        if (boxes[i]) {
            delete (boxes[i]);
            boxes[i] = NULL;
        }
    }

    for (int i = 0; i < targets.Size(); i++){
        if (targets[i]){
            delete (targets[i]);
            targets[i] = NULL;
        }
    }
    if (player) {
        delete(player);
        player = NULL;
    }
    if (playingField){
        delete playingField;
        playingField = NULL;
    }

    if (board){
        for (int y = 0; y < mapHeight; y++){
            if (board[y]){
                delete[]board[y];
                board[y] = NULL;
            }
        }
        delete[]board;
        board = nullptr;
    }

    for (int i = 0; i < buffer.Size(); i++){
        delete(buffer[i].player);
        for (int j = 0; j < mapHeight; j++){
            delete[]buffer[i].board[j];
            buffer[i].board[j] = nullptr;
        }
        delete[]buffer[i].board;
        buffer[i].board = nullptr;
    }
}

void Map::PushMapInBuffer(){
    if (buffer.Size() == 5){
        delete(buffer[0].player);
        for (int i = 0; i < mapHeight; i++){
            delete[]buffer[0].board[i];
            buffer[0].board[i] = nullptr;
        }
        delete[]buffer[0].board;
        buffer[0].board = nullptr;
        buffer.RemoveAt(0);
    }

    Buffer tmp;
    tmp.player = new Player(*player);
    tmp.lInfo = levelInfo;
    tmp.board = new GameObject*[mapHeight];
    for (int i = 0; i < mapHeight; i++)
    {
        tmp.board[i] = new GameObject[mapWidth];
        for (int j = 0; j < mapWidth; j++) tmp.board[i][j] = board[i][j];
    }

    buffer.Add(tmp);
}

/* ----------------------- visual ------------------- */

void Map::CancelMove(){
    if (buffer.Size() == 0) return;

    for (int i = 0; i < targets.Size(); i++){
        delete(targets[i]);
        targets[i] = nullptr;
    }
    targets.Clear();

    for (int i = 0; i < boxes.Size(); i++){
        delete(boxes[i]);
        boxes[i] = nullptr;
    }
    boxes.Clear();

    Buffer tmp = buffer[buffer.Size()-1];

    player->Copy(*tmp.player);
    levelInfo = tmp.lInfo;

    SDL_Renderer* renderer = window->GetRenderer();
    Wall wall(renderer,GameObjectsPath::WallImage,cellSize);
    for (int y = 0; y < mapHeight; y++){
        for (int x = 0; x < mapWidth; x++){
            board[y][x] = tmp.board[y][x];

            switch(board[y][x]){
                case WallCh:
                    playingField->setRenderTarget(true);
                    wall.RenderCopy(renderer,NULL,new SDL_Rect{x*cellSize,y*cellSize,cellSize,cellSize});
                    playingField->setRenderTarget(false);
                    break;
                case BoxCh1:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box1Image,x,y,cellSize, 1));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case BoxCh2:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box2Image,x,y,cellSize, 2));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case BoxCh3:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box3Image,x,y,cellSize, 3));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case Box1OnTarget:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box1Image,x,y,cellSize, 1));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                    targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case Box2OnTarget:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box2Image,x,y,cellSize, 2));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                    targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case Box3OnTarget:
                    boxes.Add(new Box(renderer, GameObjectsPath::Box3Image,x,y,cellSize, 3));
                    boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                    targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case PlayerCh:
                    player->SetRenderPosition(x*cellSize,y*cellSize);
                    playerPos = Cell(x,y);
                    break;
                case PlayerOnTarget:
                    player->SetRenderPosition(x*cellSize,y*cellSize);
                    playerPos = Cell(x,y);
                    targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                    targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
                case TargetCh:
                    targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                    targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                    break;
            }
        }
    }
    UpdateBoxesState();
    delete(buffer[buffer.Size()-1].player);
        for (int i = 0; i < mapHeight; i++){
            delete[]buffer[buffer.Size()-1].board[i];
            buffer[buffer.Size()-1].board[i] = nullptr;
        }
        delete[]buffer[buffer.Size()-1].board;
        buffer[buffer.Size()-1].board = nullptr;
    buffer.RemoveAt(buffer.Size()-1);
}

void Map::InitMapFromFile(const char* filePath){
    int scr = window->getWidth() < window->getHeight() ? window->getWidth() : window->getHeight();
    float maxCellSize = 0.07*scr;

    mapWidth = mapHeight = 0;
    char sym;
    int tmpWidth = 0;
    SDL_RWops* level = SDL_RWFromFile(filePath,"r+b");
    if (!level)
        throw MapLoadException(std::string("Level file not found!\nLevel: ") + std::string(filePath));

    while(SDL_RWread(level,&sym,sizeof(sym),1)){
        if (sym == '\n') {
            mapHeight++;
            if (tmpWidth > mapWidth) mapWidth = tmpWidth;
            tmpWidth = 0;
        }
        else tmpWidth++;
    }

    cellSize = maxCellSize;

    // создаем прямоугольную матрицу
    board = new GameObject*[mapHeight];
    for (int i = 0; i < mapHeight; i++)
    {
        board[i] = new GameObject[mapWidth];
        for (int j = 0; j < mapWidth; board[i][j++] = EmptyCh);
    }

    playingField = new Panel(window->GetRenderer());
    playingField->Create(mapWidth*cellSize, mapHeight*cellSize, SDL_TEXTUREACCESS_TARGET);
    playingField->setRenderTarget(true);
    SDL_SetRenderDrawColor(window->GetRenderer(),207,232,123,200);
    SDL_RenderClear(window->GetRenderer());
    playingField->setRenderTarget(false);

    // чтение карты
    SDL_Renderer* renderer = window->GetRenderer();
    int y = 0, x = 0;
    Wall wall(renderer,GameObjectsPath::WallImage,cellSize);
    SDL_RWseek(level, 0, RW_SEEK_SET);
    while(SDL_RWread(level,&sym,sizeof(sym),1))
    {
        board[y][x] = (GameObject)sym;

        switch(sym){
            case WallCh:
                playingField->setRenderTarget(true);
                wall.RenderCopy(renderer,NULL,new SDL_Rect{x*cellSize,y*cellSize,cellSize,cellSize});
                playingField->setRenderTarget(false);
                break;
            case BoxCh1:
                boxes.Add(new Box(renderer, GameObjectsPath::Box1Image,x,y,cellSize, 1));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case BoxCh2:
                boxes.Add(new Box(renderer, GameObjectsPath::Box2Image,x,y,cellSize, 2));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case BoxCh3:
                boxes.Add(new Box(renderer, GameObjectsPath::Box3Image,x,y,cellSize, 3));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case Box1OnTarget:
                boxes.Add(new Box(renderer, GameObjectsPath::Box1Image,x,y,cellSize, 1));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case Box2OnTarget:
                boxes.Add(new Box(renderer, GameObjectsPath::Box2Image,x,y,cellSize, 2));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case Box3OnTarget:
                boxes.Add(new Box(renderer, GameObjectsPath::Box3Image,x,y,cellSize, 3));
                boxes[boxes.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case PlayerCh:
                player = new Player(renderer,cellSize);
                player->SetRenderPosition(x*cellSize,y*cellSize);
                playerPos = Cell(x,y);
                break;
            case PlayerOnTarget:
                player = new Player(renderer,cellSize);
                player->SetRenderPosition(x*cellSize,y*cellSize);
                playerPos = Cell(x,y);
                targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            case TargetCh:
                targets.Add(new Target(renderer,GameObjectsPath::TargetImage,x,y,cellSize));
                targets[targets.Size()-1]->SetRenderPosition(x*cellSize,y*cellSize);
                break;
            default:
                if (sym == '\n' || sym == ' ') break;
                SDL_RWclose(level);
                SDL_Log("Error: incorrect symbol! %s dec->%d<- char->%c<-",filePath,sym,sym);
                throw MapLoadException(std::string("Incorrect map symbols!\nLevel: ") + std::string(filePath));
                break;
        }
        if (sym == '\n'){
            board[y][x] = EmptyCh;
            x = 0;
            y++;
        }
        else x++;
    }
    SDL_RWclose(level);

    if (player == nullptr) throw MapLoadException(std::string("Player not found\nLevel: ") + std::string(filePath));
    if (targets.Size() == 0) throw MapLoadException(std::string("Targets not found\nLevel: ") + std::string(filePath));
    if (targets.Size() > boxes.Size()) throw MapLoadException(std::string("Too many targets\nLevel: ") + std::string(filePath));
}

void Map::FillingGround(){
    bool** visitedCells = new bool*[mapHeight];
    for (int y = 0; y < mapHeight; y++){
        visitedCells[y] = new bool[mapWidth];
        for (int x = 0; x < mapWidth; x++)
            visitedCells[y][x] = false;
    }

    Cell startCell(playerPos.X(), playerPos.Y());

    FillingCell(visitedCells, startCell);
}
void Map::FillingCell(bool** matrixOfVisitedCells, Cell cell){

    if (matrixOfVisitedCells[cell.Y()][cell.X()])
        return;

    matrixOfVisitedCells[cell.Y()][cell.X()] = true;
    playingField->setRenderTarget(true);
    (new Image(window->GetRenderer(),GameObjectsPath::SandGroundImage))->RenderCopy(window->GetRenderer(),NULL,new SDL_Rect{cell.X()*cellSize,cell.Y()*cellSize,cellSize,cellSize});
    playingField->setRenderTarget(false);

    GameObject upGo = GetObjectAt(cell.Up());
    GameObject downGo = GetObjectAt(cell.Down());
    GameObject leftGo = GetObjectAt(cell.Left());
    GameObject rightGo = GetObjectAt(cell.Right());

    if (GOHelper::CanStay(upGo) || GOHelper::IsBox(upGo) || GOHelper::IsPlayer(upGo))
        FillingCell(matrixOfVisitedCells,cell.Up());
    if (GOHelper::CanStay(leftGo) || GOHelper::IsBox(leftGo) || GOHelper::IsPlayer(leftGo))
        FillingCell(matrixOfVisitedCells, cell.Left());
    if (GOHelper::CanStay(downGo) || GOHelper::IsBox(downGo) || GOHelper::IsPlayer(downGo))
        FillingCell(matrixOfVisitedCells, cell.Down());
    if (GOHelper::CanStay(rightGo) || GOHelper::IsBox(rightGo) || GOHelper::IsPlayer(rightGo))
        FillingCell(matrixOfVisitedCells, cell.Right());
}
