#include "mainobject.h"
#include "object.h"

mainobject :: mainobject()
{
    frame = 0;
    x_pos = 0;
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    width_frame = 0;
    height_frame = 0;
    status = WALK_NONE;
    input_type.left = 0;
    input_type.right = 0;
    input_type.jump = 0;
    input_type.up = 0;
    input_type.fall = 0;
    map_x_ = 0;
    map_y_ = 0;
    money_count = 0;
    PLAYER_SPEED = 8;
    g_sound_item[0] = Mix_LoadWAV("sound//coin.mp3");
    g_sound_item[1] = Mix_LoadWAV("sound//power up.mp3");
}

mainobject :: ~mainobject()
{

}

bool mainobject :: loadimg(string path, SDL_Renderer* screen)
{
    bool ret = object :: LoadMedia(path, screen);

    if ( ret == true )
    {
        width_frame = rect_.w/6; //8
        height_frame = rect_.h;
    }

    return ret;
}

SDL_Rect mainobject :: GetRectframe()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void mainobject :: set_clip()
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

        /*frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;*/
    }
}

void mainobject :: show(SDL_Renderer* des )
{
    update_image_player(des);

    if (input_type.left == 1 || input_type.right == 1)
    {
        frame ++;
    }
    else
    {
        frame = 0;
    }
    if ( frame >= 6 ) //8
    {
        frame = 0;
    }

    if ( comeback_time == 0 )
    {
        rect_.x = x_pos - map_x_;//
        rect_.y = y_pos - map_y_;
        //cout << x_pos << " " << y_pos << endl;

        SDL_Rect* current_clip = &frame_clip[frame];

        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame};

        SDL_RenderCopy(des, p_object, current_clip, &renderquad);
    }


}



