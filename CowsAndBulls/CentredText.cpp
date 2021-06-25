#include "CentredText.h"

//Конструктор
CenteredText::CenteredText(sf::Color color, sf::Font font, std::string label, int fontSize ) {
	this->lable = label;
	this->font = font;
	this->color = color;
	this->fontSize = fontSize;
}

//Создаем текст, помещаем его в центр обьекта
void CenteredText::makeText(sf::Sprite& sprite) {
	//Установим шрифт, размер текста, строку
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setString(lable);

	//Установим "точку опоры" текста в его центре
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	//Центрируем текст в спрайта
	sf::FloatRect spriteBounds = sprite.getGlobalBounds();
	text.setPosition(sf::Vector2f(spriteBounds.left + spriteBounds.width / 2.0f, spriteBounds.top + spriteBounds.height / 2.0f));

	//Покрасим цвет
	text.setFillColor(color);
}

//Возвращает надпись
std::string CenteredText::getLable() {
	return lable;
}
//Устанавливает надпись
void CenteredText::setLable(std::string lable) {
	this->lable = lable;
}