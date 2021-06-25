#pragma once
#include "Button.h"
#include "array"

//Класс контейнеров для кнопок (серые квадраты)
class Placeholders {
private:
	//Всего их 4 штуки (спрайта)
	std::array<MySprite*, 4> sprites;
	//Массив кнопок, находящихся в контейнерах
	std::vector<Button*> buttons;
	//Скрыт ли
	bool isHidden;

public:
	//Конструктор
	Placeholders(sf::RenderWindow* window, sf::Texture& texture);

	//Будем делать placeholder + button, чтобы кнопка переместилась в контейнетр
	bool operator+(Button* button);

	//Вернуть последнюю кнопку на место
	bool remove();
	//Вернуть все кнопки на место
	void clear();

	//Проверка на заполненность
	bool isFull();
	//Получить комбинацию из 4х цифр
	std::string getCombination();
	//Скрыть/вернуть контекйнеры
	void setHidden(bool isHidden);

	//Отрисовать контейнеры
	void draw();
};