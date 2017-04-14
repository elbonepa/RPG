#include "NPC.h"

NPC::NPC(void)
{
	frameCounter = 0;
	attackedFrameCounter = 0;
	attackingFrameCounter = 0;
	numTexts = 0;
	movingDir = 3;
	height = 21;
	width = 15;
	maxHP = 0;
	currHP = 0;
	damage = 0;
	hostile = false;
	alive = true;
	attacking = false;

	for(int i = 0; i < MAX_NPC_TEXTS; i++)
		textsArray[i] = "";

	NPCTexture.loadFromFile("resources/img/player.png");
	NPCSprite.setTexture(NPCTexture);
	NPCSprite.setTextureRect(sf::IntRect(0, 0, 14, 21));

	nameFont.loadFromFile("resources/fonts/segoeui.ttf");

	NPCName.setFont(nameFont);
	NPCName.setCharacterSize(12);
	NPCName.setColor(sf::Color::Red);

	outLine.setFont(nameFont);
	outLine.setCharacterSize(12);
	outLine.setColor(sf::Color::Black);

	hpShp.setFillColor(sf::Color::Red);
	hpShpOutline.setFillColor(sf::Color(0, 0, 0, 125));

	shadowSprite.setTexture(NPCTexture);

	shadowSprite.setPosition(xPos, yPos);
	shadowSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	shadowSprite.setColor(sf::Color(0, 0, 0, 125));
	shadowSprite.setRotation(45);
	shadowSprite.rotate(10);
}

NPC::~NPC(void)
{
}

void NPC::setName(std::string nick)
{
	NPCName.setString(nick);
	outLine.setString(nick);
	name = nick;
}

void NPC::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void NPC::setNumTexts(int num)
{
	numTexts = num;
}

void NPC::setTextArray(int index, std::string text)
{
	textsArray[index] = text;
}

void NPC::setHostile(bool val)
{
	hostile = val;
}

void NPC::setAlive(bool val)
{
	alive = val;
}

void NPC::setMoving(bool val)
{
	moving = val;
}

void NPC::setAttacked(int attDir, int dmg, int knock)
{
	attacked = true;
	currHP -= dmg;
	if(currHP < 0) currHP = 0;
	if(maxHP == 0) maxHP = 1;
	hpShp.setSize(sf::Vector2f(20 * currHP / maxHP, 3));
	attackedDir = attDir; //DIRECTION THE PLAYER WAS HEADING WHEN ATTACKED
	switch(attackedDir)
	{
		case 0: //LEFT
			xPos -= knock; 
			break;

		case 1: //RIGHT
			xPos += knock;
			break;

		case 2: //UP
			yPos -= knock;
			break;

		case 3: //DOWN
			yPos += knock;
			break;
	}
}

void NPC::setMaxHP(int val)
{
	maxHP = val;
	currHP = val;
	if(maxHP > 0)
	{
		hpShp.setSize(sf::Vector2f(20, 3));
		hpShpOutline.setSize(sf::Vector2f(22, 5));
	}
	else
	{
		hpShp.setSize(sf::Vector2f(20, 0));
		hpShpOutline.setSize(sf::Vector2f(22, 0));
	}
}

void NPC::setDamage(int val)
{
	damage = val;
}

void NPC::setAttacking(bool val)
{
	attacking = val;
}


std::string NPC::getNameString()
{
	return name;
}

int NPC::getPosX()
{
	return xPos;
}

int NPC::getPosY()
{
	return yPos;
}

sf::Sprite NPC::getSprite()
{
	return NPCSprite;
}

sf::Text NPC::getNameText()
{
	return NPCName;
}

sf::Text NPC::getNameOutline()
{
	return outLine;
}

std::string NPC::getTextArrayString(int index)
{
	return textsArray[index];
}

int NPC::getNumberOfTexts()
{
	return numTexts;
}

bool NPC::isHostile()
{
	return hostile;
}

bool NPC::isAlive()
{
	return alive;
}

bool NPC::isAttacking()
{
	return attacking;
}

int NPC::getWidth()
{
	return width;
}

int NPC::getHeight()
{
	return height;
}

sf::RectangleShape NPC::getHPShape()
{
	return hpShp;
}

sf::RectangleShape NPC::getHPShapeOutline()
{
	return hpShpOutline;
}

sf::Sprite NPC::getShadowSprite()
{
	return shadowSprite;
}

int NPC::getDamage()
{
	return damage;
}

void NPC::update()
{
	NPCSprite.setPosition(xPos, yPos);
	shadowSprite.setPosition(xPos + 20, yPos);
	NPCName.setPosition(xPos - (name.length() / 2) * 3, yPos + 20);
	outLine.setPosition(xPos - (name.length() / 2) * 3 + 1, yPos + 20);
	hpShp.setPosition(xPos, yPos - 5);
	hpShpOutline.setPosition(xPos - 1, yPos - 6);

	frameCounter++;

	switch(movingDir)
	{
		case 0: //LEFT
			if(frameCounter < 30 || !moving)
			{
				NPCSprite.setTextureRect(sf::IntRect(2 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(2 * width, 0, width, height));
			}
			else
			{
				NPCSprite.setTextureRect(sf::IntRect(5 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(5 * width, 0, width, height));
			}
			break;

		case 1: //RIGHT
			if(frameCounter < 30 || !moving)
			{
				NPCSprite.setTextureRect(sf::IntRect(8 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(8 * width, 0, width, height));
			}
			else
			{
				NPCSprite.setTextureRect(sf::IntRect(7 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(7 * width, 0, width, height));
			}
			break;

		case 2: //UP
			if(frameCounter < 30 || !moving)
			{
				NPCSprite.setTextureRect(sf::IntRect(1 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(1 * width, 0, width, height));
			}
			else
			{
				NPCSprite.setTextureRect(sf::IntRect(4 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(4 * width, 0, width, height));
			}
			break;

		case 3: //DOWN
			if(frameCounter < 30 || !moving)
			{
				NPCSprite.setTextureRect(sf::IntRect(0 * width, 0, width, height));
				shadowSprite.setTextureRect(sf::IntRect(0 * width, 0, width, height));
			}
			else
			{
				shadowSprite.setTextureRect(sf::IntRect(3 * width, 0, width, height));
				NPCSprite.setTextureRect(sf::IntRect(3 * width, 0, width, height));
			}
			break;
	}

	if (frameCounter > 60)
		frameCounter = 0;

	if(attacked)
	{
		attackedFrameCounter++;
		NPCSprite.setColor(sf::Color(attackedFrameCounter * 5, 0, 0));

		if(attackedFrameCounter > 40)
		{
			attackedFrameCounter = 0;
			attacked = false;
			NPCSprite.setColor(sf::Color(255, 255, 255));
		}
	}

	if(attacking) //HERE WE CAN PUT AN ATTACKING ANIMATION
	{
		attackingFrameCounter++;

		if(attackingFrameCounter > 40)
		{
			attackingFrameCounter = 0;
			attacking = false;
		}
	}

	if(currHP == 0 && hostile)
	{
		alive = false;
	}
}

void NPC::move(int dir)
{
	switch(dir)
	{
		case 0: //LEFT
			xPos -= 1;
			break;

		case 1: //RIGHT
			xPos += 1;
			break;

		case 2: //UP
			yPos -= 1;
			break;

		case 3: //DOWN
			yPos += 1;
			break;
	}

	movingDir = dir;
}
