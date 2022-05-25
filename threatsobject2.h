#ifndef THREATS_OBJECT_2_H
#define THREATS_OBJECT_2_H

#include "commnonfunct.h"
#include "object.h"
#include "bullet.h"

#define THREATS_FRAME2 12 //13
#define THREATS_GRAVITY 0.8
#define THREATS_MAX_FALL_SPEED 10
#define THREAT_SPEED2 10

class Threatsobject2 : public object
{
public:
    Threatsobject2();
    ~Threatsobject2();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };


    void set_x_val( const float& xVal ) {x_val = xVal;}
    void set_y_val( const float& yVal ) {y_val = yVal;}

    void set_x_pos( const float& xPos ) {x_pos = xPos;}
    void set_y_pos( const float& yPos ) {y_pos = yPos;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}

    void set_map_xy(const int& xMap, const int& yMap) { map_x = xMap; map_y = yMap;}
    void setclip();

    bool LoadImg( string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}

    void DoThreat(Map& map_data);
    void check_to_map (Map& map_data);


    void set_type_move(const int& typeMove) {type_move = typeMove;}
    void setAnimation(const int& pos_a, const int& pos_b) {animation_a = pos_a, animation_b = pos_b; }
    void set_input_left(const int& ipLeft) {input_type.left = ipLeft;}
    void impMove(SDL_Renderer* screen);

    void InitThreat();

    SDL_Rect GetRectframe();


private:

    float x_pos;
    float y_pos;

    float x_val;
    float y_val;


    int map_x;
    int map_y;


    bool on_ground;
    int comeback_time;
    SDL_Rect frame_clip[THREATS_FRAME2];
    int width_frame;
    int height_frame;
    int frame_;


    int type_move;
    int animation_a;
    int animation_b;
    input input_type;

    vector<Bullet*> bullet_list;
};

#endif