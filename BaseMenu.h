#ifndef BASEMENU_H_INCLUDED
#define BASEMENU_H_INCLUDED

#include "Window.h"

class BaseMenu{
    public:
        BaseMenu(Window* window){
            this->window = window;
            font = nullptr;
        }
        ~BaseMenu(){
            if (font){
                TTF_CloseFont(font);
                font = nullptr;
            }
        }

        virtual void Show() = 0;

    protected:
        TTF_Font *font;
        Window* window;
};

#endif // BASEMENU_H_INCLUDED
