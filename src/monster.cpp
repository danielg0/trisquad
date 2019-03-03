// monster.cpp - implement monster class

#include "monster.hpp"

#include "libtcod.hpp"

// Constructor
// Class parent class constructor
Monster::Monster(int x, int y, int ch, const TCODColor& colour) :
	Actor(x, y, ch, colour) {

}

// Update monster position
void Monster::Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
	std::shared_ptr<Map> map) {
	// Get a random int and move a different position based on it
	switch(TCODRandom::getInstance()->getInt(0, 3)) {
		case 0: if(!map->IsWall(x + 1, y)) {
				++x;
			};
			break;
		case 1: if(!map->IsWall(x - 1, y)) {
				--x;
			};
			break;;
		case 2: if(!map->IsWall(x, y + 1)) {
				++y;
			};
			break;
		case 3: if(!map->IsWall(x, y - 1)) {
				--y;
			};
			break;
		default: break;
	}
}
