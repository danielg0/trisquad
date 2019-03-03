// engine.cpp - implement the engine class

#include "engine.hpp"

#include "actor.hpp"
#include "map.hpp"

#include "libtcod.hpp"

#include <array>
#include <memory>
#include <vector>

// Constructor
Engine::Engine() {
	// Setup window and set frame rate
	TCODConsole::initRoot(80, 55, "TriSquad", false);
	TCODSystem::setFps(30);

	// Create map
	map = std::make_unique<Map>(80, 50, this);

	// Create actor
	// Get room to place in
	auto pos = map->GetRoom(true);

	// Random point in room
	auto x = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
	auto y = TCODRandom::getInstance()->getInt(pos[1], pos[3]);

	// Make actor
	auto test = std::make_shared<Actor>(x, y, '@', TCODColor::white);
	actors.push_back(test);
	player = test;

	// Calculate FOV
	map->ComputeFOV();
}

// Render function
void Engine::Render() const {
	// Clear screen
	TCODConsole::root->clear();

	map->Render();

	// Render all actors
	for(auto i : actors) {
		// TODO: Calculate actor position in scene
		i->Render();
	}

	// Output to window
    TCODConsole::flush();
}

// Update function
void Engine::Update() {
	// Take user input, and store in key
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	// Create bool value to check if fov is recalculated
	auto recalcFov = false;

	// Perform action
	switch(key.vk) {
		// Move if there isn't a tile in the way
		case TCODK_UP:
			if(!map->IsWall(player->x, player->y - 1)) {
				--(player->y);
				recalcFov = true;
			}
			break;
		case TCODK_DOWN:
			if(!map->IsWall(player->x, player->y + 1)) {
				++(player->y);
				recalcFov = true;
			}
			break;
		case TCODK_LEFT:
			if(!map->IsWall(player->x - 1, player->y)) {
				--(player->x);
				recalcFov = true;
			}
			break;
		case TCODK_RIGHT:
			if(!map->IsWall(player->x + 1, player->y)) {
				++(player->x);
				recalcFov = true;
			}
			break;
		default: break;
	}

	// Recalc fov if player has moved
	if(recalcFov) {
		map->ComputeFOV();
	}
}
