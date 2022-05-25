#include "commnonfunct.h"
#include "object.h"
#include "map.h"
#include "mainobject.h"
#include "timer.h"
#include "bullet.h"
#include "threatsobject.h"
#include "threatsobject2.h"
#include "boss.h"
#include "sidekick.h"
#include "explosion.h"
#include "textobj.h"
#include "SideItem.h"
#include "menu.h"
object background;
TTF_Font* Font_time = NULL;

int boss_hp = 500;
int grif_hp = 20;

bool init()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_EVERYTHING);

    if (ret < 0)
    {
        success = false;
    }
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    }

    win = SDL_CreateWindow("elden ring 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if ( win == NULL)
    {
        success = false;
        cout << "error loading window";
    }
    else
    {
        g_screen = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
        if ( g_screen == NULL )
        {
            success = false;
            cout << "error loading render";
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, Render_draw_color, Render_draw_color, Render_draw_color, Render_draw_color);
            int imgFlag = IMG_INIT_PNG;
            if ( !( IMG_Init(imgFlag) && imgFlag ) )
            {
                success = false;
                cout << "error loading imgFlag ";
            }
        }
        if ( TTF_Init() == -1)
        {
            cout << "error loading TTF";
            success = false;
        }
        Font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        if ( Font_time == NULL )
        {
            cout << "error loading font";
            success = false;
        }
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) //4096
        {
            success = false;
        }
        g_sound_bullet[0] = Mix_LoadWAV("sound//oval.wav");
        g_sound_bullet[1] = Mix_LoadWAV("sound//laser.wav");
        g_sound_bullet[2] = Mix_LoadWAV("sound//beam.mp3");
        g_sound_bullet[3] = Mix_LoadWAV("sound//sephere.wav");
        g_sound_bullet[4] = Mix_LoadWAV("sound//jump.wav");
        g_sound_exp[0] = Mix_LoadWAV("sound//exp1.wav");
        g_sound_exp[1] = Mix_LoadWAV("sound//hoi sinh.mp3");
        g_sound_gameplay[0] = Mix_LoadMUS("sound//game play.mp3");
    }
    return success;
}

bool loadBackground()
{
    bool ret = background.LoadMedia("img//back.png", g_screen);
    if ( ret == false )
    {
        cout << "error loading background";
        return false;
    }
    return true;
}

void close()
{
    background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;


    SDL_DestroyWindow(win);
    win = NULL;

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}


vector<Threatsobject*> MakeThreadList()
{
    vector <Threatsobject*> list_threads;


    Threatsobject* dynamic_threats = new Threatsobject[20];
    for ( int i = 0; i < 20; i++ )
    {
        Threatsobject* p_threats = (dynamic_threats + i);
        if (p_threats != NULL)
        {
            p_threats->LoadImg("img//rua_left.png", g_screen);
            p_threats->setclip();
            p_threats->set_type_move(Threatsobject:: MOVE_IN_SPACE_THREAT);
            p_threats->set_x_pos(500 + i*500);
            p_threats->set_y_pos(200);

            int pos1 = p_threats->get_x_pos() - 100;
            int pos2 = p_threats->get_x_pos() + 100;
            p_threats->setAnimation(pos1, pos2);
            p_threats->set_input_left(1);
            list_threads.push_back(p_threats);
        }
    }





    Threatsobject* threats_object = new Threatsobject[20];

    for ( int i = 0; i < 20; i++ )
    {
        Threatsobject* p_threats = (threats_object + i);
        if ( p_threats != NULL )
        {
            //p_threats->LoadImg("img//threat_level.png", g_screen);
            p_threats->LoadImg("img//plague.png", g_screen);
            p_threats->setclip();
            p_threats->set_x_pos(i*1200 + 700);
            p_threats->set_y_pos(250);
            p_threats->set_type_move(Threatsobject::STATIC_THREAT);
            p_threats->set_input_left(0);

            //Bullet* p_bullet = new Bullet();
            p_threats->InitBullet (g_screen);

            list_threads.push_back(p_threats);
        }
    }

    return list_threads;
}




