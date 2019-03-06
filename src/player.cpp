// player.hpp

#include "player.hpp"

#include "log.hpp"
#include "map.hpp"

#include "libtcod.hpp"

#include <algorithm>
#include <memory>
#include <vector>

static int PLAYER_HEALTH = 10;

// Constructor
// Call parent constructor
Player::Player(int x, int y, int ch, const TCODColor& colour) :
	Actor(x, y, ch, colour, PLAYER_HEALTH, Clan::player) {

	// Default damage
	// Todo: change this to a default weapon
	damage = 5;
}

// Attacking function
void Player::Attack(std::shared_ptr<Actor> target) {
	target->health -= damage;
}

// Update monster position
bool Player::Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
	std::shared_ptr<Map> map, std::shared_ptr<Log> log) {
	// Take user input, and store in key
	TCOD_key_t key;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

	// Create values to track change in position
	auto dx = 0;
	auto dy = 0;

	auto moved = false;
	auto typed = true;

	// Perform action
	switch(key.vk) {
		// Move if there isn't a tile in the way
		case TCODK_UP: dy = -1; break;
		case TCODK_DOWN: dy = 1; break;
		case TCODK_LEFT: dx = -1; break;
		case TCODK_RIGHT: dx = 1; break;
		default: typed = false; break;
	}

	// If user didn't type anything, return no move
	if(!typed) {
		return false;
	}

	// If player is attacking wall, return no move
	if(map->IsWall(x + dx, y + dy)) {
		log->LogMsg("You run into a wall");
		return false;
	}

	// Pointer to hold target actor
	std::shared_ptr<Actor> ptr = nullptr;

	for(auto i : *actors) {
		// If actor is on tile that will be moved to
		if(i->x == x + dx && i->y == y + dy) {
			ptr = i;
		}
	}

	// If no actor found, move
	if(ptr == nullptr) {
		x += dx;
		y += dy;
		moved = true;
	}
	// Else if tile contains actor of a type other than this
	else if(ptr->clan != clan) {
		// Attack this actor
		Attack(ptr);
		log->LogMsg("You attack...");
		moved = true;
	}
	// Else that tile contains another actor, so switch places
	else {
		log->LogMsg("You switch places");
		std::swap(x, ptr->x);
		std::swap(y, ptr->y);
		moved = true;
	}

	return moved;
}
