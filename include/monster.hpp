// monster.hpp - define a class for monsters

#pragma once

#include "actor.hpp"
#include "engine.hpp"

#include "libtcod.hpp"

class Monster : public Actor {
private:
	// TODO: Djkstra map to make moves

public:
	// Constructor
	Monster(int x, int y, int ch, const TCODColor& colour,
			int health, int damage);

	// Stats
	// Damage - the amount of damage this creature attacks with
	int damage;

	// Calculate next move
	bool Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
		std::shared_ptr<Map> map) override;
};
