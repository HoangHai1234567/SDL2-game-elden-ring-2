#ifndef TEXTOBJ_H
#define TEXTOBJ_H

#include "commnonfunct.h"

class Textobj
{
public:
    Textobj();
    ~Textobj();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };


    bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* scrren);
    void Free();

    void setcolor(Uint8 red, Uint8 green, Uint8 blue);
    void setcolor(int type);

    void RenderText(SDL_Renderer* screen, int x_pos_, int y_pos_,
                    SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);


    int getwidth() const {return width_;}
    int getheight() const {return height_;}

    void SetText(const string& text) {str_val = text;}
    string GetText() const {return str_val;}
private:
    string str_val;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width_;
    int height_;
};


#endif