#pragma once
#include "world.h"

const int MAX_INVENTORY_ITEMS = 20;
const int ITEM_BULLET = 2;

class Player
{
public:
	Player(void);
	~Player(void);

	sf::Sprite getSprite();
	float getPosX();
	float getPosY();
	int getHeight();
	int getWidth();
	int getMovingDir();
	bool isAttacking();
	bool isRunning();
	bool runAvailable();
	sf::Sprite getAnimSprite();
	sf::Sprite getShadowSprite();

	//INVENTORY FUNCTIONS
	int getWeaponSlot();
	int getGunSlot();
	int getProjSlot();

	void move(int dir);
	void update();
	void setMoving(bool val);
	void setAttacking(bool val);
	void setRunning(bool val);
	void setRunAvailable(bool val);
	void setHeading(int dir);
	void setPosition(int x, int y);

	//INVENTORY FUNCTIONS
	void setWeaponSlot(int val);
	void setGunSlot(int val);
	void setProjSlot(int val);
	void setNavigatingInv(bool val);
	void setNavigatingInvMenu(bool val);
	void addItem(int itemIndex, int amount);
	bool hasItem(int itemIndex, int amount);
	void removeItem(int itemIndex, int amount);
	void removeItemSlot(int slot);
	int getItem(int itemNumber);
	int getItemAmount(int itemNumber);
	bool getNavigatingInv();
	bool getNavigatingInvMenu();
	void clearInventory();
	void setSwapping(bool val);
	void setSwappingSlot(int val);
	bool getSwapping();
	int getSwappingSlot();
	void swap(int slot);

	//PAUSE MENU
	void setCurrMenuSelected(int val);
	int getCurrMenuSelected();

	//BATTLE
	void setAttacked(int dmg);
	void setMinHP(int val);
	void setMaxHP(int val);
	void setMaxSTA(int val);
	bool isDead();

	int getMinHP();
	int getMaxHP();
	int getMaxSTA();

	//HUD MENU
	sf::RectangleShape getHudHP();
	sf::RectangleShape getHudSTA();
	sf::Text getHudHPText();

private:
	int height, width, animFrameCounter, frameCounter, movingDir;
	float xPos, yPos;
	sf::Texture playerTexture;
	sf::Texture attackAnimTexture;
	sf::Sprite playerSprite;
	sf::Sprite shadowSprite;
	sf::Sprite attackAnimSprite;
	bool moving, attacking, attacked, running, canRun;
	int attackedFrameCounter, minHP, maxHP, maxSTA, currSTA;

	//INVENTORY
	int weaponSlot, gunSlot, projSlot;
	
	struct inventory {
		int index;
		int amount;
	};

	inventory invArr[MAX_INVENTORY_ITEMS];

	bool navigatingInv;
	bool openedInvMenu;
	bool swapping;
	int swappingSlot;

	//PAUSE MENU
	int currMenuSelected;

	//HUD MENU
	sf::RectangleShape hudHP;
	sf::RectangleShape hudSTA;
	sf::Font hudFont;
	sf::Text hudHPText;
};

