#include "Transitable.h"


//Конструктор
Transitable::Transitable(float speed) {
	this->inTransit = false;
	this->transitable = true;
	this->speed = speed;
}
//Конструктор копии
Transitable::Transitable(Transitable& obj) {
	this->speed = obj.speed;
	this->transitable = obj.transitable;
	this->inTransit = obj.inTransit;
	this->transitTo = obj.transitTo;
}

//Один шаг перемещения, возвращает false, если перемещение окончено
bool Transitable::transit(sf::Sprite& sprite) {
	//Если обьект в процессе перемещения
	if (inTransit) {
		//Получим его позицию
		sf::Vector2i curPos = sf::Vector2i(sprite.getPosition());
		//Проверим, не в нужной ли он позиции
		if (curPos == transitTo) {
			inTransit = false;
		}
		//Если нет, то
		else {
			//Будем сравнивать все координаты, и двигать обтект
			if (curPos.x < transitTo.x) {
				if (transitTo.x - curPos.x > speed + speed / 4)
					sprite.move(speed, 0);
				//Замедлим движение, когда уже почти в нужной точке
				else
					sprite.move(0.5, 0);
			}
			else if (curPos.x > transitTo.x) {
				if (curPos.x - transitTo.x > speed + speed / 4)
					sprite.move(-speed, 0);
				else
					sprite.move(-0.5, 0);
			}

			if (curPos.y < transitTo.y) {
				if (transitTo.y - curPos.y > speed + speed / 4)
					sprite.move(0, speed);
				else
					sprite.move(0, 0.5);
			}
			else if (curPos.y > transitTo.y) {
				if (curPos.y - transitTo.y > speed + speed / 4)
					sprite.move(0, -speed);
				else
					sprite.move(0, -0.5);
			}
		}
	}
	return inTransit;
}
//Находится ли обьект в движении
bool Transitable::isInTransit() {
	return inTransit;
}

//Начать перемещение к позиции position
bool Transitable::setTransit(sf::Sprite& sprite, sf::Vector2f position, float speed) {
	//Перемещение не начнется, если обьект не перемещаем
	if (!transitable)
		return false;
	//Получим текущую позицию
	sf::Vector2i curPos = sf::Vector2i(sprite.getPosition());
	//Если мы не в нужной позиции
	if (sf::Vector2i(position) != curPos) {
		//Запустим перемещение
		this->speed = (speed != -5) ? speed : this->speed;
		transitTo = sf::Vector2i(position);
		inTransit = true;
		return true;
	}
	return false;
}
//Установка перемещаемости обьекта
void Transitable::setTransitable(bool transitable) {
	this->transitable = transitable;
}
