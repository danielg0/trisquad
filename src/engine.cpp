// engine.cpp - implement the engine class

#include "engine.hpp"

#include "actor.hpp"
#include "map.hpp"
#include "monster.hpp"
#include "player.hpp"

#include "libtcod.hpp"

#include <array>
#include <memory>
#include <string>
#include <vector>

// Constructor
Engine::Engine() {
	// Setup window and set frame rate
	TCODConsole::initRoot(80, 55, "TriSquad", false);
	TCODSystem::setFps(30);

	// Setup game state
	gameLost = false;

	// Set initial level
	level = 0;

	// Create log
	log = std::make_shared<Log>();

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
		int mX, mY;

		do {
			// Get room that isn't the start
			pos = map->GetRoom(false);

			// Get random x/y coord
			mX = TCODRandom::getInstance()->getInt(pos[0], pos[2]);
			mY = TCODRandom::getInstance()->getInt(pos[1], pos[3]);
		} while(ContainsActor(mX, mY));

		auto monster = std::make_shared<Monster>(mX, mY, 'r', TCODColor::red, 10, 1);
		actors->push_back(monster);
	}

	// Output level number
	++level;
	log->LogMsg("Welcome To Level " + std::to_string(level));
}

// Tile contains actor
bool Engine::ContainsActor(int x, int y) {
	auto result = false;

	// Loop over all actors
	for(auto i : *actors) {
		if(i->x == x && i->y == y) {
			result = true;
		}
	}

	return result;
}

// Render function
void Engine::Render() const {
	// Clear screen
	TCODConsole::root->clear();

	// Render map
	map->Render();

	// Render all actors
	for(auto i : *actors) {
		// Check if actor is in fov
		if(map->InFov(i->x, i->y)) {
			i->Render();
		}
	}

	// Render log
	log->Render(0, 50, 80, 5);

	// Output to window
    TCODConsole::flush();
}

// Update function
void Engine::Update() {
	// Create bool value to track whether player moved
	auto moved = player->Update(actors, map, log);

	// Recalc fov if player has moved and then carry out enemy turn
	if(moved) {
		// Flush log messages
		log->Push();

		// Check if player stood on staircase
		if(map->OnStaircase(player->x, player->y)) {
			// Create new level, then exit update loop
			// Stops enemies attacking player who has dissapeared
			NewLevel();
			return;
		}

		// Iterate over all actors that aren't the player
		for(auto i : *actors) {
			if(i != player) {
				i->Update(actors, map, log);
			}
		}

		// Recalculate player field of view
		map->ComputeFOV(player->x, player->y);

		// See if any enemies died
		for(auto i = actors->begin(); i != actors->end(); ++i) {
			if((*i)->health <= 0) {
				// Normal monster - delete it
				if(*i != player) {
					if(map->InFov((*i)->x, (*i)->y)) {
						log->LogMsg("Enemy died");
					}

					i = actors->erase(i);
					if(i == actors->end()) { break; }
				}
				// Player - end game
				else {
					log->LogMsg("You died");
					gameLost = true;
				}
			}
		}
	}
}
