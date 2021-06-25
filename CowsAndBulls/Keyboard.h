#pragma once
#include "Button.h"
#include "Placeholders.h"

//Класс клавиатура
class KeyBoard {
private:
	//Кнопки в клавиатуре
	std::vector<Button*> buttons;
	//Основной цвет, накладываемый на кнопки
	sf::Color color;
	//Цвет наложения при наведении на кнопку
	sf::Color colorHover;
	//Скрыта ли
	bool isHidden;

public:
	//Конструктор
	KeyBoard(sf::RenderWindow*, sf::Texture&, sf::Font&, sf::Color mainColor = sf::Color::White, sf::Color = sf::Color(248, 150, 48));

	//Обработка клика на кнопку
	Buttons::BUTTON_TYPES processClick(sf::Vector2i, Placeholders*);
	//Обработка клика клавиши
	Buttons::BUTTON_TYPES processKBClick(std::string, Placeholders*);
	//Обработка hover`а кнопки мышкой (накладываем на кнопку цвет наложения)
	void processHover(sf::Vector2i);
	//Активировать/деактивировать кнопки
	void setActive(bool);
	//Скрыть/вернуть клавиатуру
	void setHidden(bool);

	//Отрисовка всех кнопок
	void draw();
};
