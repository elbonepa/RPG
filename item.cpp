#include "item.h"

Item::Item(void)
{
	itemType = 0;
	knockback = 0;
	damage = 0;
}

Item::~Item(void)
{
}

void Item::setType(int val)
{
	itemType = val;
}

void Item::setKnockBack(int val)
{
	knockback = val;
}

void Item::setDamage(int val)
{
	damage = val;
}

void Item::setIMGPath(std::string val)
{
	imgPath = val;
}

int Item::getType()
{
	return itemType;
}

int Item::getKnockBack()
{
	return knockback;
}

int Item::getDamage()
{
	return damage;
}

std::string Item::getIMGPath()
{
	return imgPath;
}