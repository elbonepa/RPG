#include "inventory.h"
#include <math.h>

const int WINDOW_HEIGHT = 768;
const int WINDOW_WIDTH = 1024;

const int FPS_LIMIT = 60;
const float VIEW_ZOOM = 0.85;

const int GAME_MODE_NORMAL = 1;
const int GAME_MODE_PAUSE = 2;
const int GAME_MODE_CUTSCENE = 3;

float lastTime = 0;

int NUM_NPCS;

int gameMode;

World world;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
sf::View view;

Player player;
NPC npcList[MAX_NPCS];

Item itemList[MAX_ITEMS];

Arrow arrowArr[MAX_ARROWS]; //all the arrows in the WORLD !!

TextBox textBox;

Inventory inv_class; //for drawing the inventory in the pause menu

bool checkCollisionPlayer(int npcIndex, int dir)
{
	sf::FloatRect auxRect;

	switch(dir)
	{
		case 0: //LEFT
			auxRect = sf::FloatRect(npcList[npcIndex].getPosX() - 2, npcList[npcIndex].getPosY(), npcList[npcIndex].getWidth(), npcList[npcIndex].getHeight());
			break;

		case 1: //RIGHT
			auxRect = sf::FloatRect(npcList[npcIndex].getPosX() + 2, npcList[npcIndex].getPosY(), npcList[npcIndex].getWidth(), npcList[npcIndex].getHeight());
			break;

		case 2: //UP
			auxRect = sf::FloatRect(npcList[npcIndex].getPosX(), npcList[npcIndex].getPosY() - 2, npcList[npcIndex].getWidth(), npcList[npcIndex].getHeight());
			break;

		case 3: //DOWN
			auxRect = sf::FloatRect(npcList[npcIndex].getPosX(), npcList[npcIndex].getPosY() + 2, npcList[npcIndex].getWidth(), npcList[npcIndex].getHeight());
			break;
	}

	if(auxRect.intersects(player.getSprite().getGlobalBounds()))
		return true;

	return false;
}

int getNPCPath(int npcIndex)
{
	if(npcList[npcIndex].getPosX() > player.getPosX())
		return 0; //move left
	else if(npcList[npcIndex].getPosX() < player.getPosX())
		return 1; //move right
	else if(npcList[npcIndex].getPosY() > player.getPosY())
		return 2; //move up
	else
		return 3; //move down
}

bool isInViewPort(int npcIndex)
{
	if((abs(npcList[npcIndex].getPosX() - player.getPosX()) <= WINDOW_WIDTH / 2) && (abs(npcList[npcIndex].getPosY() - player.getPosY()) <= WINDOW_HEIGHT / 2))
		return true;

	return false;
}

int getCollisionArrowNPC(int arrowIndex)
{
	for(int i = 0; i < NUM_NPCS; i++)
	{
		if(arrowArr[arrowIndex].getSprite().getGlobalBounds().intersects(npcList[i].getSprite().getGlobalBounds()))
			return i;
	}

	return -1;
}

bool checkCollisionArrowNPC(int arrowIndex)
{
	for(int i = 0; i < NUM_NPCS; i++)
	{
		if(arrowArr[arrowIndex].getSprite().getGlobalBounds().intersects(npcList[i].getSprite().getGlobalBounds()) && npcList[i].isAlive())
			return true;
	}

	return false;
}

bool checkCollisionBlock(int dir)
{
	sf::FloatRect auxRect;

	switch(dir)
	{
		case 0: //LEFT
			if(world.bloqLayer[(int)floor(player.getPosX()) / TILE_SIZE][(int) floor(player.getPosY()) / TILE_SIZE + 1] == 1)
				return true;
			break;

		case 1: //RIGHT
			if(world.bloqLayer[(int)floor(player.getPosX()) / TILE_SIZE + 1][(int) floor(player.getPosY()) / TILE_SIZE + 1] == 1)
				return true;
			break;

		case 2: //UP
			if(world.bloqLayer[(int)floor(player.getPosX()) / TILE_SIZE + 1][(int) floor(player.getPosY()) / TILE_SIZE] == 1)
				return true;
			break;

		case 3: //DOWN
			if(world.bloqLayer[(int)floor(player.getPosX()) / TILE_SIZE][(int) floor(player.getPosY()) / TILE_SIZE + 1] == 1)
				return true;
			break;
	}
	return false;
}

