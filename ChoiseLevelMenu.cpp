#include "ChoiseLevelMenu.h"

ChoiseLevelMenu::ChoiseLevelMenu(Window* window, char* lDir, bool editable) : BaseMenu(window), countOnPage(0), curPage(0), pageCount(0)
{
    this->window = window;
    editableLevels = editable;

    LoadPaths(levelDir = lDir);
    paths.Sort();

    backButton = nextPage = prevPage = nullptr;
    font = TTF_OpenFont(FontsPath::FreeMonoFont, 64);

    InitButtons();
    UpdateLevels();
}

void ChoiseLevelMenu::LoadPaths(char* dirPath){

paths.Clear();

#ifdef _WIN32

    WIN32_FIND_DATA f;
    HANDLE h = FindFirstFile(dirPath, &f);
    if(h != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (f.cFileName[0] == '.') continue;
            paths.Add(f.cFileName);
        } while(FindNextFile(h, &f));
    }
    else
    {
        fprintf(stderr, "Error opening directory\n");
    }

#else
#ifdef __unix__

    DIR *dir = opendir(dirPath);
    int dirLen = strlen(dirPath);
    if(dir)
    {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL)
        {
            if (ent->d_name[0] == '.') continue;
            paths.Add(ent->d_name);
        }
    }
    else
    {
        fprintf(stderr, "Error opening directory\n");
    }

#else
#ifdef __TURBOC__

    struct ffblk ffblk;
    if(findfirst("*.*", &ffblk, 0) == 0)
    {
        do
        {
            paths.Add(ffblk.ff_name);
        } while(findnext(&ffblk) == 0);
    }
    else
    {
        fprintf(stderr, "Error opening directory\n");
    }

#else
#error Unsupported Implementation
#endif
#endif
#endif

    //paths.sort();
}

void ChoiseLevelMenu::InitButtons(){
    int countOnLine = 6;
    int padding = 0.05f*window->getWidth();
    int size = (window->getWidth() - padding*(countOnLine+1))/countOnLine;
    int lineCount = window->getHeight() / (padding+size);

    countOnPage = countOnLine*lineCount;
    pageCount = (paths.Size()-1) / countOnPage + 1;
    curPage = 1;

    SDL_Rect rect = SDL_Rect{padding,padding,size,size};
    SDL_Color color = SDL_Color{255,255,255,255};

    for (int i = 0; i < buttons.Size(); i++){
        delete(buttons[i]);
        buttons[i] = nullptr;
    }
    buttons.Clear();
    Button* tmp;
    int x = 0, y = 0;
    for (int i = 0; i < paths.Size(); i++){
        tmp = new Button(window->GetRenderer(), rect);
        tmp->LoadText(color,paths[i],font, true);
        tmp->LoadBackImages(UIPaths::Buttons::Square::Normal,UIPaths::Buttons::Square::Pressed,UIPaths::Buttons::Square::Highlited);
        buttons.Add(tmp);

        x++;
        rect.x += rect.w + padding;
        if (x >= countOnLine){
            rect.x = padding;
            rect.y += rect.h + padding;
            x = 0;
            y++;
            if (y >= lineCount) {
                y = 0;
                rect.y = padding;
            }
        }
    }

    if (backButton)
        delete(backButton);
    if (nextPage)
        delete(nextPage);
    if (prevPage)
        delete(prevPage);

    backButton = new Button(window->GetRenderer(),SDL_Rect{0.015*window->getWidth(),0.015*window->getWidth(),0.03*window->getWidth(), 0.03*window->getWidth()});
    backButton->LoadBackImages(UIPaths::Buttons::Back::Normal, UIPaths::Buttons::Back::Pressed, UIPaths::Buttons::Back::Highlited);

    int btnSize = 0.05*window->getHeight();
    nextPage = new Button(window->GetRenderer(),SDL_Rect{0.5*window->getWidth(), window->getHeight()-btnSize, btnSize, btnSize});
    nextPage->LoadBackImages(UIPaths::Buttons::Next::Normal,UIPaths::Buttons::Next::Pressed, UIPaths::Buttons::Next::Highlited);

    prevPage = new Button(window->GetRenderer(),SDL_Rect{0.5*window->getWidth()-btnSize, window->getHeight()-btnSize, btnSize, btnSize});
    prevPage->LoadBackImages(UIPaths::Buttons::Back::Normal,UIPaths::Buttons::Back::Pressed, UIPaths::Buttons::Back::Highlited);
}

