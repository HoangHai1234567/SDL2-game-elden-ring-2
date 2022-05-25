#include "map.h"

void GameMap :: LoadMap( const string& file_name )
{
    ifstream file(file_name);
    if ( !file )
    {
        cout << "error loading map";
        SDL_Quit();
        exit(1);
    }

    game_map.max_x = 0;
    game_map.max_y = 0;
    game_map.start_x = game_map.start_y = 0;
    game_map.file_name = file_name;

    for ( int i = 0; i < MAX_MAP_Y; i++ )
    {
        for ( int j = 0; j < MAX_MAP_X; j++ )
        {
            file >> game_map.tile[i][j];
            int val = game_map.tile[i][j];
            if ( val > 0 )
            {
                if ( j > game_map.max_x )
                {
                    game_map.max_x = j;
                }

                if ( i > game_map.max_y )
                {
                    game_map.max_y = i;
                }
            }
        }
    }

    game_map.max_x = (game_map.max_x + 1)*TILE_SIZE;
    game_map.max_y = (game_map.max_y + 1)*TILE_SIZE;


    file.close();
}

void GameMap :: LoadTile(SDL_Renderer* screen)
{

    for ( int i = 0; i < MAX_TILE; i++ )
    {
        ifstream file("map//" + to_string(i) + ".png");

        if ( !file )
        {
            continue;
        }
        file.close();

        tile_map[i].LoadMedia("map//" + to_string(i) + ".png", screen);
    }
}

void GameMap ::  DrawMap( SDL_Renderer* screen )
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map.start_x/TILE_SIZE;
    map_y = game_map.start_y/TILE_SIZE;


    x1 = (game_map.start_x % TILE_SIZE)*-1;
    x2 = x1 + width + ( x1 == 0 ? 0 : TILE_SIZE);


    y1 = (game_map.start_y % TILE_SIZE)*-1;
    y2 = y1 + height + ( y1 == 0? 0 : TILE_SIZE);


    for ( int i = y1; i < y2 ; i += TILE_SIZE )
    {
        map_x = game_map.start_x/TILE_SIZE;
        for ( int j = x1; j < x2 ; j += TILE_SIZE )
        {
            int val = game_map.tile[map_y][map_x];
            if ( val > 0 )
            {
                tile_map[val].setrect(j, i);
                tile_map[val].Render(screen, NULL);
            }

            map_x ++;
        }
        map_y ++;
    }
}