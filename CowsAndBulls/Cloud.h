#pragma once
#include "MySprite.h"

//Класс для облаков (на фоне)
class Cloud : public MySprite {
private:
	//Скорость по оси Х
	float xSpeed;

public:
	//Конструктор
	Cloud(sf::RenderWindow*, sf::Texture&, bool = true, float = 1);

	//Проверяем, не вышло ли облако целиком за границу окна
	bool isVisible();
	//Один "шаг" графики - перемещение облака, отрисовка, и инвертация скорости, если облако вылетело за окно
	void step();

	//Установка скорости
	void setSpeed(float);
};