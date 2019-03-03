// map.cpp - implement map functions

#include "map.hpp"

#include "libtcod.hpp"

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

// Define room min and max size
static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 6;

// Constructor
Map::Map(int width, int height) : explored(width * height),
	map(std::make_unique<TCODMap>(width, height)),
	bsp(std::make_unique<TCODBsp>(0, 0, width - 1, height - 1)),
	width(width), height(height) {

	// Generate level using bsp tree
	bsp->splitRecursive(NULL, 5, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);

	// Call a recursive map generation function
	genMap(bsp.get());
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

// Dig path
void Map::digPath(int x1, int y1, int x2, int y2) {
	// Dig horizontal line at y1
	for(int x = (x1 < x2)? x1: x2; x <= x1 || x <= x2; ++x) {
		dig(x, y1);
	}

	// Dig vertical line at x2
	for(int y = (y1 < y2)? y1: y2; y <= y1 || y <= y2; ++y) {
		dig(x2, y);
	}
}

// Post-order traversal of the bsp tree
void Map::genMap(TCODBsp* ptr) {
	// Traverse left tree if not null
	if(ptr->getLeft() != nullptr) {
		genMap(ptr->getLeft());
	}

	// Traverse right tree
	if(ptr->getRight() != nullptr) {
		genMap(ptr->getRight());
	}

	// If ptr is leaf, make a room
	if(ptr->isLeaf()) {
		// Generate random corner point
		auto x = TCODRandom::getInstance()->getInt(1, ptr->w - ROOM_MIN_SIZE);
		auto y = TCODRandom::getInstance()->getInt(1, ptr->h - ROOM_MIN_SIZE);

		// Generate random width and height
		auto w = TCODRandom::getInstance()->getInt(ROOM_MIN_SIZE, ptr->w - x);
		auto h = TCODRandom::getInstance()->getInt(ROOM_MIN_SIZE, ptr->h - y);

		dig(ptr->x + x, ptr->y + y, ptr->x + x + w - 1, ptr->y + y + h - 1);

		// Set the parameters of this leaf to the random values
		ptr->x = ptr->x + x;
		ptr->y = ptr->y + y;
		ptr->w = w;
		ptr->h = h;
	}
	// Else, draw a path between the two child rooms
	else {
		// Get the midpoint of the two child nodes
		auto x1 = ptr->getLeft()->x + (ptr->getLeft()->w / 2);
		auto y1 = ptr->getLeft()->y + (ptr->getLeft()->h / 2);
		auto x2 = ptr->getRight()->x + (ptr->getRight()->w / 2);
		auto y2 = ptr->getRight()->y + (ptr->getRight()->h / 2);

		digPath(x1, y1, x2, y2);

		// Set this nodes data to the corner of the corridor
		ptr->x = x2;
		ptr->y = y1;
		ptr->w = 0;
		ptr->h = 0;
	}
}

// Map Interrogation
// Tile is wall
bool Map::IsWall(int x, int y) const {
	return !map->isWalkable(x, y);
}

// Tile currently seen
bool Map::InFov(int x, int y) {
	if(map->isInFov(x, y)) {
		explored[x + y * width].explored = true;
		return true;
	}
	else {
		return false;
	}
}

// If tile has previously been seen
bool Map::IsExplored(int x, int y) const {
	return explored[x + y * width].explored;
}

// Return a random room
std::array<int, 4> Map::GetRoom(bool start) {
	// If this is the room to place the player in, return the leftmost leaf from
	// the bsp tree
	if(start) {
		auto ptr = bsp.get();

		// Get leftmost leaf
		while(!ptr->isLeaf()) {
			ptr = ptr->getLeft();
		}

		// Return coords of room
		// array: x1, y1, x2, y2
		auto x = ptr->x;
		auto y = ptr->y;
		return {x, y, x + ptr->w - 2, y + ptr->h - 2};
	}
	else {
		return {0, 0, 0, 0};
	}
}

void Map::ComputeFOV(int x, int y) {
	map->computeFov(x, y,
		10);
}

// Render function
void Map::Render() {
	// TODO: Viewpoint!!

	// Define static colours for tiles
	static const TCODColor darkWall(0, 0, 100);
	static const TCODColor darkGround(50, 50, 150);
	static const TCODColor lightWall(130,110,50);
	static const TCODColor lightGround(200,180,50);

	// Loop over all tiles
	for(int x = 0; x < width; ++x) {
		for(int y = 0; y < height; ++y) {
			// Draw pixel if in fov or discovered
			if(InFov(x, y)) {
				TCODConsole::root->setCharBackground(x, y,
					IsWall(x, y)? lightWall: lightGround);
			}
			else if(IsExplored(x, y)) {
				TCODConsole::root->setCharBackground(x, y,
					IsWall(x, y)? darkWall: darkGround);
			}
		}
	}
}
