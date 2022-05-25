#include "textobj.h"
Textobj :: Textobj()
{
    text_color.r = 255;
    text_color.g = 255;
    text_color.b = 255;
    texture = NULL;
}
Textobj :: ~Textobj()
{

}


bool Textobj :: LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
    //cout << "5" << endl;
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, str_val.c_str(),text_color);
    if ( text_surface)
    {
        texture = SDL_CreateTextureFromSurface(screen, text_surface);
        width_ = text_surface->w;
        height_ = text_surface->h;

        SDL_FreeSurface(text_surface);
    }

    return texture != NULL;
}

void Textobj :: Free()
{
    //cout << "4" << endl;
    if ( texture != NULL )
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Textobj :: setcolor(Uint8 red, Uint8 green, Uint8 blue)
{
    //cout << "3" << endl;
    text_color.r = red;
    text_color.g = green;
    text_color.b = blue;
}

void Textobj :: setcolor(int type)
{
    //cout << "2" << endl;
    if ( type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color = color;
    }
    else if ( type == WHITE_TEXT )
    {
        SDL_Color color = {255, 255, 255};
        text_color = color;
    }
    else if ( type == BLACK_TEXT )
    {
        SDL_Color color = {0, 0, 0};
        text_color = color;
    }
}

void Textobj :: RenderText(SDL_Renderer* screen, int x_pos_, int y_pos_,
                           SDL_Rect* clip, double angle,
                           SDL_Point* center, SDL_RendererFlip flip)
{
    //cout << "1" << endl;
    SDL_Rect Renderquad = {x_pos_, y_pos_, width_, height_};
    if ( clip != NULL )
    {
        Renderquad.w = clip->w;
        Renderquad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture, clip, &Renderquad, angle, center, flip);
}