#include "player.h"

Player::Player(void)
{
	playerTexture.loadFromFile("resources/img/player2.png");
	playerSprite.setTexture(playerTexture);
	shadowSprite.setTexture(playerTexture);
	attackAnimTexture.loadFromFile("resources/img/anim1.png");
	attackAnimSprite.setTexture(attackAnimTexture);
	xPos = 0;
	yPos = 0;
	height = 29;
	width = 22;
	frameCounter = 0;
	animFrameCounter = 0;
	movingDir = 3;	
	playerSprite.setPosition(xPos, yPos);
	playerSprite.setTextureRect(sf::IntRect(0, 0, width, height));

	shadowSprite.setPosition(xPos, yPos);
	shadowSprite.setTextureRect(sf::IntRect(0, 0, width, height));
	shadowSprite.setColor(sf::Color(0, 0, 0, 125));
	shadowSprite.setRotation(45);
	shadowSprite.rotate(10);

	attackAnimSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));

	moving = false;
	attacking = false;
	attacked = false;
	running = false;
	canRun = true;

	attackedFrameCounter = 0;
	minHP = 0;
	maxHP = 1;
	maxSTA = 1;
	currSTA = 1;

	weaponSlot = 0;
	gunSlot = 0;
	projSlot = 0;

	for(int i = 0; i < MAX_INVENTORY_ITEMS; i++)
	{
		invArr[i].amount = 0;
		invArr[i].index = 0;
	}

	navigatingInv = false;
	openedInvMenu = false;
	swapping = false;
	swappingSlot = 0;

	currMenuSelected = 0;

	//HUD MENU HARDCODED
	hudFont.loadFromFile("resources/fonts/segoeui.ttf");
	hudHP.setPosition(50, 600);
	hudHP.setFillColor(sf::Color::Red);
	hudHP.setSize(sf::Vector2f(150 * minHP / maxHP, 16));
	hudSTA.setPosition(50, 620);
	hudSTA.setFillColor(sf::Color::Green);
	hudSTA.setSize(sf::Vector2f(150 * currSTA / maxSTA, 16));
	hudHPText.setCharacterSize(16);
	hudHPText.setFont(hudFont);
	hudHPText.setColor(sf::Color::White);
	hudHPText.setPosition(52, 600);
	hudHPText.setString(std::to_string(minHP) + " / " + std::to_string(maxHP));
	//HUD MENU HARDCODED
}

Player::~Player(void)
{
}

sf::Sprite Player::getSprite()
{
	return playerSprite;
}

float Player::getPosX()
{
	return xPos;
}

float Player::getPosY()
{
	return yPos;
}

int Player::getHeight()
{
	return height;
}

int Player::getWidth()
{
	return width;
}

int Player::getMovingDir()
{
	return movingDir;
}

bool Player::isAttacking()
{
	return attacking;
}

bool Player::isRunning()
{
	return running;
}

bool Player::runAvailable()
{
	return canRun;
}

sf::Sprite Player::getAnimSprite()
{
	return attackAnimSprite;
}

sf::Sprite Player::getShadowSprite()
{
	return shadowSprite;
}

int Player::getWeaponSlot()
{
	return weaponSlot;
}

int Player::getGunSlot()
{
	return gunSlot;
}

int Player::getProjSlot()
{
	return projSlot;
}

int Player::getMinHP()
{
	return minHP;
}

int Player::getMaxHP()
{
	return maxHP;
}

int Player::getMaxSTA()
{
	return maxSTA;
}

void Player::move(int dir)
{
	switch(dir)
	{
		case 0:
			//LEFT
			if(!running)
				xPos--;
			else
				xPos -= 2;
			break;
		case 1:
			//RIGHT
			if(!running)
				xPos++;
			else
				xPos += 2;
			break;
		case 2:
			//UP
			if(!running)
				yPos--;
			else
				yPos -= 2;
			break;
		case 3:
			//DOWN
			if(!running)
				yPos++;
			else
				yPos += 2;
			break;
	}
	movingDir = dir;
}

