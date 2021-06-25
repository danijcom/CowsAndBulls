#pragma once
#include "MySprite.h"
#include "Transitable.h"
#include "CentredText.h"

//Класс для всплывающего сообщения (содержит в себе спрайт, перемещаемо, и содержит центрированный текст)
class PushMessage : public MySprite, public Transitable, public CenteredText {
private:
	//Основная позиция сообщения (обычно это за экраном)
	sf::Vector2f originPos;
	//Время, в которое нужно будет вернуть сообщение назад
	std::time_t transitBack;

public:
	//Конструктор
	PushMessage(sf::RenderWindow*, sf::Texture&, sf::Color, sf::Font, std::string, int = 60, int = 20);

	//Вернуть сообщение на место
	void goBack();
	//Шаг смещения сообщения
	void transit();
	//По клику на сообщение вернуть его назад
	void processClick(sf::Vector2i);
	//Проверяем, не в пути ли сообщение
	bool isInTransit();
	//Отрисовка сообщения
	void draw();

	//Задаем перемещение сообщению
	bool setTransit(sf::Vector2f, int = 0);
	//Задаем текст сообщения
	void setText(std::string);
	//Задаем позицию сообщению
	void setPosition(float, float, bool = false);
	//Возвращает основную позицию
	sf::Vector2f getOriginPos();
};
