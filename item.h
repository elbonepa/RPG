#pragma once
#include "textBox.h"

const int MAX_ITEMS = 500;

const int ITEM_SIZE = 32; //for when drawing the inventory

const int ITEM_TYPE_WEAPON = 1;
const int ITEM_TYPE_GUN = 2;
const int ITEM_TYPE_BULLET = 3;

class Item
{
public:
	Item(void);
	~Item(void);

	void setType(int val);
	void setKnockBack(int val);
	void setDamage(int val);
	void setIMGPath(std::string val);

	int getType();
	int getKnockBack();
	int getDamage();
	std::string getIMGPath();

private:
	std::string imgPath;
	int itemType;
	
	//FOR WEAPONS, BULLETS
	int knockback, damage;

	//FOR GUNS
	int gunModifier;
};

