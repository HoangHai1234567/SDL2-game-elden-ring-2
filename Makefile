all:
	g++ -Iinclude/SDL2 -Llib -o game game.cpp boss.cpp bullet.cpp commonfunct.cpp explosion.cpp mainobject.cpp map.cpp object.cpp threatsobject.cpp threatsobject2.cpp timer.cpp textobj.cpp SideItem.cpp menu.cpp sidekick.cpp -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer