#include "SideItem.h"
Sideitem_health :: Sideitem_health()
{
    number = 0;
}
Sideitem_health :: ~Sideitem_health()
{

}

void Sideitem_health :: addpos(const int& x_pos)
{
    pos_list.push_back(x_pos);
}


void Sideitem_health :: Init(SDL_Renderer* screen)
{
    LoadMedia("img//health.png", screen);
    number = 3;
    if ( pos_list.size() > 0 )
    {
        pos_list.clear();
    }
    addpos(20);
    addpos(60);
    addpos(100);
}

void Sideitem_health :: show(SDL_Renderer* screen)
{
    for ( int i = 0; i < pos_list.size(); i++ )
    {
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void Sideitem_health :: delife()
{
    number--;
    pos_list.pop_back();
}

void Sideitem_health :: AddLife()
{
    number++;
    int last_pos = pos_list.back();
    last_pos += 40;
    pos_list.push_back(last_pos);
}



Sideitem_coin :: Sideitem_coin()
{
    x_pos = 0;
    y_pos = 0;
}
Sideitem_coin :: ~Sideitem_coin()
{

}

void Sideitem_coin :: Init(SDL_Renderer* screen)
{
    bool ret = LoadMedia("img//diamond.png", screen);
}

void Sideitem_coin :: Show(SDL_Renderer* screen)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    Render(screen);
}