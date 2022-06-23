#include "MapCreatorUI.h"

MapCreatorUI::MapCreatorUI(Window* window) : BaseMenu(window)
{
    this->window = window;
    selectedTool = Tnone;

    toolsPanel = new Image(window->GetRenderer(), UIPaths::Panel::ToolsPanel);
    toolsPanel->SetRenderRect(SDL_Rect{0,window->getHeight() - 0.13*window->getHeight(),window->getWidth(), 0.13*window->getHeight() });

    frame = new Image(window->GetRenderer(), UIPaths::Images::SquareFrame);
    frame->SetRenderPosition(window->getWidth()+1,0);

    InitButtons();
}

void MapCreatorUI::InitButtons(){
    float padding = 0.025*toolsPanel->getWidth();
    float size = toolsPanel->getWidth() / (7);
    if (size > toolsPanel->getHeight()) size = 0.75*toolsPanel->getHeight();
    float x = padding, y = toolsPanel->GetPosY() + (toolsPanel->getHeight() - size)/2;

    wallGO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    wallGO->LoadBackImages(GameObjectsPath::WallImage, GameObjectsPath::WallImage, GameObjectsPath::WallImage);
    x += size + padding;

    targetGO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    targetGO->LoadBackImages(GameObjectsPath::TargetImage, GameObjectsPath::TargetImage, GameObjectsPath::TargetImage);
    x += size + padding;

    box1GO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    box1GO->LoadBackImages(GameObjectsPath::Box1Image, GameObjectsPath::Box1Image, GameObjectsPath::Box1Image);
    box1GO->CropImages(0,0,0.5,1);
    x += size + padding;

    box2GO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    box2GO->LoadBackImages(GameObjectsPath::Box2Image, GameObjectsPath::Box2Image, GameObjectsPath::Box2Image);
    box2GO->CropImages(0,0,0.5,1);
    x += size + padding;

    box3GO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    box3GO->LoadBackImages(GameObjectsPath::Box3Image, GameObjectsPath::Box3Image, GameObjectsPath::Box3Image);
    box3GO->CropImages(0,0,0.5,1);
    x += size + padding;

    playerGO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    playerGO->LoadBackImages(GameObjectsPath::PlayerImage, GameObjectsPath::PlayerImage, GameObjectsPath::PlayerImage);
    x += size + padding;

    garbageGO = new Button(window->GetRenderer(), SDL_Rect{x,y,size,size});
    garbageGO->LoadBackImages(UIPaths::Images::GarbageImage,UIPaths::Images::GarbageImage,UIPaths::Images::GarbageImage);
    x += size + padding;

    homeButton = new Button(window->GetRenderer(), SDL_Rect{0,0,0.08*window->getHeight(), 0.08*window->getHeight()});
    homeButton->LoadBackImages(UIPaths::Buttons::Home::Normal, UIPaths::Buttons::Home::Pressed, UIPaths::Buttons::Home::Highlited);

    saveButton = new Button(window->GetRenderer(), SDL_Rect{window->getWidth()-0.08*window->getHeight(),0,0.08*window->getHeight(), 0.08*window->getHeight()});
    saveButton->LoadBackImages(UIPaths::Buttons::Save::Normal,UIPaths::Buttons::Save::Pressed, UIPaths::Buttons::Save::Highlited);
}

void MapCreatorUI::Show(){
    toolsPanel->Render();

    wallGO->Render();
    targetGO->Render();
    box1GO->Render();
    box2GO->Render();
    box3GO->Render();
    playerGO->Render();
    garbageGO->Render();

    frame->Render();

    homeButton->Render();
    saveButton->Render();
}

MapCreatorUI::State MapCreatorUI::EventHandler(SDL_Event e){
    if (wallGO->EventHandler(e) == Button::Event::LB_Down) SetTool(Twall, wallGO->GetRect());
    else if (targetGO->EventHandler(e) == Button::Event::LB_Down) SetTool(Ttarget, targetGO->GetRect());
    else if (box1GO->EventHandler(e) == Button::Event::LB_Down) SetTool(Tbox1, box1GO->GetRect());
    else if (box2GO->EventHandler(e) == Button::Event::LB_Down) SetTool(Tbox2, box2GO->GetRect());
    else if (box3GO->EventHandler(e) == Button::Event::LB_Down) SetTool(Tbox3, box3GO->GetRect());
    else if (playerGO->EventHandler(e) == Button::Event::LB_Down) SetTool(Tplayer, playerGO->GetRect());
    else if (garbageGO->EventHandler(e) == Button::Event::LB_Down) SetTool(Tgarbage, garbageGO->GetRect());
    else if (saveButton->EventHandler(e) == Button::Event::LB_Up)
        return MapCreatorUI::State::SaveState;
    else if (homeButton->EventHandler(e) == Button::Event::LB_Up) {

        DlgButton *b = new DlgButton[2];
        b[0] = DlgButton{0,"Yes"};
        b[1] = DlgButton{1,"No"};

        DialogWindow dlg(window,b, 2);
        int id = dlg.Work("Предупреждение","Вы уверены, что хотите выйти?\nВсе несохранённые данные будут потеряны.");
        if (id == 0){
            return MapCreatorUI::State::ExitState;
        }
    }

    return MapCreatorUI::State::None;
}

void MapCreatorUI::SetTool(Tool t, SDL_Rect rect){
    if (selectedTool == t){
        selectedTool = Tnone;
        frame->SetRenderPosition(window->getWidth()+1,0);
        return;
    }

    selectedTool = t;
    rect.x -= 0.1*rect.w;
    rect.y -= 0.1*rect.h;
    rect.w *= 1.2;
    rect.h *= 1.2;
    frame->SetRenderRect(rect);
}

bool MapCreatorUI::PointOnTheToolsPanel(int x, int y){
    return toolsPanel->HasPoint(x,y) || saveButton->HasPoint(x,y) || homeButton->HasPoint(x,y);
}

MapCreatorUI::~MapCreatorUI()
{
    SDL_Log("MapCreatorUI dtor\t%x",this);
    if (toolsPanel){
        delete(toolsPanel);
        toolsPanel = nullptr;
    }
    if (frame){
        delete(frame);
        frame = nullptr;
    }
    if (wallGO){
        delete(wallGO);
        wallGO = nullptr;
    }
    if (targetGO){
        delete(targetGO);
        targetGO = nullptr;
    }
    if (box1GO){
        delete(box1GO);
        box1GO = nullptr;
    }
    if (box2GO){
        delete(box2GO);
        box2GO = nullptr;
    }
    if (box3GO){
        delete(box3GO);
        box3GO = nullptr;
    }
    if (playerGO){
        delete(playerGO);
        playerGO = nullptr;
    }
    if (garbageGO){
        delete(garbageGO);
        garbageGO = nullptr;
    }
    if (homeButton){
        delete(homeButton);
        homeButton = nullptr;
    }
    if (saveButton){
        delete(saveButton);
        saveButton = nullptr;
    }
    SDL_Log("END!");
}
