// player.hpp - define a player class

#pragma once

#include "actor.hpp"

#include "libtcod.hpp"

class Player : public Actor {
public:
	// Constructor
	Player(int x, int y, int ch, const TCODColor& colour);

	// Update function
	// Take user input and then move if tile is free
	bool Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
		std::shared_ptr<Map> map, std::shared_ptr<Log> log) override;
};
