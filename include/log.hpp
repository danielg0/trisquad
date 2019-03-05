// log.hpp - a class that handles messages sent by actors and displays them

#pragma once

#include <string>
#include <vector>

class Log {
private:
	// The log of messages
	std::vector<std::string> log;

	// A vector of new messages added since the last turn
	std::vector<std::string> newLog;

public:
	// Render function
	// Takes the coord of the top left hand corner and the height and width
	void Render(unsigned x, unsigned y, unsigned w, unsigned h) const;

	// Log message
	void LogMsg(std::string message);

	// Push all logs onto the main log
	// ie. indicate the messages have been read (called every turn)
	void Push();
};
