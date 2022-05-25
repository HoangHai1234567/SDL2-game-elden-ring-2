#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "object.h"
#include "commnonfunct.h"

#define NUM_FRAME_EXPLO 4

class explosion : public object
{
public:
    explosion();
    ~explosion();
public:
    void setclip();
    void set_frame(const int& fr) { frame = fr;}
    virtual bool Loadimg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int get_frame_width() const {return frame_width;}
    int get_frame_height() const {return frame_height;}


private:
    int frame_width;
    int frame_height;
    
    unsigned int frame;
    SDL_Rect frame_clip[NUM_FRAME_EXPLO];

};
#endif
