#include "Keyboard.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
KeyBoard::KeyBoard(sf::RenderWindow* window, sf::Texture& textureNumber, sf::Font& fontNumber, sf::Color mainColor, sf::Color colorHover) {
	this->color = mainColor;
	this->colorHover = colorHover;
	this->isHidden = false;

	Button* button;
	int posN = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			button = new Button(window, textureNumber, color, fontNumber, std::to_string(posN++), Buttons::BUTTON_TYPES::NUMBER, mainColor, colorHover);
			button->setPosition((571 + 179 * j) * Globals::__W_SCALE__, (2179 + i * 178) * Globals::__W_SCALE__, true);
			buttons.push_back(button);
		}
	}
	buttons[10]->setText("0");

	buttons[9]->setText("x");
	buttons[9]->setType(Buttons::BUTTON_TYPES::CLEAR);
	buttons[11]->setText("<<");
	buttons[11]->setType(Buttons::BUTTON_TYPES::DELETE);
}

//Обработка клика на кнопку
Buttons::BUTTON_TYPES KeyBoard::processClick(sf::Vector2i mousePosition, Placeholders* placeholders) {
	for (Button* button : buttons) {
		if (button->isActive()) {
			//Если клик пришелся на область кнопки
			if (button->contains(mousePosition)) {
				//Если кнопка-цифра, то переместим ее в контейнер
				if (button->getType() == Buttons::BUTTON_TYPES::NUMBER) {
					*placeholders + button;
					return Buttons::BUTTON_TYPES::NUMBER;
				}
				//Если нажата кнопка удаления, то удалим одну цифру из контейнера
				else if (button->getType() == Buttons::BUTTON_TYPES::DELETE) {
					placeholders->remove();
					return Buttons::BUTTON_TYPES::DELETE;
				}
				//Если нажата кнопка очистить - удалим все цифры из контейнера
				else if (button->getType() == Buttons::BUTTON_TYPES::CLEAR) {
					placeholders->clear();
					return Buttons::BUTTON_TYPES::CLEAR;
				}
			}
		}
	}
	return Buttons::BUTTON_TYPES::NONE;
}
//Обработка клика клавиши
Buttons::BUTTON_TYPES KeyBoard::processKBClick(std::string lable, Placeholders* placeholders) {
	for (Button* button : buttons) {
		if (button->isActive() && button->getLable() == lable) {
			//Если кнопка-цифра, то переместим ее в контейнер
			if (button->getType() == Buttons::BUTTON_TYPES::NUMBER) {
				*placeholders + button;
				return Buttons::BUTTON_TYPES::NUMBER;
			}
			//Если нажата кнопка удаления, то удалим одну цифру из контейнера
			else if (button->getType() == Buttons::BUTTON_TYPES::DELETE) {
				placeholders->remove();
				return Buttons::BUTTON_TYPES::DELETE;
			}
		}
	}
	return Buttons::BUTTON_TYPES::NONE;
}
//Обработка hover`а кнопки мышкой (накладываем на кнопку цвет наложения)
void KeyBoard::processHover(sf::Vector2i mousePosition) {
	for (Button* button : buttons) {
		if (button->isActive()) {
			if (button->contains(mousePosition)) {
				button->setColor(colorHover);
			}
			else {
				button->setColor(color);
			}
		}
	}
}
//Активировать/деактивировать кнопки
void KeyBoard::setActive(bool isActive) {
	for (Button* button : buttons)
		button->setActive(isActive);
}
//Скрыть/вернуть клавиатуру
void KeyBoard::setHidden(bool isHidden) {
	this->isHidden = isHidden;
}

//Отрисовка всех кнопок
void KeyBoard::draw() {
	if (!isHidden) {
		for (Button* button : buttons)
			button->draw();
	}
}