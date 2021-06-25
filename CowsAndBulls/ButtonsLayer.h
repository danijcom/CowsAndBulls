#pragma once
#include "Keyboard.h"

//Класс "слой кнопок" - содержит в себе клавиатуру и 2 служебные кнопки
class ButtonsLayer : public KeyBoard {
private:
	//Кнопка выхода и кнопка информации
	MySprite* buttonExit;
	MySprite* buttonAbout;

public:
	//Конструктор
	ButtonsLayer(sf::RenderWindow*, sf::Texture&, sf::Font&, sf::Texture&, sf::Texture&);

	//Обработка нажатия на кнопки
	Buttons::BUTTON_TYPES processClick(sf::Vector2i, Placeholders*);
	//Обработка hover'а кнопки мышкой
	void processHover(sf::Vector2i);

	void setKeyboardActive(bool);
	//Рисуем обе кнопки
	void draw();
};