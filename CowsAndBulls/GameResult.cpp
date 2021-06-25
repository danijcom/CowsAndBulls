#include "GameResult.h"

#ifndef ATTEMPTS
#define ATTEMPTS 30
#endif // !ATTEMPTS


namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
GameResult::GameResult(sf::RenderWindow* window, sf::Texture& texture, sf::Font& font, sf::Color color, int secondsInGame, std::string steps, std::string secret) : MySprite(window, texture), Transitable(7) {
	this->time = time;
	this->secret = secret;
	this->steps = steps + "/" + std::to_string(ATTEMPTS);
	this->font = font;
	this->color = color;

	//Тут переводим время из секунд в строку формата hh:mm:ss
	int seconds, hours, minutes;
	minutes = secondsInGame / 60;
	seconds = secondsInGame % 60;
	hours = minutes / 60;
	minutes = minutes % 60;

	this->time += (hours >= 10) ? std::to_string(hours) : ("0" + std::to_string(hours));
	this->time += ":";
	this->time += (minutes >= 10) ? std::to_string(minutes) : ("0" + std::to_string(minutes));
	this->time += ":";
	this->time += (seconds >= 10) ? std::to_string(seconds) : ("0" + std::to_string(seconds));

	//Окошко будет выезжать снизу
	setPosition(Globals::__W_WIDTH__ / 2, Globals::__W_HEIGHT__ + getSize().y / 2);
	setTransit(sf::Vector2f(Globals::__W_WIDTH__ / 2, Globals::__W_HEIGHT__ - (getBounds().height / 2)));
}

//Создание одного текста, принимает текст, строку, и смещение по оY
void GameResult::textRender(sf::Text& text, std::string str, float y_offset) {
	text.setFont(font);
	text.setCharacterSize(130 * Globals::__W_SCALE__);
	text.setString(str);

	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(0, textRect.top + textRect.height / 2.0f);

	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	text.setPosition(sf::Vector2f(spriteBounds.left + (780 * Globals::__W_SCALE__), spriteBounds.top + (y_offset * Globals::__W_SCALE__)));
	text.setFillColor(color);
}
//Создание всех трех текстов (веремя, ходы, секретное число)
void GameResult::makeTexts() {
	textRender(textTime, time, 565);
	textRender(textSteps, steps, 807);
	textRender(textSecret, secret, 1072);
}
//Смещаем, рендерим текста
void GameResult::transit() {
	Transitable::transit(sprite);
	makeTexts();
}
//Отрисовка строки - спрайт, быки, коровы
void GameResult::draw() {
	transit();
	MySprite::draw();
	window->draw(textTime);
	window->draw(textSteps);
	window->draw(textSecret);
}
//Задаем перемещение сообщению
bool GameResult::setTransit(sf::Vector2f position) {
	return Transitable::setTransit(sprite, position);
}