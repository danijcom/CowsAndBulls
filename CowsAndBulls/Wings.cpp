#include "Wings.h"

Wings::Wings(sf::RenderWindow* window, sf::Texture& texture, bool centerOrigin, int angle) : MySprite(window, texture, centerOrigin) {
	this->angle = angle;
};

//Один шаг графики - смещение на угол и отрисовка
void Wings::step() {
	this->rotate(angle);
	draw();
}

//Установка скорости
void Wings::setSpeed(float speed) {
	this->angle = speed;
}