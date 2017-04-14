#include "textBox.h"

TextBox::TextBox(void)
{
	active = false;
	currRenderText = 0;
	textToRender = "";
	renderFont.loadFromFile("resources/fonts/segoeui.ttf");

	shape.setFillColor(sf::Color::Green);

	renderText.setFont(renderFont);
	renderText.setString(textToRender);
	renderText.setCharacterSize(20);
	renderText.setColor(sf::Color::Black);
}

TextBox::~TextBox(void)
{
}

void TextBox::setActive(bool val)
{
	active = val;
}

void TextBox::setCurrRenderText(int val)
{
	currRenderText = val;
}

void TextBox::setTextToRender(std::string txt)
{
	textToRender = txt;
	renderText.setString(textToRender);
}

void TextBox::setPosAndSize(int x, int y, int sizeW, int sizeH)
{
	shape.setPosition(x, y);
	shape.setSize(sf::Vector2f(sizeW, sizeH));

	renderText.setPosition(x, y);
}

bool TextBox::isActive()
{
	return active;
}

int TextBox::getCurrRenderText()
{
	return currRenderText;
}

sf::RectangleShape TextBox::getShape()
{
	return shape;
}

sf::Text TextBox::getText()
{
	return renderText;
}