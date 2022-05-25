#include "sidekick.h"
sidekick :: sidekick()
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

    animation_a = 0;
    animation_b = 0;
    input_type.left = 0;
    type_move = STATIC_GRIF;
    dealay_frame = 2;
}

sidekick :: ~sidekick()
{

}

bool sidekick :: LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = object :: LoadMedia(path, screen);
    if (ret == true)
    {
        width_frame = rect_.w/GRIF_FRAME;
        height_frame = rect_.h;
    }

    return ret;
}

void sidekick :: setclip()
{
    if ( width_frame > 0 && height_frame > 0 )
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 3*width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 4*width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 5*width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;
    }
}

void sidekick :: Show(SDL_Renderer* des)
{
    if ( comeback_time == 0 )
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        if ( dealay_frame >= 2 )
        {
            frame_++;
            dealay_frame = 0;
        }
        dealay_frame++;

        if (frame_ >= 6)
        {
            frame_ = 0;
        }

        SDL_Rect* CurrentClip = &frame_clip[frame_];
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object, CurrentClip, &renderquad);
    }
}

void sidekick :: DoThreat(Map& map_data)
{
    if ( comeback_time == 0)
    {
        x_val = 0;
        //y_val += THREATS_GRAVITY;

        /*if (y_val >= THREATS_MAX_FALL_SPEED)
        {
            y_val = THREATS_MAX_FALL_SPEED;
        }*/
        if (input_type.left == 1)
        {
            x_val -= GRIF_SPEED;
        }
        else if (input_type.right == 1)
        {
            x_val += GRIF_SPEED;
        }

        check_to_map(map_data);
    }
    else if ( comeback_time > 0 )
    {
        comeback_time --;
        if (comeback_time == 0)
        {
            InitThreat();
        }
    }
}

void sidekick :: InitThreat()
{
    x_val = 0;
    y_val = 0;
    if (x_pos > 256)
    {
        x_pos -= 256;
        animation_a -= 256;
        animation_b -= 256;
    }
    else
    {
        x_pos = 0;
    }
    y_pos = 0;
    comeback_time = 0;
    input_type.left = 1;
}

void sidekick :: check_to_map(Map& map_data)
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
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != BULLET_COUNT_X2 && val1 != BULLET_COUNT_X3 && val1 != GRASS) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != BULLET_COUNT_X2 && val2 != BULLET_COUNT_X3 && val2 != GRASS))
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
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != BULLET_COUNT_X2 && val1 != BULLET_COUNT_X3 && val1 != GRASS) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != BULLET_COUNT_X2 && val2 != BULLET_COUNT_X3 && val2 != GRASS))
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
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != BULLET_COUNT_X2 && val1 != BULLET_COUNT_X3 && val1 != GRASS) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != BULLET_COUNT_X2 && val2 != BULLET_COUNT_X3 && val2 != GRASS))
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
            if ((val1 != BLANK_TILE && val1 != STATE_MONEY && val1 != BULLET_COUNT_X2 && val1 != BULLET_COUNT_X3 && val1 != GRASS) || (val2 != BLANK_TILE && val2 != STATE_MONEY && val2 != BULLET_COUNT_X2 && val2 != BULLET_COUNT_X3 && val2 != GRASS))
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
void sidekick :: impMove(SDL_Renderer* screen)
{
    if (type_move == STATIC_GRIF)
    {
        ;
    }
    else
    {
        if ( on_ground == false )
        {
            if ( x_pos > animation_b ) //x_pos > animation b
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("img//grif_left.png", screen);
            }
            else if ( x_pos < animation_a )
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("img//grif_right.png", screen);
            }
        }
        else
        {
            if ( x_pos > animation_b ) //x_pos > animation b
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("img//grif_left.png", screen);
            }
            else if ( x_pos < animation_a )
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("img//grif_right.png", screen);
            }
        }
    }
}

SDL_Rect sidekick :: GetRectframe()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void sidekick :: InitBullet( SDL_Renderer*screen)
{
    Bullet* p_bullet = new Bullet();
    if ( p_bullet != NULL )
    {
        p_bullet->set_bullet_type(Bullet :: FIREBALL);
        bool ret = p_bullet->loadBullet(screen);
        if (ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(Bullet :: DIR_DOWN);
            p_bullet->setrect(rect_.x - 50,rect_.y + 50);
            //p_bullet->set_x_val(20);
            p_bullet->set_y_val(20);
            bullet_list.push_back(p_bullet);
        }
    }
}
void sidekick :: MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for ( int i = 0; i < bullet_list.size(); i++ )
    {
        Bullet* p_bullet = bullet_list.at(i);
        if ( p_bullet != NULL )
        {
            if ( p_bullet->get_is_move())
            {
                p_bullet->handle_move(x_limit, y_limit);
                p_bullet->Render(screen);
            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->setrect(rect_.x + 5,rect_.y + 50);
            }
        }
    }
}