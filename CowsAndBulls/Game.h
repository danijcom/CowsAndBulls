#pragma once
#include "Background.h"
#include "Placeholders.h"
#include "ButtonsLayer.h"
#include "ScoreBoard.h"
#include "PushMessage.h"
#include "CowsAndBulls.h"
#include "GameResult.h"
#include "ResourceHolder.hpp"

//Основной класс игра
class Game {
private:
	//Обьект окна
	sf::RenderWindow* window;

	//Обьекты хранилища под шрифты и текстуры
	ResourceHolder<sf::Texture, Textures::ID> texturesHolder;
	ResourceHolder<sf::Font, Fonts::ID> fontsHolder;

	//Обьект фона
	Background* background;
	//Обьект плейсхолдеров для кнопок
	Placeholders* placeholders;
	//Обьект кнопок
	ButtonsLayer* buttons;

	//Обьект табло
	ScoreBoard* scoreBoard;
	//Обьект всплывающего сообщения
	PushMessage* pushMessage = NULL;

	//Обьект обработчика коров и быков
	CowsAndBulls* cowsAndBulls;

	//Тип последней нажатой кнопки
	Buttons::BUTTON_TYPES lastPressed;

	//Табло об окончании игры
	GameResult* gameResult = NULL;

	//Для drag&drop окна
	sf::Vector2i grabbedOffset;
	bool grabbedWindow;

	//Просчет размеров окна и коэффицента для подстройки размеров
	// все текстуры экспортировались с запасом, под размер окна 3000*1500
	// но так как разрешения экранов у всех разные - нужно подстроить текстуры
	// под разные разрешения с помощью коэффициента Globals::__W_SCALE__
	void calculateScale();
public:
	//Конструктор
	Game();

	//Загрузка текстур и шрифтов(а)
	void loadAssets();

	//Отправить всплывающее сообщение
	void firePush(sf::Texture&, sf::Color, sf::Font&, std::string, int = 60, int = 20, int = 5, int = 0);

	//Обработка введенной пользователем комбинации
	void processCombination(std::string);

	//Функция для обработки событий
	void processEvents();

	//Основная функция, вызывающая всю логику игры
	void run();
};
