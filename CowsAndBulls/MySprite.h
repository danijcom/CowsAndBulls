#pragma once
#include "Drawable.h"

//Надстройка над sf::sprite для удобства
class MySprite : public Drawable {
private:
	//Текстура спрайта
	sf::Texture texture;
	//Размер спрайта
	sf::Vector2u size;

	//Установить "точку опоры" спрайта в его середине
	void centerOrigin();

protected:
	//Сам спрайт
	sf::Sprite sprite;

public:
	//Конструктор
	MySprite(sf::RenderWindow*, sf::Texture&, bool = true);
	//Конструктор копии
	MySprite(MySprite&);

	//Проверка на то, находится ли переданная точка в пределах спрайта
	bool contains(sf::Vector2i);
	//Нарисовать спрайт
	void draw();


	//Сдвинуть спрайт на offsetX и offsetY пикселей
	void move(float, float);
	//Повернуть спрайт на angle градусов вокруг "точки опоры"
	void rotate(float);

	//Установка позиции спрайта
	void setPosition(float, float);
	//Установка цвета спрайта
	void setColor(sf::Color);
	//Вернуть размер спрайта
	sf::Vector2f getSize();
	//Вернуть инф-цию о прямоугольнике - контейнере спрайта
	sf::FloatRect getBounds();
	//Вернуть позицию спрайта
	sf::Vector2f getPosition();
};