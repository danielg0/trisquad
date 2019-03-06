// actor.hpp - define a moving character on screen

#pragma once

#include "log.hpp"
#include "map.hpp"

#include "libtcod.hpp"

enum Clan {
	player,
	monster
};

class Actor {
private:
	// ASCII code of character used to represent this actor
	int ch;

	// Colour of this actor
	TCODColor colour;

public:
	// Health - the amount of health this creature has
	int health;

	// This actor's team
	Clan clan;

	// This actor's position
	int x;
	int y;

	// Constructor
	Actor(int x, int y, int ch, const TCODColor& colour, int health, Clan clan);

	// Render function
	void Render() const;

	// Update function
	// Specified in inherited class. Returns bool indicating whether actor moved
	virtual bool Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
		std::shared_ptr<Map> map, std::shared_ptr<Log> log) = 0;
};
