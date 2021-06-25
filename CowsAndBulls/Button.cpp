#include "Button.h"
#include "Globals.h"


//Конструктор
Button::Button(sf::RenderWindow* window, sf::Texture& texure, sf::Color color, sf::Font& font, std::string label, Buttons::BUTTON_TYPES type, sf::Color mainColor, sf::Color hoverColor) : MySprite(window, texure, true), CenteredText(color, font, label, 82 * Globals::__W_SCALE__) {
	this->type = type;
	this->active = true;
	this->mainColor = mainColor;
	this->hoverColor = hoverColor;
	this->CenteredText::makeText(sprite);
};

//Шаг перемещения кнопки
void Button::transit() {
	Transitable::transit(sprite);
	CenteredText::makeText(sprite);
}

//Отрисовка кнопки (смещение, отрисовка кнопки и текста)
void Button::draw() {
	transit();
	MySprite::draw();
	window->draw(text);
}
//(де)активировать кнопку
void Button::setActive(bool isActive) {
	if (isActive)
		sprite.setColor(mainColor);
	this->active = isActive;
}
//Начать перемещение кнопки в позицию position
bool Button::setTransit(sf::Vector2f position) {
	return Transitable::setTransit(sprite, position);
}
//Задать текст на кнопке
void Button::setText(std::string label) {
	CenteredText::setLable(label);
	CenteredText::makeText(sprite);
}
//Установить позицию кнопки
void Button::setPosition(float posX, float posY, bool origin) {
	//Является ли позиция основной
	if (origin)
		originPos = { posX, posY };
	MySprite::setPosition(posX, posY);
	CenteredText::makeText(sprite);
}
//Задать тип кнопки
void Button::setType(Buttons::BUTTON_TYPES type) {
	this->type = type;
}
//Активна ли кнопка
bool Button::isActive() {
	return active;
}
//Получить тип кнопки
Buttons::BUTTON_TYPES Button::getType() {
	return type;
}
//Получить основную позицию кнопки
sf::Vector2f Button::getOriginPos() {
	return originPos;
}