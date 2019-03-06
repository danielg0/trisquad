// main.cpp - setup engine and run main update/draw loop

#include "engine.hpp"

#include "libtcod.hpp"

int main() {
	// Create engine
	Engine engine;

	// While window open
	while(!TCODConsole::isWindowClosed() && !engine.gameLost) {
		engine.Render();
		engine.Update();
	}

	// TODO: End screen
	while(!TCODConsole::isWindowClosed()) {
		engine.Render();
		TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, NULL, NULL);
	}

	return 0;
}
