#include "bullet.h"

Bullet :: Bullet()
{
    x_val = 0;
    y_val = 0;
    is_move = false;
    bullet_type = OVAL;
    x_pos = 0;
    y_pos = 0;
    map_x = 0;
    map_y = 0;
}

Bullet :: ~Bullet()
{

}


bool Bullet :: loadBullet(SDL_Renderer* des)
{
    bool ret = false;
    if ( bullet_type == SEPHERE )
    {
        ret = LoadMedia("img//bullet2.png", des);
    }
    if ( bullet_type == GREEN_AMO )
    {
        ret = LoadMedia("img//bullet3.png", des);
    }
    if ( bullet_type == OVAL )
    {
        ret = LoadMedia("img//bullet.png", des);
    }
    if ( bullet_type == SUN )
    {
        ret = LoadMedia("img//bullet4.png", des);
    }
    if ( bullet_type == FIREBALL )
    {
        ret = LoadMedia("img//bullet5.png", des);
    }
    if ( bullet_type == PURPLE )
    {
        ret = LoadMedia("img//bullet7.png", des);
    }
    if ( bullet_type == PLAGUE_BULLET )
    {
        ret = LoadMedia("img//plague_bullet.png", des);
    }
    if ( bullet_type == BOSS_BULLET )
    {
        ret = LoadMedia("img//boss bullet.png", des);
    }
    return ret;
}


void Bullet :: handle_move(const int& x_border, const int& y_border)
{
    /*rect_.x = x_pos - map_x;
    rect_.y = y_pos - map_y;*/
    if (bullet_dir == DIR_RIGHT)
    {
        rect_.x += x_val; //x_val
        if ( rect_.x > x_border )
        {
            is_move = false;
        }
    }
    if (bullet_dir == DIR_LEFT)
    {
        rect_.x -= x_val;
        if ( rect_.x < 0 )
        {
            is_move = false;
        }
    }
    else if(bullet_dir == DIR_UP)
    {
        rect_.y -= y_val;
        if(rect_.y < 0)
        {
            is_move = false;
        }
    }
    else if(bullet_dir == DIR_UPLEFT)
    {
        rect_.x -= x_val;
        if (rect_.x < 0)
        {
            is_move = false;
        }
        rect_.y -= y_val - 10; //y_val
        if (rect_.y < 0)
        {
            is_move = false;
        }
    }
    else if(bullet_dir == DIR_UPRIGHT)
    {
        rect_.x += x_val;
        if ( rect_.x > x_border) 
        {
            is_move = false;
        }
        rect_.y -= y_val - 10;
        if ( rect_.y < 0 )
        {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_DOWNLEFT)
    {
        rect_.x -= x_val;
        if (rect_.x < 0)
        {
            is_move = false;
        }
        rect_.y += y_val - 10;
        if (rect_.y < 0)
        {
            is_move = false;
        }
    }
    else if (bullet_dir == DIR_DOWNRIGHT)
    {
        rect_.x += x_val;
        if ( rect_.x > x_border) 
        {
            is_move = false;
        }
        rect_.y += y_val - 10 ;
        if ( rect_.y < 0 )
        {
            is_move = false;
        }
    }
    else if ( bullet_dir == DIR_DOWN )
    {
        rect_.y += y_val;
        if(rect_.y > y_border)
        {
            is_move = false;
        }
    }

}