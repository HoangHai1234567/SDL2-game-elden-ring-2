#include "threatsobject2.h"
Threatsobject2 :: Threatsobject2()
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
    type_move = STATIC_THREAT;
}

Threatsobject2 :: ~Threatsobject2()
{

}

bool Threatsobject2 :: LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = object :: LoadMedia(path, screen);
    if (ret == true)
    {
        width_frame = rect_.w/THREATS_FRAME2;
        height_frame = rect_.h;
    }

    return ret;
}

void Threatsobject2 :: setclip()
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

        frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;

        frame_clip[8].x = 8*width_frame;
        frame_clip[8].y = 0;
        frame_clip[8].w = width_frame;
        frame_clip[8].h = height_frame;

        frame_clip[9].x = 9*width_frame;
        frame_clip[9].y = 0;
        frame_clip[9].w = width_frame;
        frame_clip[9].h = height_frame;

        frame_clip[10].x = 10*width_frame;
        frame_clip[10].y = 0;
        frame_clip[10].w = width_frame;
        frame_clip[10].h = height_frame;

        frame_clip[11].x = 11*width_frame;
        frame_clip[11].y = 0;
        frame_clip[11].w = width_frame;
        frame_clip[11].h = height_frame;

        /*frame_clip[12].x = 12*width_frame;
        frame_clip[12].y = 0;
        frame_clip[12].w = width_frame;
        frame_clip[12].h = height_frame;*/
    }
}

void Threatsobject2 :: Show(SDL_Renderer* des)
{
    if ( comeback_time == 0 )
    {
        rect_.x = x_pos - map_x;
        rect_.y = y_pos - map_y;
        frame_++;

        if (frame_ >= 9)
        {
            frame_ = 0;
        }

        SDL_Rect* CurrentClip = &frame_clip[frame_];
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};
        SDL_RenderCopy(des, p_object, CurrentClip, &renderquad);
    }
}

void Threatsobject2 :: DoThreat(Map& map_data)
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
            x_val -= THREAT_SPEED2;
        }
        else if (input_type.right == 1)
        {
            x_val += THREAT_SPEED2;
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

void Threatsobject2 :: InitThreat()
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

void Threatsobject2 :: check_to_map(Map& map_data)
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
void Threatsobject2 :: impMove(SDL_Renderer* screen)
{
    if (type_move == STATIC_THREAT)
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
                LoadImg("img//rong_left.png", screen);
            }
            else if ( x_pos < animation_a )
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("img//rong_right.png", screen);
            }
        }
        else
        {
            /*if ( input_type.left == 1 )
            {
                LoadImg("img//rong_left.png", screen);
            }*/
            if ( x_pos > animation_b ) //x_pos > animation b
            {
                input_type.left = 1;
                input_type.right = 0;
                LoadImg("img//rong_left.png", screen);
            }
            else if ( x_pos < animation_a )
            {
                input_type.left = 0;
                input_type.right = 1;
                LoadImg("img//rong_right.png", screen);
            }
        }
    }
}

SDL_Rect Threatsobject2 :: GetRectframe()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}