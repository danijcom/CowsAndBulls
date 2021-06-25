#pragma once
#include "Wings.h"
#include "Cloud.h"

//Класс фон, содержит в себе спрайт с фоновой картинкой, облака, лопасти мельницы
class Background {
private:
	//Обьект для фона
	MySprite* background;
	//Для крыльев мельницы
	Wings* wings;
	//Вектор с облаками
	std::vector<Cloud*> clouds;

public:
	//Конструктор
	Background(sf::RenderWindow*, sf::Texture&, sf::Texture&, sf::Texture&, sf::Texture&, sf::Texture&, std::array<float, 3>);

	//Шаг графики - рисуем фон, крутим и рисуем лопасти, двигаем и рисуем облака
	void step();
};