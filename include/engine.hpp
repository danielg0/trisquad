// engine.hpp - define a game engine class

#pragma once

#include "actor.hpp"
#include "map.hpp"

#include "libtcod.hpp"

#include <memory>
#include <vector>

class Engine {
private:
	// Vector of shared pointers to all actors on screen
	std::vector<std::shared_ptr<Actor>> actors;

	// TODO: vector of shared_ptr to all main characters
	std::shared_ptr<Actor> player;

	// Pointer to current map
	std::unique_ptr<Map> map;

	// Integer holding current state (menu? character selected?)

	// Position of view on screen
	int x;
	int y;

public:
	// Constructor
	Engine();

	// Render and update function
	void Update();
	void Render() const;
};
