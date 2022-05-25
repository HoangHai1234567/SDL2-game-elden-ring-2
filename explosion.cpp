#include "explosion.h"

explosion :: explosion()
{
    frame_height = 0;
    frame_width = 0;
    frame = 0;
}

explosion :: ~explosion()
{

}

bool explosion :: Loadimg(string path, SDL_Renderer* screen)
{
    bool ret = object :: LoadMedia(path, screen);
    if (ret)
    {
        frame_width = rect_.w/NUM_FRAME_EXPLO;
        frame_height = rect_.h;
    }

    return ret;
}

void explosion :: setclip()
{
    if ( frame_width > 0 && frame_height > 0 )
    {
        for ( int i = 0; i < NUM_FRAME_EXPLO; i++ )
        {
            frame_clip[i].x = frame_width*i;
            frame_clip[i].y = 0;
            frame_clip[i].w = frame_width;
            frame_clip[i].h = frame_height;
        }
    }
} 

void explosion :: Show(SDL_Renderer* screen)
{
    SDL_Rect* current_clip = &frame_clip[frame];

    SDL_Rect renderquad = {rect_.x, rect_.y, frame_width, frame_height};
    if ( current_clip != NULL )
    {
        renderquad.w = current_clip->w;
        renderquad.h = current_clip->h;

    }

    SDL_RenderCopy(screen, p_object, current_clip, &renderquad);
}