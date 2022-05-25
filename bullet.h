#ifndef BULLET_H
#define BULLET_H


#include "object.h"
#include "commnonfunct.h"


#define BULLET_SPEED 20

class Bullet : public object
{
public:
    Bullet();
    ~Bullet();



    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UPLEFT = 23,
        DIR_UPRIGHT = 24,
        DIR_DOWNLEFT = 25,
        DIR_DOWNRIGHT = 26,
        DIR_DOWN = 27,
    };

    enum BulletType
    {
        OVAL = 50,
        SEPHERE = 51,
        GREEN_AMO = 52,
        SUN = 53,
        FIREBALL = 54,
        PURPLE = 55,
        PLAGUE_BULLET = 56,
        BOSS_BULLET = 57,
    };



    void set_x_val(const int& xVal) {x_val = xVal;}
    void set_y_val(const int& yVal) {y_val = yVal;}
    int get_x_val() const {return x_val;}
    int get_y_val() const {return y_val;}

    void set_x_pos( const float& xPos ) {x_pos = xPos;}
    void set_y_pos( const float& yPos ) {y_pos = yPos;}

    float get_x_pos() const {return x_pos;}
    float get_y_pos() const {return y_pos;}

    void set_map_xy(const int& xMap, const int& yMap) { map_x = xMap; map_y = yMap;}

    void set_is_move(const bool& isMove) {is_move = isMove;}
    bool get_is_move() const {return is_move;}

    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir = bulletDir;}
    unsigned int get_bullet_dir() const {return bullet_dir;}

    void handle_move(const int& x_border, const int& y_border);

    void set_bullet_type(const unsigned int& bulletType) {bullet_type = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type;}

    bool loadBullet(SDL_Renderer* des);


private:
    int x_val;
    int y_val;
    bool is_move;
    unsigned int bullet_dir;
    unsigned int bullet_type;


    float x_pos;
    float y_pos;

    int map_x;
    int map_y;

};






#endif