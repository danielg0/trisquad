// log.cpp - implement the log class

#include "log.hpp"

#include "libtcod.hpp"

#include <string>
#include <vector>

// Render function
void Log::Render(unsigned x, unsigned y, unsigned w, unsigned h) const {
	// Define colours used when drawing
	static const TCODColor oldMessage(150, 150, 150);
	static const TCODColor newMessage(250, 250, 250);
	static const TCODColor background(0, 0, 0);

	// Loop through the different rows
	for(unsigned int row = 0; row < h; ++row) {
		std::string message = "";
		auto colour = oldMessage;

		// Get message
		if(newLog.size() > row) {
			message = newLog.at(newLog.size() - row - 1);
			colour = newMessage;
		}
		else if(log.size() + newLog.size() > row) {
			message = log.at(log.size() + newLog.size() - row - 1);
		}

		// Draw out each character
		for(unsigned int col = 0; col < w; ++col) {
			if(col < message.size()) {
				TCODConsole::root->setChar(x + col, y + row, message[col]);
			}
			else {
				TCODConsole::root->setChar(x + col, y + row, ' ');
			}

			// Draw background and foreground colour
			TCODConsole::root->setCharForeground(x + col, y + row, colour);
			TCODConsole::root->setCharBackground(x + col, y + row, background);
		}
	}
}

// Log message function
void Log::LogMsg(std::string message) {
	// Push onto new log vector
	newLog.push_back(message);
}

// Push logs
void Log::Push() {
	// Push all new log messages onto the log
	log.insert(log.end(), newLog.begin(), newLog.end());

	newLog.clear();
}
