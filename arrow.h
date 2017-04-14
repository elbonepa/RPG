#pragma once
#include "item.h"
#include <time.h>

const int MAX_ARROWS = 5;
const int LIFETIME = 5000;

class Arrow
{
public:
	Arrow(void);
	~Arrow(void);

	void setShotBy(int val);
	void setDamage(int val);
	void setKnockBack(int val);
	void setDir(int val);

	int getShotBy();
	int getDamage();
	int getKnockBack();
	float getPosX();
	float getPosY();
	int getDir();
	sf::Sprite getSprite();

	void update();
	void setPosition(int x, int y);

private:
	int shotBy, damage, knockback, dir; //shotby: 1 = player, 2 = NPC, 0 = not active
	float xPos, yPos, angleChance;
	sf::Texture arrowTexture;
	sf::Sprite arrowSprite;
	sf::Clock lifeTime;
};

