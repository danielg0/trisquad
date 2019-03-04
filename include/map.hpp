// map.hpp - define a map class

#pragma once

#include "libtcod.hpp"

#include <array>
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
	std::vector<Tile> explored;

	// Pointer to a TCODMap to calculate FOV
	std::unique_ptr<TCODMap> map;

	// BSP for level generation
	std::unique_ptr<TCODBsp> bsp;

	// Location of the staircase to the next level
	int endX;
	int endY;

	// Map editing functions
	// Dig single tile
	void dig(int x, int y);

	// Dig rectange
	void dig(int x1, int y1, int x2, int y2);

	// Dig L-path between points
	void digPath(int x1, int y1, int x2, int y2);

	// Dig out rooms in the map using the bsp tree
	// Post-order traversal of the bsp tree
	void genMap(TCODBsp* ptr);

	// Recursive function to get all the rooms off the bsp tree
	void getTreeLeaves(std::shared_ptr<std::vector<TCODBsp*>> results,
		TCODBsp* ptr);

public:
	// Constructor
	Map(int width, int height);

	// Map properties
	int width;
	int height;

	// Map interrogation functions
	bool IsWall(int x, int y) const;
	bool InFov(int x, int y);
	bool IsExplored(int x, int y) const;
	bool OnStaircase(int x, int y) const;

	// Returns a random room to place an item/monster in
	// Takes a boolean value: if true returns the location of the first room, to
	// place the player in, else won't return that room
	std::array<int, 4> GetRoom(bool start);

	// Generate fov
	// Takes the position (TODO: Positions) of the view
	void ComputeFOV(int x, int y);

	// Render function
	void Render();
};
