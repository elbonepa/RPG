#include "inventory.h"

Inventory::Inventory(void)
{
	//REGULAR INVENTORY
	auxFnt.loadFromFile("resources/fonts/segoeui.ttf");
	amntTxt.setFont(auxFnt);
	amntTxt.setCharacterSize(10);
	amntTxt.setColor(sf::Color::Green);

	currSel = 0;
	currSelMenu = 0;

	//SELECTED ITEM MENU
	invMenu.setSize(sf::Vector2f(70, 70));
	invMenu.setFillColor(sf::Color::Green);
	menuTxt1.setCharacterSize(12);
	menuTxt1.setFont(auxFnt);
	menuTxt1.setColor(sf::Color::Black);
	menuTxt2.setCharacterSize(12);
	menuTxt2.setFont(auxFnt);
	menuTxt2.setColor(sf::Color::Black);
	menuTxt3.setCharacterSize(12);
	menuTxt3.setFont(auxFnt);
	menuTxt3.setColor(sf::Color::Black);
}

Inventory::~Inventory(void)
{
}

void Inventory::setCurrSelMenu(int val)
{
	currSelMenu = val;
}

int Inventory::getCurrSelMenu()
{
	return currSelMenu;
}

void Inventory::setCurrSelected(int val)
{
	currSel = val;
}

int Inventory::getCurrSelected()
{
	return currSel;
}

void Inventory::setShade(sf::Color shd)
{
	itemSprt.setColor(shd);
}

void Inventory::prepareMenu(float aux, int sel)
{
	if(aux < 1) {
		invMenu.setPosition((sel + 1) * ITEM_SIZE + 50, 50);
		menuTxt1.setPosition((sel + 1) * ITEM_SIZE + 50 + 1, 50);
		menuTxt1.setString("Move");
		menuTxt2.setPosition((sel + 1) * ITEM_SIZE + 50 + 1, 65);
		menuTxt2.setString("Equip");
		menuTxt3.setPosition((sel + 1) * ITEM_SIZE + 50 + 1, 80);
		menuTxt3.setString("Drop");
	} else if (aux < 2) {
		invMenu.setPosition((5 - sel + 1) * ITEM_SIZE + 50, 82);
		menuTxt1.setPosition((5 - sel + 1) * ITEM_SIZE + 50 + 1, 82);
		menuTxt1.setString("Move");
		menuTxt2.setPosition((5 - sel + 1) * ITEM_SIZE + 50 + 1, 97);
		menuTxt2.setString("Equip");
		menuTxt3.setPosition((5 - sel + 1) * ITEM_SIZE + 50 + 1, 112);
		menuTxt3.setString("Drop");
	} else if (aux < 3) {
		invMenu.setPosition((10 - sel + 1) * ITEM_SIZE + 50, 114);
		menuTxt1.setPosition((10 - sel + 1) * ITEM_SIZE + 50 + 1, 129);
		menuTxt1.setString("Move");
		menuTxt2.setPosition((10 - sel + 1) * ITEM_SIZE + 50 + 1, 144);
		menuTxt2.setString("Equip");
		menuTxt3.setPosition((10 - sel + 1) * ITEM_SIZE + 50 + 1, 159);
		menuTxt3.setString("Drop");
	} else {
		invMenu.setPosition((15 - sel + 1) * ITEM_SIZE + 50, 146);
		menuTxt1.setPosition((15 - sel + 1) * ITEM_SIZE + 50 + 1, 161);
		menuTxt1.setString("Move");
		menuTxt2.setPosition((15 - sel + 1) * ITEM_SIZE + 50 + 1, 176);
		menuTxt2.setString("Equip");
		menuTxt3.setPosition((15 - sel + 1) * ITEM_SIZE + 50 + 1, 191);
		menuTxt3.setString("Drop");
	}

	switch(currSelMenu)
	{
		case 0:
			menuTxt1.setColor(sf::Color::White);
			menuTxt2.setColor(sf::Color::Black);
			menuTxt3.setColor(sf::Color::Black);
			break;

		case 1:
			menuTxt2.setColor(sf::Color::White);
			menuTxt1.setColor(sf::Color::Black);
			menuTxt3.setColor(sf::Color::Black);
			break;

		case 2:
			menuTxt3.setColor(sf::Color::White);
			menuTxt1.setColor(sf::Color::Black);
			menuTxt2.setColor(sf::Color::Black);
			break;
	}
}

void Inventory::prepare(int amount, std::string path, float aux, int i)
{
	amntTxt.setString(std::to_string(amount));
	itemText.loadFromFile(path);
	itemSprt.setTexture(itemText);

	if(aux < 1)
	{
		itemSprt.setPosition(50 + ITEM_SIZE * i, 50);
		amntTxt.setPosition(50 + ITEM_SIZE * i, 50 + 20);
	} else if (aux < 2) { //i = 5 6 7 8 9
		itemSprt.setPosition(50 + ITEM_SIZE * (i-5), 82);
		amntTxt.setPosition(50 + ITEM_SIZE * (i-5), 82 + 20);
	} else if (aux < 3) { //i = 10 11 12 13 14
		itemSprt.setPosition(50 + ITEM_SIZE * (i-10), 114);
		amntTxt.setPosition(50 + ITEM_SIZE * (i-10), 114 + 20);
	} else {
		itemSprt.setPosition(50 + ITEM_SIZE * (i-15), 146);
		amntTxt.setPosition(50 + ITEM_SIZE * (i-15), 146 + 20);
	}
}

sf::Sprite Inventory::getSprt()
{
	return itemSprt;
}

sf::RectangleShape Inventory::getMenu()
{
	return invMenu;
}

sf::Text Inventory::getTxt()
{
	return amntTxt;
}

sf::Text Inventory::getMoveTxt()
{
	return menuTxt1;
}

sf::Text Inventory::getEquipTxt()
{
	return menuTxt2;
}

sf::Text Inventory::getDropTxt()
{
	return menuTxt3;
}