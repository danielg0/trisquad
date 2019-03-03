// engine.hpp - define a game engine class

#pragma once

#include "actor.hpp"
#include "map.hpp"
#include "player.hpp"

#include "libtcod.hpp"

#include <memory>
#include <vector>

// Forward declare map class
class Map;

class Engine {
private:
	// Vector of shared pointers to all actors on screen
	std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors;

	// Pointer to current map
	std::shared_ptr<Map> map;

	// Integer holding current state (menu? character selected?)

	// Position of view on screen
	int x;
	int y;

public:
	// Constructor
	Engine();

	// TODO: vector of shared_ptr to all main characters
	std::shared_ptr<Player> player;

	// Render and update function
	void Update();
	void Render() const;
};
