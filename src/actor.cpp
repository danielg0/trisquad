// actor.cpp - implement the actor class

#include "actor.hpp"

#include "libtcod.hpp"

// Constructor
Actor::Actor(int x, int y, int ch, const TCODColor& colour, Clan clan) : ch(ch),
	colour(colour), clan(clan), x(x), y(y) {

}

// Render function
void Actor::Render() const {
	// Place character and colour of character
	TCODConsole::root->setChar(x, y, ch);
	TCODConsole::root->setCharForeground(x, y, colour);
}