void mainobject :: handlebullet(SDL_Renderer* des)
{
    for ( int i = 0; i < p_bullet_list.size(); i++ )
    {
        Bullet*p_bullet = p_bullet_list.at(i);
        if( p_bullet != NULL )
        {
            if( p_bullet->get_is_move() == true )
            {
                /*p_bullet->set_x_pos(x_pos);//
                p_bullet->set_y_pos(y_pos);//
                p_bullet->set_map_xy(map_x_, map_y_);*/
                p_bullet->handle_move(width, height);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin() + i);
                if ( p_bullet != NULL )
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void mainobject :: removeBullet(const int& index)
{
    int size = p_bullet_list.size();
    if ( size > 0 && index < size )
    {
        Bullet* p_bullet = p_bullet_list.at(index);
        p_bullet_list.erase(p_bullet_list.begin() + index);
        if ( p_bullet )
        {
            delete p_bullet;
            p_bullet = NULL;
        }  
    }

}

void mainobject :: doplayer(Map& map_data)
{
    if ( comeback_time == 0 )
    {
        x_val = 0;
        y_val += gravity;

        if (y_val >= MAX_FALL_SPEED)
        {
            y_val = MAX_FALL_SPEED;
        }

        if ( input_type.left == 1)
        {
            x_val -= PLAYER_SPEED;
        }

        if ( input_type.right == 1)
        {
            x_val += PLAYER_SPEED;
        }

        if( input_type.jump == 1 )
        {
            if ( on_ground == true )
            {
                y_val = PLAYER_JUMP;
            }

            on_ground = false;
            input_type.jump = 0;
        }


        if ( input_type.fall == 1 )
        {
            if( on_ground == false )
            {
                y_val = PLAYER_FALL;
            }

            input_type.fall = 0;
        }



        checkmap(map_data);
        if ( x_pos >= 24650 && x_pos <= 25000 ) //24660
        {
            t = 1;
        }
        if ( t == 0 )
        {
            centerentityonmap(map_data);
        }
        //cout << t << endl;
        //centerentityonmap(map_data);
    }

    if ( comeback_time > 0 )
    {
        comeback_time--;
        if ( comeback_time == 0 )
        {
            on_ground = false;
            if ( x_pos > 256 )
            {
                x_pos -= 256 ;
                y_pos += 100 ;
            } 
            else
            {
                x_pos = 0;
            }
            y_pos = 0;
            x_val = 0;
            y_val = 0;
        }
    }
}



void mainobject :: centerentityonmap(Map& map_data)
{
    map_data.start_x = x_pos - (width/2);
    if ( map_data.start_x < 0 )
    {
        map_data.start_x = 0;
    }
    else if ( map_data.start_x + width >= map_data.max_x )
    {
        map_data.start_x = map_data.max_x - width;
    }


    map_data.start_y = y_pos - (height/2);
    if ( map_data.start_y < 0 )
    {
        map_data.start_y = 0;
    }
    else if ( map_data.start_y + height >= map_data.max_y )
    {
        map_data.start_y = map_data.max_y - height;
    }
    //cout << map_data.start_x << " " << map_data.start_y << endl;

}

void mainobject :: checkmap(Map& map_data)
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

            if ( val1 == STATE_MONEY || val2 == STATE_MONEY ) //xu li coin
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                increaseMoney();
            }
            else
            {
                if ( val1 == BULLET_COUNT_X2 || val2 == BULLET_COUNT_X2 ) //xu li dan
                {
                    map_data.tile[y1][x2] = 0;
                    map_data.tile[y2][x2] = 0;
                    bullet_count2 = true;
                    bullet_count3 = false;
                    Mix_PlayChannel(-1, g_sound_item[1], 0);
                }
                else
                {
                    if (val1 == BULLET_COUNT_X3 || val2 == BULLET_COUNT_X3)
                    {
                        map_data.tile[y1][x2] = 0;
                        map_data.tile[y2][x2] = 0;
                        bullet_count2 = false;
                        bullet_count3 = true;
                        Mix_PlayChannel(-1, g_sound_item[1], 0);
                    }
                    else
                    {
                        if ((val1 != BLANK_TILE && val1 != GRASS) || (val2 != GRASS && val2 != BLANK_TILE))
                        {
                            x_pos = x2*TILE_SIZE;
                            x_pos -= width_frame + 1;
                            x_val = 0;
                        }
                    }
                }
            }
        }
        else if ( x_val < 0) // di chuyen sang trai //
        {
            int val1 = map_data.tile[y1][x1];
            int val2 =  map_data.tile[y2][x1];

            if ( val1 == STATE_MONEY || val2 == STATE_MONEY ) //xu li coin
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                increaseMoney();
            }

            else
            {
                if ( val1 == BULLET_COUNT_X2 || val2 == BULLET_COUNT_X2 ) //xu li dan
                {
                    map_data.tile[y1][x1] = 0;
                    map_data.tile[y2][x1] = 0;
                    bullet_count2 = true;
                    bullet_count3 = false;
                    Mix_PlayChannel(-1, g_sound_item[1], 0);
                }
                else
                {
                    if (val1 == BULLET_COUNT_X3 || val2 == BULLET_COUNT_X3)
                    {
                        map_data.tile[y1][x1] = 0;
                        map_data.tile[y2][x1] = 0;
                        bullet_count2 = false;
                        bullet_count3 = true;
                        Mix_PlayChannel(-1, g_sound_item[1], 0);
                    }
                    else
                    {
                        if ((val1 != BLANK_TILE && val1 != GRASS) || (val2 != GRASS && val2 != BLANK_TILE))
                        {
                            x_pos = (x1 + 1)*TILE_SIZE;
                            x_val = 0;
                        }
                    }
                }
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

            if ( val1 == STATE_MONEY || val2 == STATE_MONEY )
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                increaseMoney();
            }
            else
            {
                if ( val1 == BULLET_COUNT_X2 || val2 == BULLET_COUNT_X2 )
                {
                    map_data.tile[y2][x1] = 0;
                    map_data.tile[y2][x2] = 0;
                    bullet_count2 = true;
                    bullet_count3 = false;
                    Mix_PlayChannel(-1, g_sound_item[1], 0);
                }
                else
                {
                    if (val1 == BULLET_COUNT_X3 || val2 == BULLET_COUNT_X3)
                    {
                        map_data.tile[y2][x1] = 0;
                        map_data.tile[y2][x2] = 0;
                        bullet_count2 = false;
                        bullet_count3 = true;
                        Mix_PlayChannel(-1, g_sound_item[1], 0);
                    }
                    else
                    {
                        if ((val1 != BLANK_TILE && val1 != GRASS) || (val2 != GRASS && val2 != BLANK_TILE))
                        {
                            y_pos = y2*TILE_SIZE;
                            y_pos -= (height_frame + 1);
                            y_val = 0;

                            on_ground = true;
                            if ( status == WALK_NONE )
                            {
                                status = WALK_RIGHT;
                            }
                        }
                    }
                }
            }
        }
        else if ( y_val < 0 ) // nhay //
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            
            if ( val1 == STATE_MONEY || val2 == STATE_MONEY )
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                increaseMoney();
            }
            else
            {
                if ( val1 == BULLET_COUNT_X2 || val2 == BULLET_COUNT_X2 )
                {
                    map_data.tile[y1][x1] = 0;
                    map_data.tile[y1][x2] = 0;
                    bullet_count2 = true;
                    bullet_count3 = false;
                    Mix_PlayChannel(-1, g_sound_item[1], 0);
                }
                else
                {
                    if (val1 == BULLET_COUNT_X3 || val2 == BULLET_COUNT_X3)
                    {
                        bullet_count3 = true;
                        bullet_count2 = false;
                        map_data.tile[y1][x1] = 0;
                        map_data.tile[y1][x2] = 0;
                        Mix_PlayChannel(-1, g_sound_item[1], 0);
                    }
                    else
                    {
                        if ((val1 != BLANK_TILE && val1 != GRASS) || (val2 != GRASS && val2 != BLANK_TILE))
                        {
                            y_pos = (y1 + 1)*TILE_SIZE;
                            y_val = 0;
                        }
                    }
                }
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


void mainobject :: increaseMoney()
{
    money_count++;
    if ( money_count <= 5 )
    {
        static_amo_oval = true;
    }
    if (money_count > 5 && money_count <= 10)
    {
        static_amo_oval = false;
        static_amo_sephere = true;
    }
    if ( money_count > 10 && money_count <= 20 )
    {
        static_amo_sephere = false;
        static_amo_greenamo = true;
    }
    if (money_count > 20)
    {
        static_amo_greenamo = false;
        static_amo_sun = true;
    }
    Mix_PlayChannel(-1, g_sound_item[0], 0);
}


void mainobject :: update_image_player(SDL_Renderer* des)
{
    if (on_ground == true)
    {
        if ( status == WALK_LEFT )
        {
            LoadMedia("img//Dude_Monster_Walk_6_left.png", des);
            //LoadMedia("img//player_left.png", des);
        }
        else
        {
            LoadMedia("img//Dude_Monster_Walk_6.png", des);
            //LoadMedia("img//player_right.png", des);
        }
    }
    else
    {
        if ( status == WALK_LEFT )
        {
            //LoadMedia("img//jum_left.png", des);
            LoadMedia("img//Dude_Monster_Jump_8_left.png", des);
        }
        else
        {
            LoadMedia("img//Dude_Monster_Jump_8.png", des);
            //LoadMedia("img//jum_right.png", des);
        }
    }
}

void mainobject :: handle(SDL_Event e, SDL_Renderer* screen, Mix_Chunk* bullet_sound[5] )
{
    if ( e.type == SDL_KEYDOWN )
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT:
                {
                    status = WALK_RIGHT;
                    input_type.right = 1;
                    input_type.left = 0;
                    update_image_player(screen);
                }
                break;
            case SDLK_LEFT:
                {
                    status = WALK_LEFT;
                    input_type.left = 1;
                    input_type.right = 0;
                    update_image_player(screen);
                }
                break;
            case SDLK_UP:
                { 
                    input_type.jump = 1;
                    Mix_PlayChannel(-1, bullet_sound[4], 0);
                }
                break;
            case SDLK_DOWN:
                {
                    input_type.fall = 1;
                }
                break;

            case SDLK_LSHIFT:
                {
                    if (PLAYER_SPEED < MAX_SPEED)
                    {
                        PLAYER_SPEED += 4;
                    }
                    if ( PLAYER_SPEED >= MAX_SPEED )
                    {
                        PLAYER_SPEED = MAX_SPEED;
                    }
                        
                }
                break;

            case SDLK_z:
                {
                    Bullet* p_bullet3 = new Bullet();
                    Bullet* p_bullet2 = new Bullet();
                    Bullet* p_bullet1 = new Bullet();
                    if ( static_amo_sun == true )
                    {
                        p_bullet3 -> set_bullet_type(Bullet :: SUN);
                        p_bullet3 -> set_x_val(60);
                        p_bullet3 -> set_y_val(60);
                        p_bullet2 -> set_bullet_type(Bullet :: SUN);
                        p_bullet2 -> set_x_val(60);
                        p_bullet2 -> set_y_val(60);
                        p_bullet1 -> set_bullet_type(Bullet :: SUN);
                        p_bullet1 -> set_x_val(60);
                        p_bullet1 -> set_y_val(60);
                        Mix_PlayChannel(-1, bullet_sound[2], 0);
                    }
                    if (static_amo_sephere == true)
                    {
                        p_bullet3 -> set_bullet_type(Bullet :: SEPHERE);
                        p_bullet3 -> set_x_val(35);
                        p_bullet3 -> set_y_val(35);
                        p_bullet2 -> set_bullet_type(Bullet :: SEPHERE);
                        p_bullet2 -> set_x_val(35);
                        p_bullet2 -> set_y_val(35);
                        p_bullet1 -> set_bullet_type(Bullet :: SEPHERE);
                        p_bullet1 -> set_x_val(35);
                        p_bullet1 -> set_y_val(35);
                        Mix_PlayChannel(-1, bullet_sound[3], 0);
                    }
                    if ( static_amo_greenamo == true )
                    {
                        p_bullet3 -> set_bullet_type(Bullet :: GREEN_AMO);
                        p_bullet3 -> set_x_val(45);
                        p_bullet3 -> set_y_val(45);
                        p_bullet2 -> set_bullet_type(Bullet :: GREEN_AMO);
                        p_bullet2 -> set_x_val(45);
                        p_bullet2 -> set_y_val(45);
                        p_bullet1 -> set_bullet_type(Bullet :: GREEN_AMO);
                        p_bullet1 -> set_x_val(45);
                        p_bullet1 -> set_y_val(45);
                        Mix_PlayChannel(-1, bullet_sound[1], 0);
                    }
                    if ( static_amo_oval == true )
                    {
                        p_bullet1 -> set_bullet_type(Bullet :: OVAL);
                        p_bullet2 -> set_bullet_type(Bullet :: OVAL);
                        p_bullet3 -> set_bullet_type(Bullet :: OVAL);
                        p_bullet3 -> set_x_val(20);
                        p_bullet3 -> set_y_val(20);
                        p_bullet2 -> set_x_val(20);
                        p_bullet2 -> set_y_val(20);
                        p_bullet1 -> set_x_val(20);
                        p_bullet1 -> set_y_val(20);
                        Mix_PlayChannel(-1, bullet_sound[0], 0);

                    }
                    if ( bullet_count3 == true && bullet_count2 == false )
                    {
                        p_bullet1 -> loadBullet(screen);
                        p_bullet2 -> loadBullet(screen);
                        p_bullet3 -> loadBullet(screen);

                    }
                    if ( bullet_count2 == true && bullet_count3 == false )
                    {
                        p_bullet1 -> loadBullet(screen);
                        p_bullet2 -> loadBullet(screen);
                    }
                    if ( bullet_count2 == false && bullet_count3 == false )
                    {
                        p_bullet1 -> loadBullet(screen);
                    }
                    if (status == WALK_LEFT)
                    {
                        if (bullet_count3 == true && bullet_count2 == false)
                        {
                            p_bullet2->set_bullet_dir(Bullet :: DIR_UPLEFT);
                            p_bullet2->setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO1);
                            p_bullet1->set_bullet_dir(Bullet :: DIR_LEFT);
                            p_bullet1->setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO);
                            p_bullet3->set_bullet_dir(Bullet :: DIR_DOWNLEFT);
                            p_bullet3->setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO2);

                        }
                        if (bullet_count2 == true && bullet_count3 == false)
                        {
                            p_bullet2->set_bullet_dir(Bullet :: DIR_LEFT);
                            p_bullet2->setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO1);
                            p_bullet1->set_bullet_dir(Bullet :: DIR_LEFT);
                            p_bullet1->setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO2);
                        }
                        if (bullet_count2 == false && bullet_count3 == false)
                        {
                            p_bullet1->set_bullet_dir(Bullet :: DIR_LEFT);
                            p_bullet1 -> setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO);
                        }
                        /*p_bullet->set_bullet_dir(Bullet :: DIR_LEFT);
                        p_bullet -> setrect(this -> rect_.x , rect_.y + height_frame*BULLET_RATIO);*/
                    }
                    else
                    {
                        if (bullet_count3 == true && bullet_count2 == false)
                        {
                            p_bullet2->set_bullet_dir(Bullet :: DIR_UPRIGHT);
                            p_bullet2->setrect(this -> rect_.x + width_frame -20 , rect_.y + height_frame*BULLET_RATIO1);
                            p_bullet1->set_bullet_dir(Bullet :: DIR_RIGHT);
                            p_bullet1->setrect(this -> rect_.x + width_frame -20 , rect_.y + height_frame*BULLET_RATIO);
                            p_bullet3->set_bullet_dir(Bullet :: DIR_DOWNRIGHT);
                            p_bullet3->setrect(this -> rect_.x + width_frame -20 , rect_.y + height_frame*BULLET_RATIO2);

                        }
                        if (bullet_count2 == true && bullet_count3 == false)
                        {
                            p_bullet2->set_bullet_dir(Bullet :: DIR_RIGHT);
                            p_bullet2->setrect(this -> rect_.x + width_frame -20, rect_.y + height_frame*BULLET_RATIO1);
                            p_bullet1->set_bullet_dir(Bullet :: DIR_RIGHT);
                            p_bullet1->setrect(this -> rect_.x + width_frame -20 , rect_.y + height_frame*BULLET_RATIO2);
                        }
                        if (bullet_count2 == false && bullet_count3 == false)
                        {
                            p_bullet1->set_bullet_dir(Bullet :: DIR_RIGHT);
                            p_bullet1 -> setrect(this -> rect_.x + width_frame -20, rect_.y + height_frame*BULLET_RATIO);
                        }
                        /*p_bullet1->set_bullet_dir(Bullet :: DIR_RIGHT);
                        p_bullet1 -> setrect(this -> rect_.x + width_frame -20, rect_.y + height_frame*BULLET_RATIO);*/
                    }
                    if (bullet_count3 == true && bullet_count2 == false)
                    {
                        p_bullet1 -> set_is_move(true);
                        p_bullet2 -> set_is_move(true);
                        p_bullet3 -> set_is_move(true);

                        p_bullet_list.push_back(p_bullet1);
                        p_bullet_list.push_back(p_bullet2);
                        p_bullet_list.push_back(p_bullet3);
                    }

                    else if (bullet_count2 == true && bullet_count3 == false)
                    {
                        p_bullet1 -> set_is_move(true);
                        p_bullet2 -> set_is_move(true);

                        p_bullet_list.push_back(p_bullet1);
                        p_bullet_list.push_back(p_bullet2);
                    }
                    else if (bullet_count2 == false && bullet_count3 == false)
                    {
                        p_bullet1 -> set_is_move(true);
                        p_bullet_list.push_back(p_bullet1);
                    }
                }
                break;
        }
    }
    else if ( e.type == SDL_KEYUP )
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_RIGHT:
                {
                    input_type.right = 0;
                }
                break;
            case SDLK_LEFT:
                {
                    input_type.left = 0;
                }
                break;
            case SDLK_LSHIFT:
                {
                    if (PLAYER_SPEED > MIN_SPEED)
                    {
                        PLAYER_SPEED = MIN_SPEED;
                    }
                }
                break;
        }
    }
}
