#include "PushMessage.h"

//Конструктор
PushMessage::PushMessage(sf::RenderWindow* window, sf::Texture& texturePush, sf::Color color, sf::Font font, std::string label, int fontSize, int speed) : Transitable(speed), MySprite(window, texturePush, true), CenteredText(color, font, label, fontSize) {
	this->CenteredText::makeText(sprite);
	this->transitBack = 0;
};

//Вернуть сообщение на место
void PushMessage::goBack() {
	Transitable::setTransit(sprite, originPos);
}
//Шаг смещения сообщения
void PushMessage::transit() {
	//Если пора вернуть сообщение на место - возвращаем
	if (transitBack != 0 && std::time(0) >= transitBack)
		goBack();
	Transitable::transit(sprite);
	CenteredText::makeText(sprite);
}
//По клику на сообщение вернуть его назад
void PushMessage::processClick(sf::Vector2i mousePosition) {
	if (MySprite::contains(mousePosition)) {
		goBack();
	}
}
//Проверяем, не в пути ли сообщение
bool PushMessage::isInTransit() {
	if (transitBack)
		return true;
	return Transitable::isInTransit();
}
//Отрисовка сообщения
void PushMessage::draw() {
	transit();
	MySprite::draw();
	window->draw(text);
}

//Задаем перемещение сообщению
bool PushMessage::setTransit(sf::Vector2f position, int transitBack) {
	this->transitBack = std::time(0) + transitBack;
	return Transitable::setTransit(sprite, position);
}
//Задаем текст сообщения
void PushMessage::setText(std::string label) {
	CenteredText::setLable(label);
	CenteredText::makeText(sprite);
}
//Задаем позицию сообщению
void PushMessage::setPosition(float posX, float posY, bool origin) {
	if (origin)
		originPos = { posX, posY };
	MySprite::setPosition(posX, posY);
	CenteredText::makeText(sprite);
}
//Возвращает основную позицию
sf::Vector2f PushMessage::getOriginPos() {
	return originPos;
}