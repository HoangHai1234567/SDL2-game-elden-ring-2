#include "boss.h"
Bossobject :: Bossobject()
{
    width_frame = 0;
    height_frame = 0;

    x_val = 0;
    y_val = 0;
    
    x_pos = 0;
    y_pos = 0;

    on_ground = 0;

    comeback_time = 0;
    frame_ = 0;

    dealay_frame = 5;
    count = 0;
}

Bossobject :: ~Bossobject()
{

}

bool Bossobject :: LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = object :: LoadMedia(path, screen);
    if (ret == true)
    {
        width_frame = rect_.w/BOSS_FRAME;
        height_frame = rect_.h;
    }

    return ret;
}

void Bossobject :: setclip()
{
    if ( width_frame > 0 && height_frame > 0 )
    {
        for ( int i = BOSS_FRAME - 1; i >= 0; i-- )
        {
            frame_clip[i].x = width_frame*i;
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
}

void Bossobject :: Show(SDL_Renderer* des)
{
    if ( comeback_time == 0 )
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        if ( dealay_frame >= 5 )
        {
            frame_ ++;
            dealay_frame = 0;
        }
        dealay_frame ++;

        if (frame_ >= BOSS_FRAME)
        {
            frame_ = 0;
        }
        SDL_Rect* CurrentClip = &frame_clip[15 - frame_];
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object, CurrentClip, &renderquad);
    }
}

SDL_Rect Bossobject :: GetRectframe()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void Bossobject :: DoBoss(Map& map_data)
{
    if ( comeback_time == 0)
    {
        x_val = 0;
        y_val += BOSS_GRAVITY;

        if (y_val >= BOSS_MAX_FALL_SPEED)
        {
            y_val = BOSS_MAX_FALL_SPEED;
        }

        check_to_map(map_data);
    }
    else if ( comeback_time > 0 )
    {
        comeback_time --;
        if (comeback_time == 0)
        {
            x_val = 0;
            y_val = 0;
            if (x_pos > 256)
            {
                x_pos -= 256;
            }
            else
            {
                x_pos = 0;
            }
            y_pos = 0;
            comeback_time = 0;
        }
    }
}

void Bossobject :: removeBullet(const int& index)
{
    int size = bullet_list.size();
    if ( size > 0 && index < size )
    {
        Bullet* p_bullet = bullet_list.at(index);
        bullet_list.erase(bullet_list.begin() + index);
        if ( p_bullet )
        {
            delete p_bullet;
            p_bullet = NULL;
        }  
    }

}




void Bossobject :: check_to_map(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;


    //Kiem tra theo chieu ngang//

    int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
    x1 = (x_pos + x_val)/TILE_SIZE;
    x2 = (x_pos + x_val + width_frame - 1)/TILE_SIZE;

    y1 = (y_pos)/TILE_SIZE;
    y2 = (y_pos + height_min - 1)/TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X  &&  y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val > 0) // di chuyen sang phai //
        {
            int val1 = map_data.tile[y1][x2];
            int val2 =  map_data.tile[y2][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos = x2*TILE_SIZE;
                x_pos -= width_frame + 1;
                x_val = 0;
            }
        }
        else if ( x_val < 0) // di chuyen sang trai //
        {
            int val1 = map_data.tile[y1][x1];
            int val2 =  map_data.tile[y2][x1];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos = (x1 + 1)*TILE_SIZE;
                x_val = 0;
            }
        }
    }

    // kiem tra theo chieu doc//
    
    int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
    x1 = (x_pos)/TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_frame -1)/TILE_SIZE;

    if ( x1 >= 0 && x2 < MAX_MAP_X &&  y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if ( y_val > 0 )
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos = y2*TILE_SIZE;
                y_pos -= (height_frame + 1);
                y_val = 0;

                on_ground = true;
            }
        }
        else if ( y_val < 0 ) // nhay //
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }


    x_pos += x_val;
    y_pos += y_val;

    if ( x_pos < 0 )
    {
        x_pos = 0;
    }

    if (x_pos + width_frame > map_data.max_x)
    {
        x_pos = map_data.max_x - width_frame - 1;
    }

    if ( y_pos > map_data.max_y )
    {
        comeback_time = 60;
    }
}


void Bossobject :: InitBullet(SDL_Renderer*screen)
{
    Bullet* p_bullet = new Bullet();
    if ( p_bullet != NULL )
    {
        p_bullet->set_bullet_type(Bullet :: BOSS_BULLET);
        bool ret = p_bullet->loadBullet(screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(Bullet :: DIR_LEFT);
            p_bullet->setrect(rect_.x +5,rect_.y + 200);
            p_bullet->set_x_val(10);
            //p_bullet->set_y_val(20);
            bullet_list.push_back(p_bullet);
        }
    }
}

void Bossobject :: MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    if ( frame_ == 4 && dealay_frame == 1)
    {
        count ++;
    }
    if ( count == 12 )
    {
        InitBullet(screen);
        count = 0;
    }
    //cout << dealay_frame << endl;
    //cout << frame_ << endl;
    //InitBullet(screen);
    for ( int i = 0; i < bullet_list.size(); i++ )
    {
        Bullet* p_bullet = bullet_list.at(i);
        if ( p_bullet != NULL )
        {
            if ( p_bullet->get_is_move())
            {
                int bullet_distance = rect_.x + width_frame - p_bullet->getrect().x;
                if ( bullet_distance < 2000 && bullet_distance > 0 )
                {
                    p_bullet->handle_move(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->setrect(rect_.x + 5,rect_.y + 200);
            }
        }
    }
}