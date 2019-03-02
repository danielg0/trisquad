// map.cpp - implement map functions

#include "map.hpp"

#include "libtcod.hpp"

#include <algorithm>
#include <memory>
#include <vector>

// Constructor
Map::Map(int width, int height) : exploredTiles(width * height),
	width(width), height(height) {
	map = std::make_unique<TCODMap>(width, height);

	// Dig out a test room
	dig(10, 10, 30, 30);

	// TODO: bsp level gen
}

// Dig out a tile
void Map::dig(int x, int y) {
	// Set tile x, y to be empty and visible through
	map->setProperties(x, y, true, true);
}

// Dig out a room
void Map::dig(int x1, int y1, int x2, int y2) {
	// Switch coords around to get top left and bottom right corner
	if(x2 < x1) {
		std::swap(x1, x2);
	}
	if(y2 < y1) {
		std::swap(y1, y2);
	}

	// Dig out all tiles from x1, y1 to x2, y2
	for(int x = x1; x < x2; ++x) {
		for(int y = y1; y < y2; ++y) {
			dig(x, y);
		}
	}
}

// Map Interrogation
bool Map::isWall(int x, int y) const {
	return !map->isWalkable(x, y);
}

// Render function
void Map::Render() const {
	// TODO: Viewpoint!!

	// Define static colours for tiles
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);

	// Loop over all tiles
	for(int x = 0; x < width; ++x) {
		for(int y = 0; y < height; ++y) {
			// Draw pixel background with colour
			TCODConsole::root->setCharBackground(x, y,
				isWall(x, y)? darkWall: darkGround);
		}
	}
}
