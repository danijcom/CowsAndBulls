#include "Placeholders.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
Placeholders::Placeholders(sf::RenderWindow* window, sf::Texture& texture) {
	this->isHidden = false;
	for (int i = 0; i < 4; i++) {
		sprites[i] = new MySprite(window, texture);
		sprites[i]->setPosition((462 + 183 * i) * Globals::__W_SCALE__, 1807 * Globals::__W_SCALE__);
	}
}

//Будем делать placeholder + button, чтобы кнопка переместилась в контейнетр
bool Placeholders::operator+(Button* button) {
	int arr_size = buttons.size();
	//Кнопок не может быть больше чем 4
	if (arr_size < 4) {
		buttons.push_back(button);
		button->setActive(false);
		button->setTransit(sprites[arr_size]->getPosition());
		return true;
	}
	return false;
}

//Вернуть последнюю кнопку на место
bool Placeholders::remove() {
	int arr_size = buttons.size();
	if (arr_size > 0) {
		Button* button = buttons.back();
		buttons.pop_back();
		button->setTransit(button->getOriginPos());
		button->setActive(true);
		return true;
	}
	return false;
}
//Вернуть все кнопки на место
void Placeholders::clear() {
	for (Button* button : buttons) {
		button->setTransit(button->getOriginPos());
		button->setActive(true);
		buttons.pop_back();
	}
}

//Проверка на заполненность
bool Placeholders::isFull() {
	if (buttons.size() == 4) {
		for (Button* button : buttons) {
			if (button->isInTransit()) {
				//std::cout << "Button [" << button->getLable() << "] still in transit" << std::endl;
				return false;
			}
		}
		return true;
	}
	return false;
}
//Получить комбинацию из 4х цифр
std::string Placeholders::getCombination() {
	if (!isFull())
		throw std::runtime_error("Placeholders::getCombination() error - There is NO combination");
	else {
		std::string tmp;
		for (Button* button : buttons) {
			tmp += button->getLable();
		}
		return tmp;
	}
}
//Скрыть/вернуть контекйнеры
void Placeholders::setHidden(bool isHidden) {
	this->isHidden = isHidden;
}

//Отрисовать контейнеры
void Placeholders::draw() {
	if (!isHidden) {
		for (MySprite* placeholder : sprites)
			placeholder->draw();
	}
}