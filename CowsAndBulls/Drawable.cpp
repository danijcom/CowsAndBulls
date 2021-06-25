#include "Drawable.h"

Drawable::Drawable(sf::RenderWindow* window) {
	this->window = window;
};
Drawable::Drawable(Drawable& obj) {
	this->window = obj.window;
}