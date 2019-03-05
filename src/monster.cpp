// monster.cpp - implement monster class

#include "monster.hpp"

#include "libtcod.hpp"

// Constructor
// Class parent class constructor
Monster::Monster(int x, int y, int ch, const TCODColor& colour, int health,
	int damage) : Actor(x, y, ch, colour, health, Clan::monster), damage(damage)
	{

}

// Update monster position
bool Monster::Update(
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

	// Create value to hold the change in direction
	auto dx = 0;
	auto dy = 0;

	// If no actor found, wander
	if(ptr == nullptr) {
		// Get a random int and move a different position based on it
		switch(TCODRandom::getInstance()->getInt(0, 3)) {
			case 0: if(!map->IsWall(x + 1, y)) {
					dx = 1;
				};
				break;
			case 1: if(!map->IsWall(x - 1, y)) {
					dx = -1;
				};
				break;
			case 2: if(!map->IsWall(x, y + 1)) {
					dy = 1;
				};
				break;
			case 3: if(!map->IsWall(x, y - 1)) {
					dy = -1;
				};
				break;
			default: break;
		}
	}

	// Else, move toward that player
	else if(ptr->x > x && !map->IsWall(x + 1, y)) {
		dx = 1;
	}
	else if(ptr->x < x && !map->IsWall(x - 1, y)) {
		dx = -1;
	}
	else if(ptr->y > y && !map->IsWall(x, y + 1)) {
		dy = 1;
	}
	else if(ptr->y < y && !map->IsWall(x, y - 1)) {
		dy = -1;
	}

	// Find tile monster would end up at
	auto tx = x + dx;
	auto ty = y + dy;

	ptr = nullptr;
	// Find if change in direction ends up attacking a different player
	for(auto i : *actors) {
		if(i->x == tx && i->y == ty) {
			ptr = i;
			break;
		}
	}

	// If tile is empty
	if(ptr == nullptr) {
		x = tx;
		y = ty;
	}
	// If clan is different from this monster's clan
	else if(ptr->clan != clan) {
		// Attack that unit
	}
	// Otherwise, tile is occupied by same type of monster as this so don't move
	else {
		return false;
	}

	// Monster moved
	return true;
}
