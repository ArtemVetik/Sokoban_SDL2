#include "ExceptionMenu.h"

ExceptionMenu::ExceptionMenu(Window* window,std::exception& gameException) : BaseMenu(window)
{
    this->window = window;

    font = TTF_OpenFont(FontsPath::FreeMonoFont, 64);

    exceptionText = new Text(window->GetRenderer());
    exceptionText->Load(gameException.what(), SDL_Color{100,100,100,255}, font,0.9*window->getWidth());
    exceptionText->SetRenderRect(SDL_Rect{0.05*window->getWidth(),0.2*window->getHeight(),0.9*window->getWidth(), window->getHeight()*0.5});

    title = new Text(window->GetRenderer());
    title->Load("Ошибка",SDL_Color{255,255,255,255},font);
    title->ChangeHeightProportionally(0.15*window->getHeight());
    title->SetRenderPosition(window->getWidth()/2-title->getWidth()/2, 0);

    int btnSize = 0.08*window->getWidth();
    int btnY = 0.7*window->getHeight();
    returnButton = new Button(window->GetRenderer(), SDL_Rect{window->getWidth()/2-btnSize/2, btnY, btnSize, btnSize});
    returnButton->LoadBackImages(UIPaths::Buttons::Home::Normal, UIPaths::Buttons::Home::Pressed, UIPaths::Buttons::Home::Highlited);
}

void ExceptionMenu::Show(){
    title->Render();
    exceptionText->Render();
    returnButton->Render();
}

bool ExceptionMenu::EventHandler(SDL_Event e){
    if (returnButton->EventHandler(e) == Button::Event::LB_Up) return true;
}

ExceptionMenu::~ExceptionMenu()
{
    SDL_Log("ExceptionMenu dtor\t%x",this);
    if (returnButton){
        delete(returnButton);
        returnButton = nullptr;
    }
    if (exceptionText){
        delete(exceptionText);
        exceptionText = nullptr;
    }
    if (title){
        delete(title);
        title = nullptr;
    }
}
