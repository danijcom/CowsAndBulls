#pragma once
#include <SFML/Graphics.hpp>

//Вспомогательный класс для обьектов, 
// которые смогут плавно перемещаться в заданную точку
class Transitable {
private:
	//Скорость перемещения
	float speed;
	//Переменная, указывающая, может ли обьект перемещаться
	bool transitable;
	//Переменная, указывающая, находится ли обьект в процессе перемещения
	bool inTransit;
	//Позиция, куда нужно переместить обьект
	sf::Vector2i transitTo;

public:
	//Конструктор
	Transitable(float = 20);
	//Конструктор копии
	Transitable(Transitable&);

	//Один шаг перемещения, возвращает false, если перемещение окончено
	bool transit(sf::Sprite&);
	//Находится ли обьект в движении
	bool isInTransit();

	//Начать перемещение к позиции position
	bool setTransit(sf::Sprite&, sf::Vector2f, float = -5);
	//Установка перемещаемости обьекта
	void setTransitable(bool);
};