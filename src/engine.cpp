// engine.cpp - implement the engine class

#include "engine.hpp"

#include "actor.hpp"
#include "map.hpp"
#include "monster.hpp"
#include "player.hpp"

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
	map = std::make_unique<Map>(80, 50);

	// Create array of actors
	actors = std::make_shared<std::vector<std::shared_ptr<Actor>>>();

	// Create actor
	// Get room to place in
	auto pos = map->GetRoom(true);

	// Random point in room
	auto x = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
	auto y = TCODRandom::getInstance()->getInt(pos[1], pos[3]);

	// Make actor
	auto test = std::make_shared<Player>(x, y, '@', TCODColor::white);
	actors->push_back(test);
	player = test;

	// Calculate FOV
	map->ComputeFOV(x, y);

	x = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
	y = TCODRandom::getInstance()->getInt(pos[1], pos[3]);
	auto test2 = std::make_shared<Monster>(x, y, 'R', TCODColor::red);
	actors->push_back(test2);
}

// Render function
void Engine::Render() const {
	// Clear screen
	TCODConsole::root->clear();

	map->Render();

	// Render all actors
	for(auto i : *actors) {
		// Check if actor is in fov
		if(map->InFov(i->x, i->y)) {
			i->Render();
		}
	}

	// Output to window
    TCODConsole::flush();
}

// Update function
void Engine::Update() {
	// Take user input, and store in key
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	// Create bool value to track whether player moved
	auto moved = false;

	// Perform action
	switch(key.vk) {
		// Move if there isn't a tile in the way
		case TCODK_UP:
			if(!map->IsWall(player->x, player->y - 1)) {
				--(player->y);
				moved = true;
			}
			break;
		case TCODK_DOWN:
			if(!map->IsWall(player->x, player->y + 1)) {
				++(player->y);
				moved = true;
			}
			break;
		case TCODK_LEFT:
			if(!map->IsWall(player->x - 1, player->y)) {
				--(player->x);
				moved = true;
			}
			break;
		case TCODK_RIGHT:
			if(!map->IsWall(player->x + 1, player->y)) {
				++(player->x);
				moved = true;
			}
			break;
		default: break;
	}

	// Recalc fov if player has moved and then carry out enemy turn
	if(moved) {
		map->ComputeFOV(player->x, player->y);

		// Iterate over all actors that aren't the player
		for(auto i : *actors) {
			if(i != player) {
				i->Update(actors, map);
			}
		}
	}
}
