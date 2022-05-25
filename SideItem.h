#ifndef SIDE_ITEM_H
#define SIDE_ITEM_H

#include "commnonfunct.h"
#include "object.h"

class Sideitem_health : public object
{
public:
    Sideitem_health();
    ~Sideitem_health();

    void setnum(const int& num) {number = num;}
    void addpos(const int& x_pos);
    void show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void AddLife();
    void delife();


private:
    int number;
    vector<int> pos_list;
};

class Sideitem_coin : public object
{
public:
    Sideitem_coin();
    ~Sideitem_coin();


    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int& y) {x_pos = x; y_pos = y;}


private:
    int x_pos;
    int y_pos;
};




#endif