void ChoiseLevelMenu::Show(){
    int i0 = (curPage-1)*countOnPage;
    int i1 = i0+countOnPage;
    if (i1 > paths.Size()) i1 = paths.Size();

    for (int i = i0; i < i1; i++){
        buttons[i]->Render();
    }

    backButton->Render();
    nextPage->Render();
    prevPage->Render();
}

 ChoiseLevelMenu::ReturnValue ChoiseLevelMenu::EventHandler(SDL_Event e){
    if (backButton->EventHandler(e) == Button::Event::LB_Up) {
        GameState::curState = GameState::MainMenuStatus;
        curPage = 1;
    }
    if (nextPage->EventHandler(e) == Button::Event::LB_Up){
        if (curPage+1 <= pageCount) curPage++;
    }
    else if (prevPage->EventHandler(e) == Button::Event::LB_Up){
        if (curPage - 1 > 0) curPage--;
    }

    int i0 = (curPage-1)*countOnPage;
    int i1 = i0+countOnPage;
    if (i1 > paths.Size()) i1 = paths.Size();

    Button::Event ev;
    for (int i = i0; i < i1; i++){
        ev = buttons[i]->EventHandler(e);
        if (ev == Button::Event::LB_Up)
            return ReturnValue{GetFullPath(paths[i]), ChoiseLevelMenu::Event::PlayLevel};
        else if (ev == Button::Event::RB_Up && editableLevels){
            DlgButton *b = new DlgButton[3];
            b[0] = DlgButton{0,"Редактировать"};
            b[1] = DlgButton{1,"Удалить"};
            b[2] = DlgButton{2,"Закрыть"};

            DialogWindow dlg(window, b, 3);

            std::string s1("Уровень: ");
            std::string s2(paths[i]);
            std::string title = s1 + s2;

            int id = dlg.Work((char*)title.data(), "Выберите действие для этого уровня");
            if (id < 0) id = dlg.Work("Уровень: error", "Выберите действие для этого уровня");

            if (id == 1) return ReturnValue{GetFullPath(paths[i]), ChoiseLevelMenu::Event::DeleteLevel};
            else if (id == 0) return ReturnValue{GetFullPath(paths[i]), ChoiseLevelMenu::Event::RedactLevel};
            else break;
        }
    }

    return ReturnValue{NULL, ChoiseLevelMenu::Event::PlayLevel};
}

char* ChoiseLevelMenu::GetNextLevelPath(char* curLevelPath){
    char* level = strstr(curLevelPath, levelDir) + strlen(levelDir);
    for (int i = 0; i < paths.Size(); i++){
        if (strcmp(level, paths[i]) == 0){
            if (i == paths.Size()-1) return GetFullPath(paths[0]);
            return GetFullPath(paths[i+1]);
        }
    }
    return NULL;
}

void ChoiseLevelMenu::UpdateLevels(bool reload){
    if (reload){
        LoadPaths(levelDir);
        paths.Sort();
        InitButtons();
    }

    //TTF_Font* font = TTF_OpenFont(FontsPath::FreeMonoFont, 64);
    SDL_Color color = SDL_Color{0,0,255,255};
    for (int i = 0; i < paths.Size(); i++){
        if (CompleteLevelInfo::HasLevelWithName(paths[i], editableLevels ? L_Type::L_Custom : L_Main)){
            buttons[i]->LoadText(color,paths[i],font, true);
        }
    }
}

char* ChoiseLevelMenu::GetFullPath(char* level){
    char* path = new char[strlen(levelDir) + strlen(level) + 1];
    path[0] = '\0';
    strcat(path, levelDir);
    strcat(path,level);
    return path;
}

ChoiseLevelMenu::~ChoiseLevelMenu()
{
    SDL_Log("ChoiseLevel dtor\t%x",this);
    paths.Clear();
    buttons.Clear();
    if (backButton){
        delete(backButton);
        backButton = nullptr;
    }
    if (nextPage){
        delete(nextPage);
        nextPage = nullptr;
    }
    if (prevPage){
        delete(prevPage);
        prevPage = nullptr;
    }
}
