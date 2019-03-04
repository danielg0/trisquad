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

	// Initialise array of actors
	actors = std::make_shared<std::vector<std::shared_ptr<Actor>>>();

	// Create player
	auto actor = std::make_shared<Player>(0, 0, '@', TCODColor::white);

	// Add to actors list and player variable
	actors->push_back(actor);
	player = actor;

	// Create a new level
	NewLevel();
}

// Create a level function
void Engine::NewLevel() {
	// Create map
	map = std::make_unique<Map>(80, 50);

	// Clear array of actors and add player again
	actors->clear();
	actors->push_back(player);

	// Get room to place actor in
	auto pos = map->GetRoom(true);

	// Assign andom point in room to the players position
	auto x = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
	auto y = TCODRandom::getInstance()->getInt(pos[1], pos[3]);
	player->x = x;
	player->y = y;

	// Calculate player's FOV
	map->ComputeFOV(x, y);

	// Create some monsters
	auto monsterCount = 10;
	for(int i = 0; i < monsterCount; ++i) {
		// Get room that isn't the start
		pos = map->GetRoom(false);

		// Get random x/y coord
		auto x = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
		auto y = TCODRandom::getInstance()->getInt(pos[1], pos[3]);

		auto monster = std::make_shared<Monster>(x, y, 'r', TCODColor::red);
		actors->push_back(monster);
	}
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
		// Check if player stood on staircase
		if(map->OnStaircase(player->x, player->y)) {
			// Create new level, then exit update loop
			// Stops enemies attacking player who has dissapeared
			NewLevel();
			return;
		}

		map->ComputeFOV(player->x, player->y);

		// Iterate over all actors that aren't the player
		for(auto i : *actors) {
			if(i != player) {
				i->Update(actors, map);
			}
		}
	}
}
