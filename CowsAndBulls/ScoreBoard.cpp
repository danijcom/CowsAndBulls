#include "ScoreBoard.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Оператор +, будем делать scoreBoard + scoreRow
void ScoreBoard::operator+(ScoreRow& row) {
	//Делаем копию строки
	ScoreRow* copyRow = new ScoreRow(row);
	//Размещаем строку за экраном, куда нужно
	sf::FloatRect spriteBounds = copyRow->getBounds();
	copyRow->setPosition(Globals::__W_WIDTH__ / 2, -spriteBounds.height + 5);
	//Просчитываем новую позицию для строки с учетом остальных строк
	int amount = rows.size();
	float posX = (amount % 2 == 0) ? (Globals::__W_WIDTH__ / 2 - 40 * Globals::__W_SCALE__ - spriteBounds.width / 2) : (Globals::__W_WIDTH__ / 2 + 40 * Globals::__W_SCALE__ + spriteBounds.width / 2);
	sf::Vector2f lastPos = { posX , (float)(260 * Globals::__W_SCALE__ + ((int)(amount / 2) * 10 * Globals::__W_SCALE__) + spriteBounds.height * (int)(amount / 2)) };
	//Задаем строке смещение на нужную позицию
	copyRow->setTransit(lastPos, 4 + (amount / 2 + 0.5));
	//Сохраняем ее в массив
	rows.push_back(copyRow);
}

//Отрисовка табло
void ScoreBoard::draw() {
	for (ScoreRow* row : rows)
		row->draw();
}