bool checkCollisionNPC(int dir)
{
	sf::FloatRect auxRect;

	switch(dir)
	{
		case 0: //LEFT
			auxRect = sf::FloatRect(player.getPosX() - 2, player.getPosY(), player.getWidth(), player.getHeight());
			break;

		case 1: //RIGHT
			auxRect = sf::FloatRect(player.getPosX() + 2, player.getPosY(), player.getWidth(), player.getHeight());
			break;

		case 2: //UP
			auxRect = sf::FloatRect(player.getPosX(), player.getPosY() - 2, player.getWidth(), player.getHeight());
			break;

		case 3: //DOWN
			auxRect = sf::FloatRect(player.getPosX(), player.getPosY() + 2, player.getWidth(), player.getHeight());
			break;
	}

	for(int i = 0; i < NUM_NPCS; i++)
	{
		if(auxRect.intersects(npcList[i].getSprite().getGlobalBounds()) && npcList[i].isAlive())
			return true;
	}

	return false;
}

int getCollisionNPC(int dir)
{
	sf::FloatRect auxRect;

	switch(dir)
	{
		case 0: //LEFT
			auxRect = sf::FloatRect(player.getPosX() - 2, player.getPosY(), player.getWidth(), player.getHeight());
			break;

		case 1: //RIGHT
			auxRect = sf::FloatRect(player.getPosX() + 2, player.getPosY(), player.getWidth(), player.getHeight());
			break;

		case 2: //UP
			auxRect = sf::FloatRect(player.getPosX(), player.getPosY() - 2, player.getWidth(), player.getHeight());
			break;

		case 3: //DOWN
			auxRect = sf::FloatRect(player.getPosX(), player.getPosY() + 2, player.getWidth(), player.getHeight());
			break;
	}

	for(int i = 0; i < NUM_NPCS; i++)
	{
		
		if(auxRect.intersects(npcList[i].getSprite().getGlobalBounds()))
			return i;
	}

	return -1;
}

void saveUser()
{
	std::ofstream myWriteFile ("resources/data/playerdata.txt", std::ofstream::out);

	myWriteFile << player.getPosX();
	myWriteFile << " ";
	myWriteFile << player.getPosY();
	myWriteFile << "\r\n"; //line jump
	myWriteFile << player.getMinHP();
	myWriteFile << " ";
	myWriteFile << player.getMaxHP();
	myWriteFile << "\r\n"; //line jump
	myWriteFile << player.getMaxSTA();
	myWriteFile << "\r\n"; //line jump
	myWriteFile << player.getWeaponSlot();
	myWriteFile << "\r\n"; //line jump
	myWriteFile << player.getGunSlot();
	myWriteFile << "\r\n"; //line jump
	myWriteFile << player.getProjSlot();
	myWriteFile << "\r\n"; //line jump

	for(int i = 0; i < MAX_INVENTORY_ITEMS; i++)
	{
		myWriteFile << player.getItem(i);
		myWriteFile << " ";
		myWriteFile << player.getItemAmount(i);
		myWriteFile << " ";
	}

	myWriteFile.close();
}

void loadItems()
{
	std::ifstream myReadFile;
	std::string aux, path;
	int num, type, knock, dmg;

	myReadFile.open("resources/data/itemdata.txt");

	myReadFile >> num;
	std::getline(myReadFile, aux); //read the line

	for(int i = 1; i <= num; i++) //ITEMS START ON 1
	{
		myReadFile >> path;
		myReadFile >> type;
		myReadFile >> knock;
		myReadFile >> dmg;
		std::getline(myReadFile, aux); //read the line
		itemList[i].setType(type);
		itemList[i].setKnockBack(knock);
		itemList[i].setDamage(dmg);
		itemList[i].setIMGPath(path);
	}

	myReadFile.close();
}

