#include "Cloud.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}


//Конструктор
Cloud::Cloud(sf::RenderWindow* window, sf::Texture& texture, bool centerOrigin, float xSpeed) : MySprite(window, texture, centerOrigin) {
	this->xSpeed = xSpeed;
}

//Проверяем, не вышло ли облако целиком за границу окна
bool Cloud::isVisible() {
	sf::Vector2f curPos = getPosition();
	sf::Vector2f curSize = getSize();

	if (xSpeed < 0 && curPos.x + (curSize.x / 2) < 0)
		return false;
	else if (xSpeed > 0 && curPos.x - (curSize.x / 2) > Globals::__W_WIDTH__)
		return false;
	else
		return true;
}
//Один "шаг" графики - перемещение облака, отрисовка, и инвертация скорости, если облако вылетело за окнo
void Cloud::step() {
	move(xSpeed, 0);
	draw();
	if (!isVisible())
		xSpeed *= -1;
}

//Установка скорости
void Cloud::setSpeed(float speed) {
	this->xSpeed = xSpeed;
}