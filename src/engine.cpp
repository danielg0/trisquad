// engine.cpp - implement the engine class

#include "engine.hpp"

#include "actor.hpp"
#include "map.hpp"

#include "libtcod.hpp"

#include <memory>
#include <vector>

// Constructor
Engine::Engine() {
	// Setup window and set frame rate
	TCODConsole::initRoot(80, 50, "TriSquad", false);
	TCODSystem::setFps(30);

	// Create map
	map = std::make_unique<Map>(80, 50);

	// Create actor
	auto test = std::make_shared<Actor>(12, 12, '@', TCODColor::white);
	actors.push_back(test);
	player = test;
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

	// Perform action
	switch(key.vk) {
		// Move if there isn't a tile in the way
		case TCODK_UP:
			if(!map->isWall(player->x, player->y - 1)) {
				--(player->y);
			}
			break;
		case TCODK_DOWN:
			if(!map->isWall(player->x, player->y + 1)) {
				++(player->y);
			}
			break;
		case TCODK_LEFT:
			if(!map->isWall(player->x - 1, player->y)) {
				--(player->x);
			}
			break;
		case TCODK_RIGHT:
			if(!map->isWall(player->x + 1, player->y)) {
				++(player->x);
			}
			break;
		default: break;
	}
}