void loadPlayerData()
{
	std::ifstream myReadFile;
	std::string aux;
	int x, y, weap, gun, proj, item, amount, minhp, maxhp, maxsta;
	myReadFile.open("resources/data/playerdata.txt");

	myReadFile >> x;
	myReadFile >> y;
	std::getline(myReadFile, aux); //read the line
	myReadFile >> minhp;
	myReadFile >> maxhp;
	std::getline(myReadFile, aux); //read the line
	myReadFile >> maxsta;
	std::getline(myReadFile, aux); //read the line
	myReadFile >> weap;
	std::getline(myReadFile, aux); //read the line
	myReadFile >> gun;
	std::getline(myReadFile, aux); //read the line
	myReadFile >> proj;
	std::getline(myReadFile, aux); //read the line

	player.setPosition(x, y);
	player.setMinHP(minhp);
	player.setMaxHP(maxhp);
	player.setMaxSTA(maxsta);
	player.setWeaponSlot(weap);
	player.setGunSlot(gun);
	player.setProjSlot(proj);

	for(int i = 0; i < MAX_INVENTORY_ITEMS; i++)
	{
		myReadFile >> item;
		myReadFile >> amount;
		player.addItem(item, amount);
	}

	myReadFile.close();
}

void loadNPCs()
{
	std::ifstream myReadFile;
	std::string nick;
	std::string aux;
	int x, y, numTexts, hostile, maxhp, dmg;
	std::string texts[MAX_NPC_TEXTS];
	myReadFile.open("resources/world/npcs.txt");
	
	myReadFile >> NUM_NPCS; //first thing we read is the number of NPCs to load

	for(int i = 0; i < NUM_NPCS; i++)
	{
		myReadFile >> x;
		myReadFile >> y;
		std::getline(myReadFile, nick);
		myReadFile >> numTexts;
		npcList[i].setName(nick);
		npcList[i].setPosition(x * TILE_SIZE, y * TILE_SIZE);
		npcList[i].setNumTexts(numTexts);
		std::getline(myReadFile, aux); //read the line

		for(int j = 0; j < numTexts; j++)
		{
			std::getline(myReadFile, texts[j]);
			npcList[i].setTextArray(j, texts[j]);
		}

		myReadFile >> hostile;
		if(hostile == 1)
			npcList[i].setHostile(true);
		else
			npcList[i].setHostile(false);

		std::getline(myReadFile, aux); //read the line
		myReadFile >> maxhp;
		npcList[i].setMaxHP(maxhp);
		std::getline(myReadFile, aux); //read the line
		myReadFile >> dmg;
		npcList[i].setDamage(dmg);
		std::getline(myReadFile, aux); //read the line

		npcList[i].setAlive(true);
	}

	myReadFile.close();
}

void playerDie()
{
	//if the player dies we just reload everything
	world.load();
	loadNPCs();

	//empty the inventory before reloading player data
	player.clearInventory();

	loadPlayerData();
	loadItems();
}

