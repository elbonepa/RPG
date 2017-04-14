#pragma once
#include "player.h"

const int MAX_NPC_TEXTS = 10;

class NPC
{
public:
	NPC(void);
	~NPC(void);

	void setName(std::string nick);
	void setPosition(int x, int y);
	void setNumTexts(int num);
	void setTextArray(int index, std::string text);
	void setHostile(bool val);
	void setMoving(bool val);
	void setAttacked(int attDir, int dmg, int knock);
	void setMaxHP(int val);
	void setAlive(bool val);
	void setDamage(int val);
	void setAttacking(bool val);

	std::string getNameString();
	sf::Text getNameText();
	sf::Text getNameOutline();
	int getPosX();
	int getPosY();
	sf::Sprite getSprite();
	std::string getTextArrayString(int index);
	int getNumberOfTexts();
	bool isHostile();
	bool isAlive();
	bool isAttacking();
	int getWidth();
	int getHeight();
	int getDamage();
	sf::RectangleShape getHPShape();
	sf::RectangleShape getHPShapeOutline();
	sf::Sprite getShadowSprite();

	void update();
	void move(int dir);

private:
	int xPos, yPos, frameCounter, numTexts, width, height, movingDir;
	int attackedFrameCounter, attackedDir, maxHP, currHP, damage, attackingFrameCounter;
	bool attacked, alive, attacking;
	bool hostile, moving;

	sf::Texture NPCTexture;
	sf::Sprite NPCSprite;
	sf::Sprite shadowSprite;
	std::string name;
	std::string textsArray[MAX_NPC_TEXTS];

	sf::Text NPCName;
	sf::Text outLine;
	sf::Font nameFont;

	sf::RectangleShape hpShp;
	sf::RectangleShape hpShpOutline;
};

