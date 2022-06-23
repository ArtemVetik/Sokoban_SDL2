#include "InfoMenu.h"

InfoMenu::InfoMenu(Window* window) : BaseMenu(window), vScroll(window, ScrollType::S_Vertical, &vPos,
 SDL_Rect{(Uint32)(0.97*window->getWidth()),(Uint32)(0), (Uint32)(0.03*window->getWidth()), (Uint32)(window->getHeight())})
{
    infoText = new Text(window->GetRenderer());
    char* text = "---- ПРАВИЛА ИГРЫ ----\nУправляя игроком, Вам нужно передвинуть все ящики на специально обозначенные места. Толкать ящики можно только впереди себя. \
Уровень считается пройденным, если все ящики окажутся на своих местах. У разных ящиков отличается вес, поэтому игрок передвигает их с разной скоростью и по разному \
тратит энергию на их перемещение. Каждую секунду восстанавливается 1 единица энергии.\n\n------ КАК ИГРАТЬ -------\nУправление игроком осуществляется при помощи клавиш w a s d.\n\n\
---- РЕДАКТОР УРОВНЕЙ ----\nВ игре присутствует редактор уровней. Вы можете создать собственный уровень и попробовать пройти его в меню \"Мои уровни\". В этом меню можно удалить или \
отредактировать свой уровень, нажав на правую кнопку мыши на соответсвующем уровне.\n\n----------------------------------------------\
\n\nИгра написана на С++ с использованием библиотеки SDL2\nАвтор игры: студент 2-го курса БГТУ \"Военмех\" группы И584 Ветик Артём \nДекабрь 2019";

    font = TTF_OpenFont(FontsPath::FreeMonoFont, 50);
    infoText->Load(text, SDL_Color{66,149,255,255} ,font, 0.76*window->getWidth());
    infoText->SetRenderPosition(0.12*window->getWidth(),(Uint32)(0.12*window->getHeight()));

    title = new Text(window->GetRenderer());
    title->Load("Информация", SDL_Color{141,33,204,255} ,TTF_OpenFont(FontsPath::SerifGothicBold, 64));
    title->ChangeHeightProportionally(0.1*window->getHeight());
    title->SetRenderPosition(window->getWidth()/2 - title->getWidth()/2,0);

    exitButton = new Button(window->GetRenderer(), SDL_Rect{0,0,(Uint32)(0.04*window->getWidth()), (Uint32)(0.04*window->getWidth())});
    exitButton->LoadBackImages(UIPaths::Buttons::Back::Normal, UIPaths::Buttons::Back::Pressed, UIPaths::Buttons::Back::Highlited);

    infoPanel = new Image(window->GetRenderer());
    infoPanel->Load(UIPaths::Panel::InfoPanel);
    infoPanel->SetRenderRect(SDL_Rect{0.05*window->getWidth(),0.05*window->getHeight(), 0.9*window->getWidth(),0.9*window->getHeight()});

    vScroll.SetScrollRange(0,infoText->GetPosY()*2 + infoText->getHeight() - window->getHeight());
    vPos = 0;

    this->window = window;
}

InfoMenu::~InfoMenu()
{
    SDL_Log("InfoMenu dtor\t%x",this);
    if (exitButton){
        delete(exitButton);
        exitButton = nullptr;
    }
    if (infoText){
        delete(infoText);
        infoText = nullptr;
    }
    if (title){
        delete(title);
        title = nullptr;
    }
    if (infoPanel){
        delete(infoPanel);
        infoPanel = nullptr;
    }
}

void InfoMenu::Show(){
    title->Render();
    infoPanel->Render();
    infoText->SetClipRect(new SDL_Rect{0,vPos,infoText->getWidth(), 0.76*window->getHeight()});
    infoText->Render(0,-vPos);

    vScroll.Show();
    exitButton->Render();
}
void InfoMenu::EventHandler(SDL_Event e){
    vScroll.EventHandler(e);

    if (exitButton->EventHandler(e) == Button::Event::LB_Up)
        GameState::curState = GameState::MainMenuStatus;
}
