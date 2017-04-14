#include "world.h"

World::World(void)
{
	path = "resources/world/world.txt";
	if(!spriteSheet.loadFromFile("resources/img/spritesheet.png"))
		std::cout << "Error loading spritesheet texture.";
	tileSprite.setTexture(spriteSheet);

	for(int i = 0; i < WORLD_MAX_Y; i++)
	{
		for(int j = 0; j < WORLD_MAX_X; j++)
		{
			layer1[j][i] = TILE_EMPTY;
		}
	}

	//LAYER TWO
	for(int i = 0; i < WORLD_MAX_Y; i++)
	{
		for(int j = 0; j < WORLD_MAX_X; j++)
		{
			layer2[j][i] = TILE_EMPTY;
		}
	}

	//BLOQ TWO
	for(int i = 0; i < WORLD_MAX_Y; i++)
	{
		for(int j = 0; j < WORLD_MAX_X; j++)
		{
			bloqLayer[j][i] = TILE_NONE;
		}
	}
}

World::~World(void)
{
}

void World::load()
{
	std::ifstream myReadFile;
	int x, y;
	myReadFile.open(path);
	
	myReadFile >> x;
	myReadFile >> y;

	//LAYER ONE
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			myReadFile >> layer1[j][i];
		}
	}

	//LAYER TWO
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			myReadFile >> layer2[j][i];
		}
	}

	//BLOQ LAYER
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			myReadFile >> bloqLayer[j][i];
		}
	}

	myReadFile.close();
}

void World::loadTileSprite(int x, int y, int sprite_type)
{
	switch(sprite_type)
	{
		case TILE_FLOWER:
			tileSprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
			break;
		case TILE_GRASS:
			tileSprite.setTextureRect(sf::IntRect(0, TILE_SIZE, TILE_SIZE, TILE_SIZE));
			break;
	}

	tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
}

sf::Sprite World::getTileSprite()
{
	return tileSprite;
}