// actor.hpp - define a moving character on screen

#pragma once

#include "map.hpp"

#include "libtcod.hpp"

class Actor {
private:
	// ASCII code of character used to represent this actor
	int ch;

	// Colour of this actor
	TCODColor colour;

public:
	// This actor's position
	int x;
	int y;

	// Constructor
	Actor(int x, int y, int ch, const TCODColor& colour);

	// Render function
	void Render() const;

	// Update function
	// Specified in inherited class
	virtual void Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
		std::shared_ptr<Map> map) = 0;
};
