#pragma once
#include "MySprite.h"
#include "Transitable.h"

//Класс строка на табло, состоит из перемещаемого спрайта
class ScoreRow : public MySprite, public Transitable {
private:
	//Строка с цифрами в строке (например "1234")
	std::string numbers;
	//Шрифт букв на табло
	sf::Font font;
	//Обьект текста для числа
	sf::Text _number;
	//Для быков
	sf::Text _bulls;
	//И коров
	sf::Text _cows;
	//Цвет текста
	sf::Color textColor;
	//Сами быки и коровы
	int bulls;
	int cows;

public:
	//Конструктор
	ScoreRow(sf::RenderWindow*, sf::Texture&, sf::Font&, sf::Color, std::string, int, int, float = 20);
	//Конструктор копии
	ScoreRow(ScoreRow&);

	//Создание одного текста, принимает текст, строку, и смещение по оХ
	void textRender(sf::Text&, std::string, float);
	//Создание всех трех текстов (число, быки, коровы)
	void makeTexts();
	//Отрисовка строки - спрайт, быки, коровы
	void draw();

	//Перемещение строки
	bool setTransit(sf::Vector2f, float);
	//Задание позиции строке
	void setPosition(float, float);
	//Шаг перемещения строки
	void transit();
};
