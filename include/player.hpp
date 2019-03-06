// player.hpp - define a player class

#pragma once

#include "actor.hpp"

#include "libtcod.hpp"

class Player : public Actor {
public:
	// Constructor
	Player(int x, int y, int ch, const TCODColor& colour);

	// The damage this player attacks with
	// This will change for different weapons
	int damage;

	// Attack function
	// This will attack a given actor
	// Eventually upgrade to allow targeting at a tile, throwing, etc.
	void Attack(std::shared_ptr<Actor> target);

	// Update function
	// Take user input and then move if tile is free
	bool Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
		std::shared_ptr<Map> map, std::shared_ptr<Log> log) override;
};
