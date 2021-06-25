#include "ButtonsLayer.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
ButtonsLayer::ButtonsLayer(sf::RenderWindow* window, sf::Texture& textureNumber, sf::Font& fontNumber, sf::Texture& textureExit, sf::Texture& textureAbout) : KeyBoard(window, textureNumber, fontNumber) {
	buttonExit = new MySprite(window, textureExit);
	buttonExit->setPosition((-100 * Globals::__W_SCALE__) + Globals::__W_WIDTH__, (100 * Globals::__W_SCALE__));

	buttonAbout = new MySprite(window, textureAbout);
	buttonAbout->setPosition(100 * Globals::__W_SCALE__, (100 * Globals::__W_SCALE__));

}

//Обработка нажатия на кнопки
Buttons::BUTTON_TYPES ButtonsLayer::processClick(sf::Vector2i mousePosition, Placeholders* placeholders) {
	Buttons::BUTTON_TYPES pressed = KeyBoard::processClick(mousePosition, placeholders);
	if (pressed == Buttons::BUTTON_TYPES::NONE) {
		if (buttonExit->contains(mousePosition)) {
			return Buttons::EXIT;
		}
		else if (buttonAbout->contains(mousePosition)) {
			return Buttons::ABOUT;
		}
	}
	return pressed;
}
//Обработка hover'а кнопки мышкой
void ButtonsLayer::processHover(sf::Vector2i mousePosition) {
	KeyBoard::processHover(mousePosition);
	if (buttonExit->contains(mousePosition)) {
		buttonExit->setColor(sf::Color(253, 160, 160));
	}
	else {
		buttonExit->setColor(sf::Color::White);
	}
	if (buttonAbout->contains(mousePosition)) {
		buttonAbout->setColor(sf::Color(160, 210, 253));
	}
	else {
		buttonAbout->setColor(sf::Color::White);
	}
}

void ButtonsLayer::setKeyboardActive(bool isActive) {
	KeyBoard::setActive(isActive);
}

//Рисуем обе кнопки
void ButtonsLayer::draw() {
	KeyBoard::draw();
	buttonExit->draw();
	buttonAbout->draw();
}