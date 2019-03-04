// monster.cpp - implement monster class

#include "monster.hpp"

#include "libtcod.hpp"

// Constructor
// Class parent class constructor
Monster::Monster(int x, int y, int ch, const TCODColor& colour,
	int health, int damage) : Actor(x, y, ch, colour, Clan::monster),
	health(health), damage(damage) {

}

// Update monster position
void Monster::Update(
	std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
	std::shared_ptr<Map> map) {
	// Recompute map fov
	map->ComputeFOV(x, y);

	// Find the first player in the actors array
	std::shared_ptr<Actor> ptr = nullptr;
	for(auto i : *actors) {
		if(i->clan == Clan::player && map->InFov(i->x, i->y)) {
			ptr = i;
			break;
		}
	}

	// If no actor found, wander
	if(ptr == nullptr) {
		// Get a random int and move a different position based on it
		switch(TCODRandom::getInstance()->getInt(0, 3)) {
			case 0: if(!map->IsWall(x + 1, y)) {
					++x;
				};
				break;
			case 1: if(!map->IsWall(x - 1, y)) {
					--x;
				};
				break;
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

	// Else, move toward that player
	else if(ptr->x > x && !map->IsWall(x + 1, y)) {
		++x;
	}
	else if(ptr->x < x && !map->IsWall(x - 1, y)) {
		--x;
	}
	else if(ptr->y > y && !map->IsWall(x, y + 1)) {
		++y;
	}
	else if(ptr->y < y && !map->IsWall(x, y - 1)) {
		--y;
	}
}
