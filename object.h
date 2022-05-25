#ifndef OBJECT_H_
#define OBJECT_H_

#include "commnonfunct.h"
#include "textobj.h"

const int menu_item = 2;
class object
{
    public:
    object();
    ~object();
    void setrect( const int& x, const int& y ) {rect_.x = x, rect_.y = y;}
    SDL_Rect getrect () const { return rect_;}
    SDL_Texture* getObject () const {return p_object;}
    bool LoadMedia(string path, SDL_Renderer* &re);
    void Render( SDL_Renderer* des, SDL_Rect* clip = NULL  );
    void Free();

    int ShowMenu(SDL_Renderer*screen, TTF_Font* font);

    protected:
    SDL_Texture* p_object;
    SDL_Rect rect_;
};




#endif