vector <Threatsobject2*> MakeThreadList2()
{
    vector <Threatsobject2*> list_threads2;

    Threatsobject2* threats_object = new Threatsobject2[30]; //30

    for ( int i = 0; i < 30; i++ )
    {
        Threatsobject2* p_threats = (threats_object + i);
        if ( p_threats != NULL )
        {
            p_threats->LoadImg("img//rong_left.png", g_screen);
            p_threats->setclip();
            p_threats->set_type_move(Threatsobject:: MOVE_IN_SPACE_THREAT);
            p_threats->set_x_pos(i*900 + 500);
            p_threats->set_y_pos(60);

            int pos1 = p_threats->get_x_pos() - 300;
            int pos2 = p_threats->get_x_pos() + 300;
            p_threats->setAnimation(pos1, pos2);
            p_threats->set_input_left(1);
            list_threads2.push_back(p_threats);
        }
    }

    return list_threads2;
}

#undef main
int main()
{
    //cout << "1";
    TIMER fps_timer;
    if ( init() == false )
    {
        return 0;
    }
    if ( g_screen == NULL )
    {
        cout << "error4";
        exit(0);
    }

    if ( !loadBackground() )
    {
        cout << "error loading background";
        return 0;
    }



    GameMap game_map;
    game_map.LoadMap("map//map01.dat");
    game_map.LoadTile(g_screen);



    mainobject p_player;
    //p_player.loadimg("img//player_right.png", g_screen);
    p_player.loadimg("img//Dude_Monster_Walk_6.png", g_screen);
    p_player.set_clip();

    Sideitem_health player_health;
    player_health.Init(g_screen);

    Sideitem_coin player_coin;
    player_coin.Init(g_screen);
    player_coin.SetPos(width*0.5 - 300, 8);


    vector <Threatsobject*> threats_list = MakeThreadList();
    vector <Threatsobject2*> threats_list2 = MakeThreadList2();

    //BOSS
    Bossobject BOSS;
    BOSS.LoadImg("img//king_walk.png", g_screen);
    BOSS.setclip();
    BOSS.set_x_pos(24900);
    BOSS.set_y_pos(20);

    sidekick grif;
    grif.LoadImg("img//grif_left.png", g_screen);
    grif.setclip();
    grif.set_x_pos(24700);//24700
    grif.InitBullet(g_screen);
    grif.set_y_pos(60);
    grif.set_type_move(sidekick::MOVE_IN_SPACE_GRIF);
    int pos3 = grif.get_x_pos() - 600;
    int pos4 = grif.get_x_pos() + 200;
    grif.setAnimation(pos3, pos4);
    grif.set_input_left(1);


    explosion threat_exp;
    bool t_ret = threat_exp.Loadimg("img//explo.png", g_screen);
    if (!t_ret)
    {
        return -1;
    }
    threat_exp.setclip();


    explosion main_exp;
    bool m_ret = main_exp.Loadimg("img//explo.png", g_screen);
    if (!m_ret)
    {
        return -1;
    }
    main_exp.setclip();

    int num_die = 0;

    //TIME
    Textobj time_game;
    time_game.setcolor(Textobj::WHITE_TEXT);
    Textobj game_mark;
    game_mark.setcolor(Textobj::RED_TEXT);
    UINT mark_value = 0;
    Textobj Coin;
    Coin.setcolor(Textobj::BLACK_TEXT);

    Mix_PlayMusic(g_sound_gameplay[0], 20);
    bool quit;
    Menu p_menu;
    int ret_menu = p_menu.ShowMenu(g_screen, Font_time);
    if ( ret_menu == 1)
    {
        quit = false;
        p_menu.Free();
    }
    if ( ret_menu == 0 )
    {
        quit = true;
        p_menu.Free();
    }

    while(quit == false)
    {
        fps_timer.start();
        while ( SDL_PollEvent( &g_e ) != 0 )
        {
            if ( g_e.type == SDL_QUIT)
            {
                quit = true;
                break;
            }

            p_player.handle(g_e, g_screen, g_sound_bullet);
        }
        SDL_SetRenderDrawColor(g_screen, Render_draw_color, Render_draw_color, Render_draw_color, Render_draw_color );
        SDL_RenderClear( g_screen );

        background.Render(g_screen, NULL);
        //game_map.DrawMap(g_screen);

        Map map_data = game_map.getmap();
        p_player.handlebullet(g_screen);

        p_player.setmapxy(map_data.start_x, map_data.start_y);
        p_player.doplayer(map_data);
        p_player.show(g_screen);

        game_map.DrawMap(g_screen);
        game_map.setmap(map_data);

        player_health.show(g_screen);
        player_coin.Show(g_screen);


        bool boss_update = false;

        int player_check = MAX_MAP_X*TILE_SIZE - (map_data.start_x + p_player.getrect().x);
        if ( player_check <= width + 1500 )
        {
            boss_update = true;
            BOSS.set_map_xy(map_data.start_x, map_data.start_y);
            BOSS.DoBoss(map_data);
            BOSS.MakeBullet(g_screen, width, height);
            BOSS.Show(g_screen);

        }

        //sidekick
        grif.set_map_xy(map_data.start_x, map_data.start_y);
        grif.DoThreat(map_data);
        grif.impMove(g_screen);
        grif.MakeBullet(g_screen, width, height);
        grif.Show(g_screen);
        SDL_Rect rect_grif = grif.GetRectframe();
        SDL_Rect rect_player = p_player.GetRectframe();
        bool bcol3 = SDLCommonfunc::checkcollision(rect_grif, rect_player);
        bool bcol4;
        vector<Bullet*> gr_list = grif.get_bullet_list();
        for ( int i = 0 ; i < gr_list.size(); i++ )
        {
            Bullet* gr_bullet = gr_list.at(i);
            if ( gr_bullet != NULL )
            {
                bcol4 = SDLCommonfunc::checkcollision(gr_bullet->getrect(), rect_player);
            }
        }
        if ( bcol3 || bcol4 )
        {
            Mix_PlayChannel(-1, g_sound_exp[1], 0);
            int width_exp_frame = main_exp.get_frame_width();
            int height_exp_frame = main_exp.get_frame_height();

            for ( int ex = 0; ex < NUM_FRAME_EXPLO; ex ++ )
            {
                int x_pos = (p_player.getrect().x + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                int y_pos = (p_player.getrect().y + p_player.get_height_frame()*0.5) - height_exp_frame*0.5;

                main_exp.set_frame(ex);
                main_exp.setrect(x_pos, y_pos);
                main_exp.Show(g_screen);
                SDL_RenderPresent(g_screen);

            }

            num_die++;

            if ( num_die <= 3 )
            {
                p_player.setrect(0, 0);
                p_player.ComeBackTime(60);
                player_health.delife();
                player_health.show(g_screen);
                SDL_Delay(1000);
                continue;
            }
            else
            {
                if ( MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                {
                    grif.Free();
                    close();
                    SDL_Quit();
                    return 0;

                }
            }
        }


        for ( int i = 0; i < threats_list.size(); i++ ) //threats_list.size()
        {
            Threatsobject* p_threat = threats_list.at(i);
            if ( p_threat != NULL )
            {
                p_threat->set_map_xy(map_data.start_x, map_data.start_y);
                p_threat->impMove(g_screen);
                p_threat->DoThreat(map_data);
                p_threat->MakeBullet(g_screen, width, height);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectframe();
                bool bCol1 = false;
                vector<Bullet*> tb_list = p_threat->get_bullet_list();
                for (int u = 0; u < tb_list.size(); u++)
                {
                    Bullet* pt_bullet = tb_list.at(u);
                    if ( pt_bullet != NULL )
                    {
                        bCol1 = SDLCommonfunc::checkcollision(pt_bullet->getrect(), rect_player);
                        if ( bCol1 == true )
                        {
                            //p_threat->removeBullet(u);
                            break;
                        }
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectframe();
                bool bcol2 = SDLCommonfunc::checkcollision(rect_player, rect_threat);

                if ( bCol1 || bcol2 )
                {
                    Mix_PlayChannel(-1, g_sound_exp[1], 0);
                    int width_exp_frame = main_exp.get_frame_width();
                    int height_exp_frame = main_exp.get_frame_height();

                    for ( int ex = 0; ex < NUM_FRAME_EXPLO; ex ++ )
                    {
                        int x_pos = (p_player.getrect().x + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.getrect().y + p_player.get_height_frame()*0.5) - height_exp_frame*0.5;

                        main_exp.set_frame(ex);
                        main_exp.setrect(x_pos, y_pos);
                        main_exp.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                        //SDL_Delay(100);

                    }

                    num_die++;

                    if ( num_die <= 3 )
                    {
                        p_player.setrect(0, 0);
                        p_player.ComeBackTime(60);
                        player_health.delife();
                        player_health.show(g_screen);
                        SDL_Delay(1000);
                        continue;
                    }
                    else
                    {
                        if ( MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }

            }
        }



        //dinh dan cua boss va cham vao boss
        SDL_Rect rect_player_boss = p_player.GetRectframe();
        BOSS.getrect();
        bool bcol_boss_and_player = false;
        if ( boss_update )
        {
            SDL_Rect boss_rect;
            boss_rect = BOSS.GetRectframe();
            bcol_boss_and_player =  SDLCommonfunc::checkcollision(boss_rect, rect_player_boss);
        }
        //bool bcol_boss_and_player =  SDLCommonfunc::checkcollision(rect_player_boss, rect_player_boss);
        bool bCol_boss = false;
        vector<Bullet*> boss_list = BOSS.get_bullet_list();
        for (int u = 0; u < boss_list.size(); u++)
        {
            Bullet* pt_bullet = boss_list.at(u);
            if ( pt_bullet != NULL )
            {
                bCol_boss = SDLCommonfunc::checkcollision(pt_bullet->getrect(), rect_player_boss);
                if ( bCol_boss == true )
                {
                    break;
                }
            }
        }
        if (bCol_boss || bcol_boss_and_player) 
        {
            Mix_PlayChannel(-1, g_sound_exp[1], 0);
            num_die++;
            if ( num_die <= 3 )
            {
                p_player.setrect(0, 0);
                p_player.ComeBackTime(60);
                player_health.delife();
                player_health.show(g_screen);
                SDL_Delay(1000);
                continue;
            }
            else
            {
                if ( MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                {
                    BOSS.Free();
                    close();
                    SDL_Quit();
                    return 0;
                }
            }
        }




        for ( int i = 0; i < threats_list2.size(); i++ )
        {
            Threatsobject2* p_threat = threats_list2.at(i);
            if ( p_threat != NULL )
            {
                p_threat->set_map_xy(map_data.start_x, map_data.start_y);
                p_threat->impMove(g_screen);
                p_threat->DoThreat(map_data);
                p_threat->Show(g_screen);

                SDL_Rect rect_player = p_player.GetRectframe();
                SDL_Rect rect_threat = p_threat->GetRectframe();
                bool bcol2 = SDLCommonfunc::checkcollision(rect_player, rect_threat);
                if ( bcol2 )
                {
                    p_threat->Free();
                    threats_list2.erase(threats_list2.begin() + i);
                    Mix_PlayChannel(-1, g_sound_exp[1], 0);
                    int width_exp_frame = main_exp.get_frame_width();
                    int height_exp_frame = main_exp.get_frame_height();

                    for ( int ex = 0; ex < NUM_FRAME_EXPLO; ex ++ )
                    {
                        int x_pos = (p_player.getrect().x + p_player.get_width_frame()*0.5) - width_exp_frame*0.5;
                        int y_pos = (p_player.getrect().y + p_player.get_height_frame()*0.5) - height_exp_frame*0.5;

                        main_exp.set_frame(ex);
                        main_exp.setrect(x_pos, y_pos);
                        main_exp.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                        //SDL_Delay(100);

                    }

                    num_die++;

                    if ( num_die <= 3 )
                    {
                        p_player.setrect(0, 0);
                        p_player.ComeBackTime(60);
                        player_health.delife();
                        player_health.show(g_screen);
                        SDL_Delay(1000);
                        continue;
                    }
                    else
                    {
                        if ( MessageBox(NULL, "GAME OVER", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                        {
                            p_threat->Free();
                            close();
                            SDL_Quit();
                            return 0;
                        }
                    }
                }
            }
        }



        int frame_exp_width = threat_exp.get_frame_width();
        int frame_exp_height = threat_exp.get_frame_height();

        vector<Bullet*> bullet_arr = p_player.get_bullet_list();
        for ( int r = 0; r < bullet_arr.size(); r++ )
        {
            Bullet* p_bullet = bullet_arr.at(r);
            if ( p_bullet != NULL )
            {
                if ( boss_update )
                {
                    SDL_Rect boss_rect;
                    boss_rect = BOSS.GetRectframe();
                    //cout <<boss_rect.x << " " << boss_rect.y << " " << boss_rect.w << " " << boss_rect.h << endl;
                    SDL_Rect b_rect = p_bullet->getrect();
                    bool bcol_boss = SDLCommonfunc::checkcollision(b_rect, boss_rect);
                    if ( bcol_boss )
                    {
                        p_player.removeBullet(r);
                        boss_hp--;
                        if (boss_hp <= 0 )
                        {
                            if ( MessageBox(NULL, "YOU WIN", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                            {
                                BOSS.Free();
                                quit = true;
                                mark_value += 1000000;
                            }
                        }
                    }
                }
                SDL_Rect grif_rect;
                grif_rect = grif.GetRectframe();
                SDL_Rect b_rect = p_bullet->getrect();
                bool bcol_grif = SDLCommonfunc::checkcollision(b_rect, grif_rect);
                if ( bcol_grif )
                {
                    p_player.removeBullet(r);
                    grif_hp--;
                    if ( grif_hp <= 0 )
                    {
                        if ( MessageBox(NULL, "YOU WIN", "Info", MB_OK | MB_ICONSTOP) == IDOK )
                        {
                            grif.Free();
                            quit = true;
                            mark_value += 10000;
                        }
                    }

                }



                for ( int t = 0; t < threats_list.size(); t++ )
                {
                    Threatsobject* object_threat = threats_list.at(t);
                    if (object_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = object_threat->getrect().x;
                        tRect.y = object_threat->getrect().y;
                        tRect.w = object_threat->get_width_frame();
                        tRect.h = object_threat->get_height_frame();
                        //cout << tRect.x << " " << tRect.y << " " << tRect.w << " " << tRect.h << endl;

                        SDL_Rect bRect = p_bullet->getrect();

                        bool bCol = SDLCommonfunc::checkcollision(bRect, tRect);

                        if (bCol)
                        {
                            //point
                            mark_value += 150;
                            //sound
                            Mix_PlayChannel(-1, g_sound_exp[0], 0);
                            //exp
                            for ( int exp = 0; exp < NUM_FRAME_EXPLO; exp++ )
                            {
                                int x_pos = p_bullet->getrect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->getrect().y - frame_exp_height*0.5;
                                threat_exp.set_frame(exp);
                                threat_exp.setrect(x_pos, y_pos);
                                threat_exp.Show(g_screen);
                            }



                            p_player.removeBullet(r);
                            object_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }

                    }
                }
                for ( int t = 0; t < threats_list2.size(); t++ )
                {
                    Threatsobject2* object_threat = threats_list2.at(t);
                    if (object_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = object_threat->getrect().x;
                        tRect.y = object_threat->getrect().y;
                        tRect.w = object_threat->get_width_frame();
                        tRect.h = object_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->getrect();

                        bool bCol = SDLCommonfunc::checkcollision(bRect, tRect);

                        if (bCol)
                        {
                            //point
                            mark_value += 100;
                            //sound
                            Mix_PlayChannel(-1, g_sound_exp[0], 0);
                            //exp
                            for ( int exp = 0; exp < NUM_FRAME_EXPLO; exp++ )
                            {
                                int x_pos = p_bullet->getrect().x - frame_exp_width*0.5;
                                int y_pos = p_bullet->getrect().y - frame_exp_height*0.5;
                                threat_exp.set_frame(exp);
                                threat_exp.setrect(x_pos, y_pos);
                                threat_exp.Show(g_screen);
                            }

                            p_player.removeBullet(r);
                            object_threat->Free();
                            threats_list2.erase(threats_list2.begin() + t);
                        }

                    }
                }
            }
        }

        //SHOW TIME
        string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = 600 - time_val;
        if ( val_time <= 0 )
        {
            quit = true;
            break;
        }
        else
        {
            string str_val = to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(Font_time, g_screen);
            time_game.RenderText(g_screen, width - 200, 15);
        }

        string val_str_mark = to_string(mark_value);
        string strMark = "SCORE: ";
        strMark += val_str_mark;

        game_mark.SetText(strMark);
        game_mark.LoadFromRenderText(Font_time, g_screen);
        game_mark.RenderText(g_screen, width*0.5 - 50, 15);

        int COIN_COUNT = p_player.GetMoney();
        string coin_str_mark = to_string(COIN_COUNT);
        Coin.SetText(coin_str_mark);
        Coin.LoadFromRenderText(Font_time, g_screen);
        Coin.RenderText(g_screen, width*0.5 - 250, 15);
        //cout << COIN_COUNT << endl;



        SDL_RenderPresent(g_screen);
        time_game.Free();
        game_mark.Free();
        Coin.Free();
        p_menu.Free();

        
        int real_time = fps_timer.get_ticks();
        int time_per_frame = 600/FRAME_PER_SEC; // milisec //
        if (real_time < time_per_frame)
        {
            int delay = time_per_frame - real_time;
            if ( delay >= 0 )
            {
                SDL_Delay(delay);
            }
        }
    }


    for ( int i = 0; i < threats_list.size(); i ++)
    {
        Threatsobject*p_threat = threats_list.at(i);
        if ( p_threat != NULL )
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list.clear();

    for ( int i = 0; i < threats_list2.size(); i ++)
    {
        Threatsobject2*p_threat = threats_list2.at(i);
        if ( p_threat != NULL )
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    threats_list2.clear();

    close();
    return 0;
}