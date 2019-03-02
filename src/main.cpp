// main.cpp - setup engine and run main update/draw loop

#include "engine.hpp"

#include "libtcod.hpp"

int main() {
	// Create engine
	Engine engine;

	// While window open
	while(!TCODConsole::isWindowClosed()) {
		engine.Render();
		engine.Update();
	}

	return 0;
}