void render(sf::Font auxFnt)
{
	sf::Sprite tileSprite;
	sf::Text renderText;

	//FOR THE PAUSE MENU
	sf::RectangleShape pEff;
	sf::RectangleShape invent;
	sf::RectangleShape menu;
	sf::Texture auxText;
	sf::Sprite auxSprt;
	sf::Text auxTxt;
	//FOR THE PAUSE MENU

	window.clear();

	window.setView(view);

	//RENDER THE FIRST LAYER OF THE MAP
	for(int i = 0; i < WORLD_MAX_Y; i++)
	{
		for(int j = 0; j < WORLD_MAX_X; j++)
		{
			if(world.layer1[j][i] != TILE_EMPTY)
			{
				world.loadTileSprite(j, i, world.layer1[j][i]);
				window.draw(world.getTileSprite());
			}
		}
	}
	//RENDER THE FIRST LAYER OF THE MAP

	//RENDER THE PLAYER
	window.draw(player.getShadowSprite());
	window.draw(player.getSprite());
	if(player.isAttacking())
		window.draw(player.getAnimSprite());
	//RENDER THE PLAYER

	//RENDER NPCS
	for(int i = 0; i < NUM_NPCS; i++)
	{
		//ONLY RENDER THE NPC IF IT'S IN THE USER'S VIEWPORT
		if(isInViewPort(i) && npcList[i].isAlive())
		{
			//RENDER THE NPC SHADOW
			window.draw(npcList[i].getShadowSprite());
			//RENDER THE NPC SHADOW

			//RENDER THE NPC
			window.draw(npcList[i].getSprite());
			//RENDER THE NPC

			//RENDER THE NPC NAME
			window.draw(npcList[i].getNameOutline());
			window.draw(npcList[i].getNameText());
			//RENDER THE NPC NAME

			//RENDER THE NPC HP BAR
			window.draw(npcList[i].getHPShapeOutline());
			window.draw(npcList[i].getHPShape());
			//RENDER THE NPC HP BAR
		}
	}
	//RENDER NPCS

	//RENDER ANY ACTIVE ARROWS
	for(int i = 0; i < MAX_ARROWS; i++)
	{
		if(arrowArr[i].getShotBy() != 0)
		{
			window.draw(arrowArr[i].getSprite());
		}
	}
	//RENDER ANY ACTIVE ARROWS

	//RENDER THE SECOND LAYER OF THE MAP
	for(int i = 0; i < WORLD_MAX_Y; i++)
	{
		for(int j = 0; j < WORLD_MAX_X; j++)
		{
			if(world.layer2[j][i] != TILE_NONE && world.layer2[j][i] != TILE_EMPTY) //0 IN LAYER TWO MEANS NOTHING
			{
				world.loadTileSprite(j, i, world.layer2[j][i]);
				window.draw(world.getTileSprite());
			}
		}
	}
	//RENDER THE SECOND LAYER OF THE MAP

	//HUD
	window.setView(window.getDefaultView());
	
	window.draw(player.getHudHP());
	window.draw(player.getHudHPText());
	window.draw(player.getHudSTA());
	//HUD

	//NPC TEXT RENDERING
	if(textBox.isActive())
	{
		window.setView(window.getDefaultView());
		textBox.setPosAndSize(0, WINDOW_HEIGHT - 180, WINDOW_WIDTH, 130);
		window.draw(textBox.getShape());
		window.draw(textBox.getText());
	}
	//NPC TEXT RENDERING

	//PAUSE RENDERS
	if(gameMode == GAME_MODE_PAUSE)
	{
		float aux;
		window.setView(window.getDefaultView());
		
		pEff.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
		pEff.setPosition(0,0);
		pEff.setFillColor(sf::Color(0, 0, 0, 125));
		window.draw(pEff);

		invent.setSize(sf::Vector2f(5 * ITEM_SIZE, 4 * ITEM_SIZE));
		invent.setPosition(50, 50);
		invent.setFillColor(sf::Color(255, 0, 0, 125));
		window.draw(invent);

		//RENDER THE INVENTORY
		for(int i = 0; i < MAX_INVENTORY_ITEMS; i++)
		{
			aux = i / 5;
			if(player.getItem(i) > 0)
			{
				if(player.getItem(inv_class.getCurrSelected()) == 0)
				{
					inv_class.setCurrSelected(i);
				}
				inv_class.prepare(player.getItemAmount(i), itemList[player.getItem(i)].getIMGPath(), aux, i);

				if(i == inv_class.getCurrSelected() && player.getNavigatingInv())
				{
					auxSprt.setColor(sf::Color(255, 0, 0, 125));
					inv_class.setShade(sf::Color(255, 0, 0, 125));
				} else if(player.getSwapping() && i == player.getSwappingSlot()) {
					auxSprt.setColor(sf::Color(0, 0, 255, 125));
					inv_class.setShade(sf::Color(0, 0, 255, 125));
				} else if((player.getItem(i) == player.getGunSlot()) || (player.getItem(i) == player.getProjSlot()) || (player.getItem(i) == player.getWeaponSlot())) {
					auxSprt.setColor(sf::Color(0, 200, 0, 125));
					inv_class.setShade(sf::Color(0, 200, 0, 125));
				} else {
					auxSprt.setColor(sf::Color(255, 255, 255));
					inv_class.setShade(sf::Color(255, 255, 255));
				}	

				window.draw(inv_class.getSprt());
				window.draw(inv_class.getTxt());
			}

			if(player.getNavigatingInvMenu())
			{
				aux = inv_class.getCurrSelected() / 5;

				inv_class.prepareMenu(aux, inv_class.getCurrSelected());
				window.draw(inv_class.getMenu());
				window.draw(inv_class.getMoveTxt());
				window.draw(inv_class.getDropTxt());
				window.draw(inv_class.getEquipTxt());

			}
		}

		//RENDER THE EQUIPPED ITEM SLOTS
		for(int i = 0; i < 4; i++)
		{
			//4: gun, weapon, armour, algo ma
			auxSprt.setColor(sf::Color(255, 255, 255));

			if(player.getWeaponSlot() > 0)
			{
				auxSprt.setPosition(50, 200);
				auxText.loadFromFile(itemList[player.getWeaponSlot()].getIMGPath());
				auxSprt.setTexture(auxText);
				window.draw(auxSprt);
			} else {
				
			}

			if(player.getGunSlot() > 0)
			{
				auxSprt.setPosition(50 + 40, 200);
				auxText.loadFromFile(itemList[player.getGunSlot()].getIMGPath());
				auxSprt.setTexture(auxText);
				window.draw(auxSprt);
			} else {
				
			}

			if(player.getProjSlot() > 0)
			{
				auxSprt.setPosition(50 + 80, 200);
				auxText.loadFromFile(itemList[player.getProjSlot()].getIMGPath());
				auxSprt.setTexture(auxText);
				window.draw(auxSprt);
			} else {
				
			}
		}

		if(!player.getNavigatingInv())
		{
			invent.setFillColor(sf::Color(0, 0, 0, 125));
			window.draw(invent);
		}

		//RENDER THE PAUSE MENU
		menu.setSize(sf::Vector2f(5 * ITEM_SIZE, 4 * ITEM_SIZE));
		menu.setPosition(400, 50);
		menu.setFillColor(sf::Color(255, 0, 0, 125));
		window.draw(menu);

		auxTxt.setFont(auxFnt);
		auxTxt.setCharacterSize(20);

		if(player.getCurrMenuSelected() == 0 && !player.getNavigatingInv())
		{
			auxTxt.setColor(sf::Color::Green);
		} else {
			auxTxt.setColor(sf::Color::White);
		}

		auxTxt.setPosition(400, 50);
		auxTxt.setString("Save");
		window.draw(auxTxt);

		if(player.getCurrMenuSelected() == 1 && !player.getNavigatingInv())
		{
			auxTxt.setColor(sf::Color::Green);
		} else {
			auxTxt.setColor(sf::Color::White);
		}

		auxTxt.setPosition(400, 72);
		auxTxt.setString("Options");
		window.draw(auxTxt);

		if(player.getCurrMenuSelected() == 2 && !player.getNavigatingInv())
		{
			auxTxt.setColor(sf::Color::Green);
		} else {
			auxTxt.setColor(sf::Color::White);
		}

		auxTxt.setPosition(400, 94);
		auxTxt.setString("Exit");
		window.draw(auxTxt);

		if(player.getNavigatingInv())
		{
			menu.setSize(sf::Vector2f(5 * ITEM_SIZE, 4 * ITEM_SIZE));
			menu.setPosition(400, 50);
			menu.setFillColor(sf::Color(0, 0, 0, 125));
			window.draw(menu);
		}

	}
	//PAUSE RENDERS

    window.display();
}

