#include "ScoreRow.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
ScoreRow::ScoreRow(sf::RenderWindow* window, sf::Texture& bgTexture, sf::Font& font, sf::Color textColor, std::string numbers, int bulls, int cows, float speed) : MySprite(window, bgTexture), Transitable(speed) {
	this->numbers = numbers;
	this->cows = cows;
	this->bulls = bulls;
	this->font = font;
	this->textColor = textColor;
	makeTexts();
}
//Конструктор копии
ScoreRow::ScoreRow(ScoreRow& obj) : MySprite(obj), Transitable(obj) {
	this->numbers = obj.numbers;
	this->font = obj.font;
	this->_number = obj._number;
	this->_bulls = obj._bulls;
	this->_cows = obj._cows;
	this->textColor = obj.textColor;
	this->bulls = obj.bulls;
	this->cows = obj.cows;
}

//Создание одного текста, принимает текст, строку, и смещение по оХ
void ScoreRow::textRender(sf::Text& text, std::string str, float x_offset) {
	text.setFont(font);
	text.setCharacterSize(75 * Globals::__W_SCALE__);
	text.setString(str);

	sf::FloatRect textRect = _number.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	text.setPosition(sf::Vector2f(spriteBounds.left + (x_offset * Globals::__W_SCALE__), spriteBounds.top + spriteBounds.height / 2.0f));
	text.setFillColor(textColor);
}
//Создание всех трех текстов (число, быки, коровы)
void ScoreRow::makeTexts() {
	textRender(_number, numbers, 115);
	textRender(_bulls, "x" + std::to_string(bulls), 380);
	textRender(_cows, "x" + std::to_string(cows), 565);
}
//Отрисовка строки - спрайт, быки, коровы
void ScoreRow::draw() {
	transit();
	MySprite::draw();
	window->draw(_number);
	window->draw(_bulls);
	window->draw(_cows);
}

//Перемещение строки
bool ScoreRow::setTransit(sf::Vector2f position, float speed) {
	return Transitable::setTransit(sprite, position, speed);
}
//Задание позиции строке
void ScoreRow::setPosition(float posX, float posY) {
	MySprite::setPosition(posX, posY);
	makeTexts();
}
//Шаг перемещения строки
void ScoreRow::transit() {
	Transitable::transit(sprite);
	makeTexts();
}