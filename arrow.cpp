#include "arrow.h"

Arrow::Arrow(void)
{
	damage = 0;
	knockback = 0;
	shotBy = 0;
	arrowTexture.loadFromFile("resources/img/arrow.png");
	arrowSprite.setTexture(arrowTexture);
}

Arrow::~Arrow(void)
{
}

void Arrow::setShotBy(int val)
{
	shotBy = val;
}

void Arrow::setKnockBack(int val)
{
	knockback = val;
}

void Arrow::setDamage(int val)
{
	damage = val;
}

void Arrow::setDir(int val)
{
	dir = val;
}

int Arrow::getShotBy()
{
	return shotBy;
}

int Arrow::getKnockBack()
{
	return knockback;
}

int Arrow::getDamage()
{
	return damage;
}

sf::Sprite Arrow::getSprite()
{
	return arrowSprite;
}

float Arrow::getPosX()
{
	return xPos;
}

float Arrow::getPosY()
{
	return yPos;
}

int Arrow::getDir()
{
	return dir;
}

void Arrow::update()
{
	switch(dir)
	{
		case 0: //LEFT
			xPos -= 3;
			yPos += angleChance / 3;
			break;

		case 1: //RIGHT
			xPos += 3;
			yPos += angleChance / 3;
			break;

		case 2: //UP
			yPos -= 3;
			xPos += angleChance / 3;
			break;

		case 3: //DOWN
			yPos += 3;
			xPos += angleChance / 3;
			break;
	}
	arrowSprite.setPosition(xPos, yPos);
	if(lifeTime.getElapsedTime().asMilliseconds() > LIFETIME)
	{
		shotBy = 0; //kill the arrow
		xPos = 0;
		yPos = 0;
	}
}

void Arrow::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
	arrowSprite.setPosition(xPos, yPos);
	lifeTime.restart();

	srand(time(NULL));
	angleChance = rand() % 9 + 1;
	if(angleChance <= 3)
		angleChance = 0;
	else if(angleChance <= 6)
		angleChance = 1;
	else
		angleChance = -1;
}