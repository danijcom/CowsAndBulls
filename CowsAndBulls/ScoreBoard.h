#pragma once
#include "ScoreRow.h"

//Класс табло
class ScoreBoard {
private:
	//Содержит в себе строки
	std::vector<ScoreRow*> rows;

public:
	//Конструктор
	ScoreBoard() {}

	//Оператор +, будем делать scoreBoard + scoreRow
	void operator+(ScoreRow&);

	//Отрисовка табло
	void draw();
};
