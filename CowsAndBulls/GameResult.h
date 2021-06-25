#pragma once
#include "MySprite.h"
#include "Transitable.h"

//Класс для табло об окончании игры
class GameResult : public MySprite, public Transitable {
private:
	//Шрифт
	sf::Font font;
	//Цвет букв
	sf::Color color;
	//Время в игре
	std::string time;
	//Кол-во попыток
	std::string steps;
	//Секретное число
	std::string secret;
	//Обьекты текста для трех вышеперечисленных строк
	sf::Text textTime;
	sf::Text textSteps;
	sf::Text textSecret;

public:
	//Конструктор
	GameResult(sf::RenderWindow*, sf::Texture&, sf::Font&, sf::Color, int, std::string, std::string);

	//Создание одного текста, принимает текст, строку, и смещение по оY
	void textRender(sf::Text&, std::string, float);
	//Создание всех трех текстов (веремя, ходы, секретное число)
	void makeTexts();
	//Смещаем, рендерим текста
	void transit();
	//Отрисовка строки - спрайт, быки, коровы
	void draw();
	//Задаем перемещение сообщению
	bool setTransit(sf::Vector2f);
};
