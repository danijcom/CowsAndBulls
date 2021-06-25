#pragma once
#include "Transitable.h"
#include "CentredText.h"
#include "MySprite.h"


//Идентификаторы кнопок
namespace Buttons {
	enum BUTTON_TYPES {
		NUMBER, //Кнопка число
		DELETE, //Кнопка удалить
		CLEAR,  //Кнопка очистить
		ABOUT,  //Кнопка "?"
		EXIT,   //Кнопка выход
		NONE    //Кнопка не нажата
	};
}

//Класс для кнопок (содержат в себе спрайт, перемещаемы, содержат центрированный текст)
class Button : public MySprite, public Transitable, public CenteredText {
private:
	//Основная позиция кнопки (если понадобится туда вернуть ее)
	sf::Vector2f originPos;
	//Тип кнопки
	Buttons::BUTTON_TYPES type;
	//Цвета кнопки
	sf::Color mainColor;
	sf::Color hoverColor;
	//Активна ли кнопка
	bool active;

public:
	//Конструктор
	Button(sf::RenderWindow*, sf::Texture&, sf::Color, sf::Font&, std::string, Buttons::BUTTON_TYPES, sf::Color, sf::Color);

	//Шаг перемещения кнопки
	void transit();

	//Отрисовка кнопки (смещение, отрисовка кнопки и текста)
	void draw();
	//(де)активировать кнопку
	void setActive(bool);
	//Начать перемещение кнопки в позицию position
	bool setTransit(sf::Vector2f);
	//Задать текст на кнопке
	void setText(std::string);
	//Установить позицию кнопки
	void setPosition(float, float, bool = false);
	//Задать тип кнопки
	void setType(Buttons::BUTTON_TYPES);
	//Активна ли кнопка
	bool isActive();
	//Получить тип кнопки
	Buttons::BUTTON_TYPES getType();
	//Получить основную позицию кнопки
	sf::Vector2f getOriginPos();
};