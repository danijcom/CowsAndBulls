#pragma once
#include <SFML/Graphics.hpp>

//Самый базовый класс любого обьекта, который может быть нарисован
// нужен для хранения окна
class Drawable {
protected:
	sf::RenderWindow* window;

public:
	Drawable(sf::RenderWindow*);
	Drawable(Drawable&);
};