void Player::update()
{
	playerSprite.setPosition(xPos, yPos);
	shadowSprite.setPosition(xPos + 29, yPos - 3);

	if(running)
	{
		currSTA--;
		if(currSTA == 0)
		{
			running = false;
			canRun = false;
		}
	}

	if(!canRun)
	{
		currSTA++;
		if(currSTA == maxSTA)
		{
			canRun = true;
		}
	}

	if(currSTA > maxSTA)
		currSTA = maxSTA;

	hudSTA.setSize(sf::Vector2f(150 * currSTA / maxSTA, 16));

	if(!attacking)
	{
		switch(movingDir)
		{
			case 0: //LEFT
				attackAnimSprite.setPosition(xPos - 15, yPos);
				break;

			case 1: //RIGHT
				attackAnimSprite.setPosition(xPos + 15, yPos);
				break;

			case 2: //UP
				attackAnimSprite.setPosition(xPos, yPos - 15);
				break;

			case 3: //DOWN
				attackAnimSprite.setPosition(xPos, yPos + 15);
				break;
		}
	}
	frameCounter++;

	switch(movingDir)
	{
		case 0: //LEFT
			if(!moving) {
				playerSprite.setTextureRect(sf::IntRect(0 * width, 2 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(0 * width, 2 * height, width, height));

			} else if(frameCounter < 30) {
				playerSprite.setTextureRect(sf::IntRect(2 * width, 2 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(2 * width, 2 * height, width, height));

			} else {
				playerSprite.setTextureRect(sf::IntRect(1 * width, 2 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(1 * width, 2 * height, width, height));
			}
			break;

		case 1: //RIGHT
			if(!moving) {
				playerSprite.setTextureRect(sf::IntRect(2 * width, 3 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(2 * width, 3 * height, width, height));

			} else if(frameCounter < 30) {
				playerSprite.setTextureRect(sf::IntRect(1 * width, 3 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(1 * width, 3 * height, width, height));

			} else {
				playerSprite.setTextureRect(sf::IntRect(0 * width, 3 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(0 * width, 3 * height, width, height));
			}
			break;

		case 2: //UP
			if(!moving) {
				playerSprite.setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));

			} else if(frameCounter < 30) {
				playerSprite.setTextureRect(sf::IntRect(2 * width, 0 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(2 * width, 0 * height, width, height));

			} else {
				playerSprite.setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(1 * width, 0 * height, width, height));
			}
			break;

		case 3: //DOWN
			if(!moving) {
				playerSprite.setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));

			} else if(frameCounter < 30) {
				playerSprite.setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(2 * width, 1 * height, width, height));

			} else {
				playerSprite.setTextureRect(sf::IntRect(1 * width, 1 * height, width, height));
				shadowSprite.setTextureRect(sf::IntRect(1 * width, 1 * height, width, height));
			}
			break;
	}

	if(attacking)
	{
		animFrameCounter++;
		//play attacking animation
		if (animFrameCounter < 10)
			attackAnimSprite.setTextureRect(sf::IntRect(0, 0, 40, 40));
		else if (animFrameCounter < 20)
			attackAnimSprite.setTextureRect(sf::IntRect(0, 40, 40, 40));
		else if (animFrameCounter < 30)
			attackAnimSprite.setTextureRect(sf::IntRect(0, 80, 40, 40));
		else
			attackAnimSprite.setTextureRect(sf::IntRect(0, 120, 40, 40));
	}

	if(attacked)
	{
		attackedFrameCounter++;
		playerSprite.setColor(sf::Color(attackedFrameCounter * 5, 0, 0));

		if(attackedFrameCounter > 40)
		{
			attackedFrameCounter = 0;
			attacked = false;
			playerSprite.setColor(sf::Color(255, 255, 255));
		}
	}

	if (frameCounter > 60)
		frameCounter = 0;

	if (animFrameCounter > 40)
	{
		attacking = false;
		animFrameCounter = 0;
	}


	//HUD MENU UPDATES
	hudHP.setSize(sf::Vector2f(150 * minHP / maxHP, 16));
	hudHPText.setString(std::to_string(minHP) + " / " + std::to_string(maxHP));
}

void Player::setMoving(bool val)
{
	moving = val;
}

void Player::setAttacking(bool val)
{
	attacking = val;
}

void Player::setRunning(bool val)
{
	running = val;
}

void Player::setRunAvailable(bool val)
{
	canRun = val;
}

void Player::setHeading(int dir)
{
	switch(dir)
	{
		case 0: //LEFT
			playerSprite.setTextureRect(sf::IntRect(0 * width, 2 * height, width, height));
			shadowSprite.setTextureRect(sf::IntRect(0 * width, 2 * height, width, height));
			break;

		case 1: //RIGHT
			playerSprite.setTextureRect(sf::IntRect(0 * width, 3 * height, width, height));
			shadowSprite.setTextureRect(sf::IntRect(0 * width, 3 * height, width, height));
			break;

		case 2: //UP
			playerSprite.setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));
			shadowSprite.setTextureRect(sf::IntRect(0 * width, 0 * height, width, height));
			break;

		case 3: //DOWN
			playerSprite.setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));
			shadowSprite.setTextureRect(sf::IntRect(0 * width, 1 * height, width, height));
			break;
	}

	movingDir = dir;
}

void Player::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Player::setWeaponSlot(int val)
{
	weaponSlot = val;
}

