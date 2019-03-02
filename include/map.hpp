// map.hpp - define a map class

#pragma once

#include "libtcod.hpp"

#include <memory>
#include <vector>

// Struct representing a tile
// Holds whether or not tile has been explored
struct Tile {
	bool explored;
	Tile() : explored(false) {}
};

class Map {
private:
	// Vector of tiles
	std::vector<Tile> exploredTiles;

	// Pointer to a TCODMap to calculate FOV
	std::unique_ptr<TCODMap> map;

	// BSP for level generation
	std::unique_ptr<TCODBsp> bsp;

	// Map editing functions
	// Dig single tile
	void dig(int x, int y);

	// Dig rectange
	void dig(int x1, int y1, int x2, int y2);

	// Dig L-path between points
	void digPath(int x1, int y1, int x2, int y2);

public:
	// Constructor
	Map(int width, int height);

	// Map properties
	int width;
	int height;

	// Map interrogation functions
	bool isWall(int x, int y) const;
	bool inFov(int x, int y) const;
	bool explored(int x, int y) const;

	// Generate fov
	void computeFOV();

	// Render function
	void Render() const;
};
