// engine.hpp - define a game engine class

#pragma once

#include "actor.hpp"
#include "log.hpp"
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

	// Pointer to log
	std::shared_ptr<Log> log;

	// Integer holding current state (menu? character selected?)
	int level;

	// Position of view on screen
	int x;
	int y;

public:
	// Constructor
	Engine();

	// Create a new level
	void NewLevel();

	// Whether game lost yet
	bool gameLost;

	// TODO: vector of shared_ptr to all main characters
	std::shared_ptr<Player> player;

	// A tile in the map contains an actor
	bool ContainsActor(int x, int y);

	// Render and update function
	void Update();
	void Render() const;
};
