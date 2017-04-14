#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>

const int WORLD_MAX_X = 500;
const int WORLD_MAX_Y = 500;
const int TILE_SIZE = 16;

const int MAX_NPCS = 100;

const int TILE_FLOWER = 0;
const int TILE_GRASS = 1;

//FOR LAYER TWO
const int TILE_NONE = 0;

const int TILE_EMPTY = -1;

class World
{
public:
	World(void);
	~World(void);

	void load();
	void loadTileSprite(int x, int y, int sprite_type);

	sf::Sprite getTileSprite();
	int layer1[WORLD_MAX_X][WORLD_MAX_Y];
	int layer2[WORLD_MAX_X][WORLD_MAX_Y];
	int bloqLayer[WORLD_MAX_X][WORLD_MAX_Y];

private:
	sf::Texture spriteSheet;
	sf::Sprite tileSprite;
	std::string path;
};

