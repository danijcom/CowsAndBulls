#include "MySprite.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

MySprite::MySprite(sf::RenderWindow* window, sf::Texture& texture, bool centerOrigin) : Drawable(window) {
	this->texture = texture;
	texture.setSmooth(true);
	if (centerOrigin)
		this->centerOrigin();
	sprite.setTexture(texture);
	sprite.setScale(Globals::__W_SCALE__, Globals::__W_SCALE__);
	this->size = texture.getSize();
}
//Конструктор копии
MySprite::MySprite(MySprite& obj) : Drawable(obj) {
	this->texture = obj.texture;
	this->sprite = obj.sprite;
	this->texture = obj.texture;
	this->sprite.setTexture(this->texture);
	this->size = obj.size;
}

//Установить "точку опоры" спрайта в его середине
void MySprite::centerOrigin() {
	sf::Vector2u t_size = texture.getSize();
	sprite.setOrigin(t_size.x / 2, t_size.y / 2);
}

//Проверка на то, находится ли переданная точка в пределах спрайта
bool MySprite::contains(sf::Vector2i mousePosition) {
	return sprite.getGlobalBounds().contains(sf::Vector2f(mousePosition));
}
//Нарисовать спрайт
void MySprite::draw() {
	window->draw(sprite);
}


//Сдвинуть спрайт на offsetX и offsetY пикселей
void MySprite::move(float offsetX, float offsetY) {
	sprite.move(offsetX, offsetY);
}
//Повернуть спрайт на angle градусов вокруг "точки опоры"
void MySprite::rotate(float angle) {
	sprite.rotate(angle);
}

//Установка позиции спрайта
void MySprite::setPosition(float posX, float posY) {
	sprite.setPosition(posX, posY);
}
//Установка цвета спрайта
void MySprite::setColor(sf::Color color) {
	sprite.setColor(color);
}
//Вернуть размер спрайта
sf::Vector2f MySprite::getSize() {
	return sf::Vector2f(size);
}
//Вернуть инф-цию о прямоугольнике - контейнере спрайта
sf::FloatRect MySprite::getBounds() {
	return sprite.getGlobalBounds();
}
//Вернуть позицию спрайта
sf::Vector2f MySprite::getPosition() {
	return sprite.getPosition();
}