#include "object.h"
object::object()
{
    p_object = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

object::~object()
{
    Free();
}

bool object::LoadMedia(string path, SDL_Renderer* &re)
{
    Free();
    SDL_Texture* newtext = NULL;
    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if ( re == NULL )
    {
        cout << "error";
        exit(0);
    }
    if ( loadSurface == NULL )
    {
        cout << IMG_GetError();
        exit(0);
    }
    else
    {
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface -> format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newtext = SDL_CreateTextureFromSurface(re, loadSurface);
        if ( newtext == NULL )
        {
            cout << SDL_GetError() ;
            exit(0);
        }
        else
        {
            rect_.w = loadSurface -> w;
            rect_.h = loadSurface -> h;
        }

        SDL_FreeSurface(loadSurface);
    }


    p_object = newtext;
    return p_object != NULL;
}


void object :: Render( SDL_Renderer* des, SDL_Rect* clip )
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(des, p_object, clip, &renderquad);
}


void object :: Free()
{
    if ( p_object == NULL )
    {
        //cout << "1  ";
    }
    else
    {
        SDL_DestroyTexture(p_object);
        p_object = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
