#ifndef MAP_H
#define MAP_H

#include "commnonfunct.h"
#include "object.h"
#define MAX_TILE 100

class TileMat : public object
{
public:
    TileMat() {;}
    ~TileMat() {;}    
};


class GameMap 
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap( const string& file_name );
    void LoadTile ( SDL_Renderer* screen );
    void DrawMap( SDL_Renderer* screen );
    Map getmap() const {return game_map;};
    void setmap(Map& map_data) {game_map = map_data;};
private:
    Map game_map;
    TileMat tile_map[MAX_TILE];
};


#endif