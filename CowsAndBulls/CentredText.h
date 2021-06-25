#pragma once
#include <SFML/Graphics.hpp>

//Вспомогательный класс для обьектов,
// содержащих центрированный текст
class CenteredText {
protected:
	//Сам текст, строка
	std::string lable;
	//Шрифт
	sf::Font font;
	//Цвет текста
	sf::Color color;
	//Обьект текста
	sf::Text text;
	//Размер шрифта
	int fontSize;

public:
	//Конструктор
	CenteredText(sf::Color, sf::Font, std::string, int = 55);

	//Создаем текст, помещаем его в центр обьекта
	void makeText(sf::Sprite&);

	//Возвращает надпись
	std::string getLable();
	//Устанавливает надпись
	void setLable(std::string);
};