void Player::setGunSlot(int val)
{
	gunSlot = val;
}

void Player::setProjSlot(int val)
{
	projSlot = val;
}

void Player::setNavigatingInv(bool val)
{
	navigatingInv = val;
}

void Player::setNavigatingInvMenu(bool val)
{
	openedInvMenu = val;
}

void Player::clearInventory() //when the player dies
{
	for(int i = 0; i < MAX_INVENTORY_ITEMS; i++)
	{
		invArr[i].index = 0;
		invArr[i].amount = 0;
	}
}

void Player::addItem(int itemIndex, int amount)
{
	int i = 0;
	while(invArr[i].index != 0 && i < MAX_INVENTORY_ITEMS)
	{
		i++;
	}

	if(i < MAX_INVENTORY_ITEMS)
	{
		invArr[i].index = itemIndex;
		invArr[i].amount = amount;
	}
}

bool Player::hasItem(int itemIndex, int amount)
{
	int i = 0;
	while(((invArr[i].index != itemIndex) || (invArr[i].amount < amount)) && (i < MAX_INVENTORY_ITEMS))
	{
		i++;
	}

	if(i < MAX_INVENTORY_ITEMS)
	{
		return true;
	}

	return false;
}

void Player::removeItem(int itemIndex, int amount)
{
	int i = 0;
	while(invArr[i].index != itemIndex && i < MAX_INVENTORY_ITEMS)
	{
		i++;
	}

	if(i < MAX_INVENTORY_ITEMS)
	{
		invArr[i].amount -= amount;
		if(invArr[i].amount <= 0)
		{
			invArr[i].index = 0;
			invArr[i].amount = 0;
		}
	}
}

void Player::removeItemSlot(int slot)
{
	int i = 0, auxInd, auxAm;
	while(i < MAX_INVENTORY_ITEMS && i != slot)
	{
		i++;
	}

	if(i == slot)
	{
		invArr[i].index = 0;
		invArr[i].amount = 0;
	
		i++;

		while(i < MAX_INVENTORY_ITEMS)
		{
			//rearrange the inventory
			invArr[i-1].index = invArr[i].index;
			invArr[i-1].amount = invArr[i].amount;

			i++;
		}
	}
}

void Player::swap(int slot)
{
	//swap the item in the swapping slot with the item in the parameter slot
	int auxIndex, auxAmount, auxI;
	int i = 0;

	while(i < MAX_INVENTORY_ITEMS && i < swappingSlot)
	{
		i++;
	}

	if(i == swappingSlot)
	{
		auxI = i;
	}

	i = 0;

	while(i < MAX_INVENTORY_ITEMS && i < slot)
	{
		i++;
	}

	if(i == slot)
	{
		auxIndex = invArr[i].index;
		auxAmount = invArr[i].amount;

		invArr[i].amount = invArr[auxI].amount;
		invArr[i].index = invArr[auxI].index;

		invArr[auxI].amount = auxAmount;
		invArr[auxI].index = auxIndex;
	}
}

int Player::getItem(int itemNumber) //to render the inventory
{
	return invArr[itemNumber].index;
}

int Player::getItemAmount(int itemNumber) //to render the inventory
{
	return invArr[itemNumber].amount;
}

bool Player::getNavigatingInv() //no need to be in the player class but whatever
{
	return navigatingInv;
}

bool Player::getNavigatingInvMenu() //no need to be in the player class but whatever
{
	return openedInvMenu;
}

void Player::setCurrMenuSelected(int val) //no need to be in the player class but whatever
{
	currMenuSelected = val;
}

int Player::getCurrMenuSelected() //no need to be in the player class but whatever
{
	return currMenuSelected;
}

void Player::setSwapping(bool val)
{
	swapping = val;
}

void Player::setSwappingSlot(int val)
{
	swappingSlot = val;
}

bool Player::getSwapping()
{
	return swapping;
}
	
int Player::getSwappingSlot()
{
	return swappingSlot;
}

void Player::setAttacked(int dmg)
{
	attacked = true;

	minHP -= dmg;

	if(minHP <= 0)
	{
		minHP = 0;
	}
}

void Player::setMinHP(int val)
{
	minHP = val;
}

void Player::setMaxHP(int val)
{
	maxHP = val;
}

void Player::setMaxSTA(int val)
{
	maxSTA = val;
	currSTA = val;
}

bool Player::isDead()
{
	return(minHP <= 0);
}

sf::RectangleShape Player::getHudHP()
{
	return hudHP;
}

sf::RectangleShape Player::getHudSTA()
{
	return hudSTA;
}

sf::Text Player::getHudHPText()
{
	return hudHPText;
}