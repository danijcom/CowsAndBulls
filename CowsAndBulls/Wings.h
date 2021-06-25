#pragma once
#include "MySprite.h"

//Класс для лопостей мельницы
class Wings : public MySprite {
private:
	//Угол поворота за шаг графики
	int angle;
public:
	//Конструктор
	Wings(sf::RenderWindow*, sf::Texture&, bool = true, int = 1);

	//Один шаг графики - смещение на угол и отрисовка
	void step();

	//Установка скорости
	void setSpeed(float);
};