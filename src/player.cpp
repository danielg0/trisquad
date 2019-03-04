// player.hpp

#include "player.hpp"

#include "libtcod.hpp"

// Constructor
// Call parent constructor
Player::Player(int x, int y, int ch, const TCODColor& colour) :
	Actor(x, y, ch, colour, Clan::player) {

}

// Update monster position
void Player::Update(std::shared_ptr<std::vector<std::shared_ptr<Actor>>> actors,
	std::shared_ptr<Map> map) {

}