void update(sf::Clock clock, sf::Font auxFnt)
{
    sf::Event event;
	int i = 0;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			//check for keys and move the player
			if(gameMode == GAME_MODE_NORMAL)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::A:
						if(!textBox.isActive())
						{
							if(checkCollisionNPC(player.getMovingDir()))
							{
								textBox.setActive(true);
								textBox.setCurrRenderText(0);
								textBox.setTextToRender(npcList[getCollisionNPC(player.getMovingDir())].getTextArrayString(textBox.getCurrRenderText()));
								textBox.setCurrRenderText(textBox.getCurrRenderText() + 1);
							}
						}
						else
						{
							if(textBox.getCurrRenderText() < npcList[getCollisionNPC(player.getMovingDir())].getNumberOfTexts())
							{
								textBox.setTextToRender(npcList[getCollisionNPC(player.getMovingDir())].getTextArrayString(textBox.getCurrRenderText()));
								textBox.setCurrRenderText(textBox.getCurrRenderText() + 1);
							}
							else
							{
								textBox.setActive(false);
							}
						}
						break;

					case sf::Keyboard::S:
						if(!player.isAttacking())
						{
							player.setAttacking(true);
							if(checkCollisionNPC(player.getMovingDir()) && npcList[getCollisionNPC(player.getMovingDir())].isHostile())
							{
								npcList[getCollisionNPC(player.getMovingDir())].setAttacked(player.getMovingDir(), itemList[player.getWeaponSlot()].getDamage(), itemList[player.getWeaponSlot()].getKnockBack());
							}
						}
						break;

					case sf::Keyboard::X:
						if(player.runAvailable() && !player.isRunning())
						{
							player.setRunning(true);
						}
						break;

					case sf::Keyboard::Space:
						while(i < MAX_ARROWS)
						{
							if((arrowArr[i].getShotBy() == 0) && (player.getGunSlot() > 0) && (player.getProjSlot() > 0)) //not active arrow
							{
								player.removeItem(player.getProjSlot(), 1);

								arrowArr[i].setShotBy(1); //player
								arrowArr[i].setDir(player.getMovingDir());
								arrowArr[i].setPosition(player.getPosX(), player.getPosY());
								arrowArr[i].setDamage(itemList[player.getProjSlot()].getDamage());
								arrowArr[i].setKnockBack(itemList[player.getProjSlot()].getKnockBack());
								break;
							}
							i++;
						}
						break;

					case sf::Keyboard::Escape:
						gameMode = GAME_MODE_PAUSE;
						player.setNavigatingInv(true);
						break;
				}

			} else if (gameMode == GAME_MODE_PAUSE) {

				//PAUSE BUTTONS
				switch(event.key.code)
				{
					case sf::Keyboard::Escape:
						player.setNavigatingInvMenu(false);
						inv_class.setCurrSelMenu(0);
						gameMode = GAME_MODE_NORMAL;
						break;
						
					case sf::Keyboard::Z:
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu() && !player.getSwapping())
						{
							player.setNavigatingInvMenu(true);
						}

						else if(player.getSwapping())
						{
							player.swap(inv_class.getCurrSelected());
							player.setSwapping(false);
						}

						else if(player.getNavigatingInvMenu())
						{
							switch(inv_class.getCurrSelMenu())
							{
								case 0: // MOVE
									player.setSwapping(true);
									player.setSwappingSlot(inv_class.getCurrSelected());
									break;

								case 1: //EQUIP
									switch(itemList[player.getItem(inv_class.getCurrSelected())].getType())
									{
										case ITEM_TYPE_WEAPON:
											player.setWeaponSlot(player.getItem(inv_class.getCurrSelected()));
											break;

										case ITEM_TYPE_GUN:
											player.setGunSlot(player.getItem(inv_class.getCurrSelected()));
											break;

										case ITEM_TYPE_BULLET:
											player.setProjSlot(player.getItem(inv_class.getCurrSelected()));
											break;
									}
									break;

								case 2: //DROP
									//CHE IF THE ITEM WAS EQUIPPED AND UNEQUIP IT
									if(player.getGunSlot() == player.getItem(inv_class.getCurrSelected()))
									{
										player.setGunSlot(0);
									} else if(player.getWeaponSlot() == player.getItem(inv_class.getCurrSelected()))
									{
										player.setWeaponSlot(0);
									} else if(player.getProjSlot() == player.getItem(inv_class.getCurrSelected()))
									{
										player.setProjSlot(0);
									}
									player.removeItemSlot(inv_class.getCurrSelected());
									break;
							}

							player.setNavigatingInvMenu(false);
							inv_class.setCurrSelMenu(0);
						}

						if(!player.getNavigatingInv())
						{
							switch(player.getCurrMenuSelected())
							{
								case 0: //SAVE
									saveUser();
									break;

								case 1: //OPTIONS
									break;

								case 2: //EXIT
									window.close();
									break;
							}
						}
						break;

					case sf::Keyboard::X:
						if(player.getNavigatingInvMenu())
						{
							player.setNavigatingInvMenu(false);
							inv_class.setCurrSelMenu(0);
						}

						if(player.getSwapping())
						{
							player.setSwapping(false);
						}
						break;

					case sf::Keyboard::Q: //L1
						if(!player.getNavigatingInv())
							player.setNavigatingInv(true);
						break;

					case sf::Keyboard::E: //R1
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu())
							player.setNavigatingInv(false);
						break;

					case sf::Keyboard::Left:
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu() && player.getItem(inv_class.getCurrSelected() - 1) > 0)
						{
							if(inv_class.getCurrSelected() > 0)
							{
								inv_class.setCurrSelected(inv_class.getCurrSelected() - 1);
							}
						}
						break;

					case sf::Keyboard::Right:
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu() && player.getItem(inv_class.getCurrSelected() + 1) > 0)
						{
							if(inv_class.getCurrSelected() < MAX_INVENTORY_ITEMS && player.getItem(inv_class.getCurrSelected() + 1) != 0)
							{
								inv_class.setCurrSelected(inv_class.getCurrSelected() + 1);
							}
						}
						break;

					case sf::Keyboard::Up:
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu())
						{
							if(inv_class.getCurrSelected() >= 5 && player.getItem(inv_class.getCurrSelected() - 5) > 0)
							{
								inv_class.setCurrSelected(inv_class.getCurrSelected() - 5);
							}
						} else if (player.getNavigatingInvMenu()){

							if(inv_class.getCurrSelMenu() > 0)
							{
								inv_class.setCurrSelMenu(inv_class.getCurrSelMenu() - 1);
							}

						} else { //NAVIGATING PAUSE MENU
							if(player.getCurrMenuSelected() > 0)
							{
								player.setCurrMenuSelected(player.getCurrMenuSelected() - 1);
							}
						}
						break;

					case sf::Keyboard::Down:
						if(player.getNavigatingInv() && !player.getNavigatingInvMenu())
						{
							if(inv_class.getCurrSelected() < MAX_INVENTORY_ITEMS - 5 && player.getItem(inv_class.getCurrSelected() + 5) != 0)
							{
								inv_class.setCurrSelected(inv_class.getCurrSelected() + 5);
							}

						} else if (player.getNavigatingInvMenu()){

							if(inv_class.getCurrSelMenu() < 2)
							{
								inv_class.setCurrSelMenu(inv_class.getCurrSelMenu() + 1);
							}

						} else { //NAVIGATING PAUSE MENU
							if(player.getCurrMenuSelected() < 2)
							{
								player.setCurrMenuSelected(player.getCurrMenuSelected() + 1);
							}
						}
						break;
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			switch(event.key.code)
			{
				if(gameMode == GAME_MODE_NORMAL)
				{
					case sf::Keyboard::Left:
						player.setMoving(false);
						break;
					case sf::Keyboard::Right:
						player.setMoving(false);
						break;
					case sf::Keyboard::Up:
						player.setMoving(false);
						break;
					case sf::Keyboard::Down:
						player.setMoving(false);
						break;
					case sf::Keyboard::X:
						if(player.isRunning())
						{
							player.setRunning(false);
							player.setRunAvailable(false);
						}
						break;
				}
			}
		}
    }

	//MORE RESPONSIVE MOVEMENT
	if(gameMode == GAME_MODE_NORMAL)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if(!textBox.isActive())
			{
				if(!checkCollisionNPC(0) && !checkCollisionBlock(0))
				{
					player.move(0);
					player.setMoving(true);
				}
				else
					player.setHeading(0);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if(!textBox.isActive())
			{
				if(!checkCollisionNPC(1) && !checkCollisionBlock(1))
				{
					player.move(1);
					player.setMoving(true);
				}
				else
					player.setHeading(1);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if(!textBox.isActive())
			{
				if(!checkCollisionNPC(2) && !checkCollisionBlock(2))
				{
					player.move(2);
					player.setMoving(true);
				}
				else
					player.setHeading(2);
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if(!textBox.isActive())
			{
				if(!checkCollisionNPC(3) && !checkCollisionBlock(3))
				{
					player.move(3);
					player.setMoving(true);
				}
				else
					player.setHeading(3);
			}
		}
	}

    render(auxFnt);

	float currentTime = clock.restart().asSeconds();
    float fps = 1.f / (currentTime - lastTime);
    lastTime = currentTime;

	if(gameMode == GAME_MODE_NORMAL)
	{
		player.update();

		for(int i = 0; i < MAX_NPCS; i++)
		{
			//ONLY UPDATE IF THE NPC IS IN THE USER'S VIEWPORT AND IF IT IS ALIVE
			if(isInViewPort(i) && npcList[i].isAlive())
			{
				if(npcList[i].isHostile() && !checkCollisionPlayer(i, getNPCPath(i)))
				{
					npcList[i].move(getNPCPath(i));
					npcList[i].setMoving(true);
				}
				else
				{
					//ATTACK THE USER
					if(npcList[i].isAlive() && npcList[i].isHostile() && !npcList[i].isAttacking())
					{
						player.setAttacked(npcList[i].getDamage());
						npcList[i].setAttacking(true);
					}

					npcList[i].setMoving(false);
				}
				npcList[i].update();
			}
		}

		for(int i = 0; i < MAX_ARROWS; i++)
		{
			if(arrowArr[i].getShotBy() != 0 && !checkCollisionArrowNPC(i))
			{
				arrowArr[i].update();
			}
			else
			{
				if(checkCollisionArrowNPC(i) && npcList[getCollisionArrowNPC(i)].isHostile())
				{
					npcList[getCollisionArrowNPC(i)].setAttacked(arrowArr[i].getDir(), arrowArr[i].getDamage(), arrowArr[i].getKnockBack());
					arrowArr[i].setShotBy(0); //kills the arrow
					arrowArr[i].setPosition(0, 0); //kills the arrow
				}
				else
				{
					arrowArr[i].update();
				}
			}
		}

		view.setCenter(sf::Vector2f(player.getPosX() - player.getWidth() / 2, player.getPosY() - player.getHeight() / 2));
	
	} else if (gameMode == GAME_MODE_PAUSE) {
		
	}

	if(player.isDead())
	{
		playerDie();
	}
	window.setTitle("FPS: " + std::to_string(fps) + " posX: " + std::to_string(player.getPosX() / TILE_SIZE) + " posY: " + std::to_string(player.getPosY() / TILE_SIZE));
}

int main()
{
	sf::Clock clock;
	sf::Font auxFnt;

	auxFnt.loadFromFile("resources/fonts/segoeui.ttf");
	clock.restart();

	view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	view.setCenter(sf::Vector2f(player.getPosX() - player.getWidth() / 2, player.getPosY() - player.getHeight() / 2));
	view.zoom(VIEW_ZOOM);

	window.setFramerateLimit(FPS_LIMIT);

	world.load();
	loadNPCs();
	loadPlayerData();
	loadItems();

	gameMode = GAME_MODE_NORMAL;

	while (window.isOpen())
    {
		update(clock, auxFnt);
	}
    return 0;
}