#pragma once
#include "NPC.h"

class TextBox
{
public:
	TextBox(void);
	~TextBox(void);

	void setActive(bool val);
	void setCurrRenderText(int val);
	void setTextToRender(std::string txt);
	void setPosAndSize(int x, int y, int sizeW, int sizeH);

	bool isActive();
	int getCurrRenderText();
	sf::RectangleShape getShape();
	sf::Text getText();

private:
	bool active;
	sf::Font renderFont;
	sf::Text renderText;
	int currRenderText;
	std::string textToRender;
	sf::RectangleShape shape; //CAMBIAR X TEXTURA DESSPUES
};

