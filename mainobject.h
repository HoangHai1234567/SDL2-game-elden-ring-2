#ifndef MAIN_OBJECT_
#define MAIN_OBJECT_

#include <vector>
#include "commnonfunct.h"
#include "object.h"
#include "bullet.h"

#define gravity 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_JUMP -18
#define PLAYER_FALL 16
#define BULLET_RATIO 0.3
#define BULLET_RATIO1 0.2
#define BULLET_RATIO2 0.4
#define MAX_SPEED 12  //12
#define MIN_SPEED 8

static Mix_Chunk* g_sound_item[2];



class mainobject : public object
{
public:
    mainobject();
    ~mainobject();

    enum walktype
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2,
    };

    virtual bool loadimg( string path, SDL_Renderer* screen );
    void show(SDL_Renderer* des);
    void handle(SDL_Event e, SDL_Renderer* screen, Mix_Chunk* bullet_sound[5] );
    void set_clip();

    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}



    void doplayer(Map& map_data);
    void checkmap(Map& map_data);
    void setmapxy(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void centerentityonmap(Map& map_data);
    void update_image_player(SDL_Renderer* des);
    SDL_Rect GetRectframe();

    void set_bullet_list(vector<Bullet*> bullet_list)
    {
        p_bullet_list = bullet_list;
    }

    vector<Bullet*> get_bullet_list() const {return p_bullet_list;}
    void handlebullet(SDL_Renderer* des);
    void removeBullet(const int& index);

    void increaseMoney();

    void ComeBackTime(const int& cb_time) {comeback_time = cb_time;}
    int GetMoney() const {return money_count;}

    bool die();
    


private:

    int money_count;


    vector<Bullet*> p_bullet_list;

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    int map_x_;
    int map_y_;

    SDL_Rect frame_clip[8];
    input input_type;
    int frame;
    int status;
    bool on_ground = false;

    int comeback_time = 0;

    bool static_amo_sephere = false;
    bool static_amo_greenamo = false;
    bool static_amo_oval = true;
    bool static_amo_sun = false;
    bool bullet_count2 = false;
    bool bullet_count3 = false;

    int t = 0;

    int check_coin;


    int PLAYER_SPEED;
    
    bool dead;
};


#endif