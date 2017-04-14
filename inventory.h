#pragma once
#include "arrow.h"

class Inventory
{
public:
	Inventory(void);
	~Inventory(void);

	void prepare(int amount, std::string path, float aux, int i);
	void setShade(sf::Color shd);

	void prepareMenu(float aux, int sel);

	void setCurrSelected(int val);
	int getCurrSelected();

	void setCurrSelMenu(int val);
	int getCurrSelMenu();

	sf::Sprite getSprt();
	sf::Text getTxt();
	sf::RectangleShape getMenu();

	sf::Text getMoveTxt();
	sf::Text getEquipTxt();
	sf::Text getDropTxt();

private:
	sf::RectangleShape invent;
	sf::RectangleShape invMenu;
	sf::Texture itemText;
	sf::Sprite itemSprt;
	sf::Text amntTxt;
	sf::Text menuTxt1;
	sf::Text menuTxt2;
	sf::Text menuTxt3;
	sf::Font auxFnt;

	int currSel;
	int currSelMenu;
};

