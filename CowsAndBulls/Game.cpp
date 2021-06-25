#include "Game.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
Game::Game() {
	//Просчет размеров окна и коэффицента для подстройки размеров
	calculateScale();
	//Загружаем текстуры
	loadAssets();
	//Создаем окно
	window = new sf::RenderWindow(
		sf::VideoMode(Globals::__W_WIDTH__, Globals::__W_HEIGHT__), //Окно размеров W_WIDTH, W_HEIGHT
		"Cows and Bulls", //Тайтл
		sf::Style::None //Убираем контролл бокс окна
	);
	//Создаем фон
	background = new Background(
		window, //Наше окно
		texturesHolder.get(Textures::Background), //Текстура фона
		texturesHolder.get(Textures::Wings), //Лопости мельницы
		texturesHolder.get(Textures::Cloud1), texturesHolder.get(Textures::Cloud2), texturesHolder.get(Textures::Cloud3), //Текстуры всех 3х облаков
		{ 1, -0.7, 0.5 } //Скорости облаков
	);
	//Создаем плейсхолдеры под цифры
	placeholders = new Placeholders(
		window, //Наше окно
		texturesHolder.get(Textures::Placeholder) //Текстура плейсхолдеров
	);
	//Создаем все кнопки (клавиатуру и две служебные)
	buttons = new ButtonsLayer(
		window, //Наше окно
		texturesHolder.get(Textures::ButtonNumber), //Текстура кнопки клавиатуры
		fontsHolder.get(Fonts::LotusMono),          //Шрифт кнопки клавиатуры
		texturesHolder.get(Textures::ButtonExit),   //Текстура кнопки выхода
		texturesHolder.get(Textures::ButtonAbout)   //Текстура кнопки информации
	);
	//Создаем табло
	scoreBoard = new ScoreBoard();

	//Ограничение 60 кадров/с
	window->setFramerateLimit(60);

	//Создаем игровой обработчик
	cowsAndBulls = new CowsAndBulls();

	grabbedWindow = false;
}

//Просчет размеров окна и коэффицента для подстройки размеров
	// все текстуры экспортировались с запасом, под размер окна 3000*1500
	// но так как разрешения экранов у всех разные - нужно подстроить текстуры
	// под разные разрешения с помощью коэффициента Globals::__W_SCALE__
	void Game::calculateScale() {
		int screenH = sf::VideoMode::getDesktopMode().height;
		if (screenH >= 3000) {
			Globals::__W_HEIGHT__ = 3000;
			Globals::__W_WIDTH__ = 1500;
			Globals::__W_SCALE__ = 1;
		}
		else if (screenH >= 2000) {
			Globals::__W_HEIGHT__ = 2000;
			Globals::__W_WIDTH__ = 1000;
			Globals::__W_SCALE__ = 1 / 1.5;
		}
		else if (screenH >= 1600) {
			Globals::__W_HEIGHT__ = 1600;
			Globals::__W_WIDTH__ = 800;
			Globals::__W_SCALE__ = 0.53333333;
		}
		else if (screenH >= 1000) {
			Globals::__W_HEIGHT__ = 1000;
			Globals::__W_WIDTH__ = 500;
			Globals::__W_SCALE__ = 0.333333333;
		}
		else if (screenH >= 700) {
			Globals::__W_HEIGHT__ = 700;
			Globals::__W_WIDTH__ = 350;
			Globals::__W_SCALE__ = 0.2333333333;
		}
		else
			throw std::runtime_error("Can not set scale for this screen size!");
	}

//Загрузка текстур и шрифтов(а)
void Game::loadAssets() {
	texturesHolder.load(Textures::Background, "..//assets/textures/background.png");
	texturesHolder.load(Textures::Wings, "..//assets/textures/wings.png");
	texturesHolder.load(Textures::Cloud1, "..//assets/textures/cloud1.png");
	texturesHolder.load(Textures::Cloud2, "..//assets/textures/cloud2.png");
	texturesHolder.load(Textures::Cloud3, "..//assets/textures/cloud3.png");
	texturesHolder.load(Textures::AboutText, "..//assets/textures/about_text.png");
	texturesHolder.load(Textures::ButtonAbout, "..//assets/textures/about.png");
	texturesHolder.load(Textures::ButtonExit, "..//assets/textures/exit.png");
	texturesHolder.load(Textures::ButtonNumber, "..//assets/textures/number.png");
	texturesHolder.load(Textures::Placeholder, "..//assets/textures/placeholder.png");
	texturesHolder.load(Textures::PopupError, "..//assets/textures/popup_error.png");
	texturesHolder.load(Textures::PopupSuccess, "..//assets/textures/popup_success.png");
	texturesHolder.load(Textures::PopupInfo, "..//assets/textures/popup_info.png");
	texturesHolder.load(Textures::ScoreRow, "..//assets/textures/score_row.png");
	texturesHolder.load(Textures::ScoreRowWin, "..//assets/textures/score_row_win.png");
	texturesHolder.load(Textures::ScoreRowLose, "..//assets/textures/score_row_lose.png");
	texturesHolder.load(Textures::YouWon, "..//assets/textures/you_won.png");
	texturesHolder.load(Textures::YouLost, "..//assets/textures/you_lose.png");

	fontsHolder.load(Fonts::LotusMono, "..//assets/fonts/lotus.ttf");
}

//Отправить всплывающее сообщение
void Game::firePush(sf::Texture& bgTexture, sf::Color color, sf::Font& font, std::string label, int fontSize, int speed, int lifetime, int yOffset) {
	if (this->pushMessage != NULL) {
		delete pushMessage;
	}
	this->pushMessage = new PushMessage(window, bgTexture, color, font, label, fontSize, speed);
	this->pushMessage->setPosition(Globals::__W_WIDTH__ / 2, 2 - pushMessage->getSize().y / 2, true);
	this->pushMessage->setTransit({ (float)(Globals::__W_WIDTH__ / 2), (float)(100 * Globals::__W_SCALE__ + yOffset * Globals::__W_SCALE__) }, lifetime);
}

//Обработка введенной пользователем комбинации
void Game::processCombination(std::string combination) {
	Combinations::RESULT result = cowsAndBulls->check(combination);
	//Если она уже вводилась, то просто сделаем всплывающее сообщение
	if (result == Combinations::RESULT::REPEAT) {
		firePush(texturesHolder.get(Textures::PopupError), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "Already used!", 75 * Globals::__W_SCALE__, 3, 3);
		placeholders->clear();
	}
	//Если она неверная, то добавим ее на табло
	else if (result == Combinations::RESULT::INCORRECT) {
		std::tuple<int, int> cAb = cowsAndBulls->countAnimals(combination);
		ScoreRow sr(window, texturesHolder.get(Textures::ScoreRow), fontsHolder.get(Fonts::LotusMono), sf::Color::White, combination, std::get<1>(cAb), std::get<0>(cAb), 5);
		(*scoreBoard) + sr;
		placeholders->clear();
	}
	//Если это победная комбинация - сделаем всплывающее сообщение, скроем кнопки и плейсхолдеры, выведем табло об окончании игры
	else if (result == Combinations::RESULT::CORRECT) {
		firePush(texturesHolder.get(Textures::PopupSuccess), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "YOU WIN", 90 * Globals::__W_SCALE__, 3, 60 * 5);
		ScoreRow sr(window, texturesHolder.get(Textures::ScoreRowWin), fontsHolder.get(Fonts::LotusMono), sf::Color::Black, combination, 4, 0, 5);
		(*scoreBoard) + sr;
		buttons->setKeyboardActive(false);
		lastPressed = Buttons::BUTTON_TYPES::NONE;
		buttons->setHidden(true);
		placeholders->setHidden(true);
		gameResult = new GameResult(window, texturesHolder.get(Textures::YouWon), fontsHolder.get(Fonts::LotusMono), sf::Color::White, cowsAndBulls->elapcedTime(), std::to_string(cowsAndBulls->getSteps()), cowsAndBulls->getSecret());
	}
	//Если достигнут максимум попыток - сделаем всплывающее сообщение, выведем табло о проигрыше
	else if (result == Combinations::RESULT::ATTEMPTSMAX) {
		firePush(texturesHolder.get(Textures::PopupError), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "YOU LOSE", 90 * Globals::__W_SCALE__, 3, 60 * 5);
		ScoreRow sr(window, texturesHolder.get(Textures::ScoreRowLose), fontsHolder.get(Fonts::LotusMono), sf::Color::White, combination, 4, 0, 5);
		(*scoreBoard) + sr;
		buttons->setKeyboardActive(false);
		lastPressed = Buttons::BUTTON_TYPES::NONE;
		buttons->setHidden(true);
		placeholders->setHidden(true);
		gameResult = new GameResult(window, texturesHolder.get(Textures::YouLost), fontsHolder.get(Fonts::LotusMono), sf::Color::White, cowsAndBulls->elapcedTime(), std::to_string(cowsAndBulls->getSteps()), cowsAndBulls->getSecret());
	}
}

//Функция для обработки событий
void Game::processEvents() {
	sf::Event event;
	Buttons::BUTTON_TYPES lastPressedBuff = lastPressed;

	//Считываем события
	window->pollEvent(event);

	//Если последней нажатой кнопкой было число
	if (lastPressed == Buttons::BUTTON_TYPES::NUMBER) {
		
		//С первой нажатой цифрой запустим игру, если она не запущена
		if (!cowsAndBulls->isStarted())
			cowsAndBulls->setStart();

		//Если поле для ввода полно (есть комбинация)
		if (placeholders->isFull()) {
			//То обработаем собранную комбинацию
			try {
				processCombination(placeholders->getCombination());
			}
			catch (std::exception& err) {
				std::cout << "That should not happened, but its not critical error: " << err.what();
			}
		}
	}

	//Обработка нажатий кнопки мыши
	if (event.type == sf::Event::MouseButtonPressed) {
		if (event.key.code == sf::Mouse::Left) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
			lastPressed = buttons->processClick(mousePos, placeholders);
			//Если кнопки не нажаты, и есть уведомление - проверим, может нажали на него?
			if (pushMessage != NULL && lastPressed == Buttons::BUTTON_TYPES::NONE)
				pushMessage->processClick(sf::Mouse::getPosition(*window));
			//Обработка кнопки выход
			if (lastPressed == Buttons::BUTTON_TYPES::EXIT) {
				//В первый раз переспросим
				if (lastPressedBuff != Buttons::BUTTON_TYPES::EXIT && gameResult == NULL)
					firePush(texturesHolder.get(Textures::PopupInfo), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "Press again", 80 * Globals::__W_SCALE__, 3, 3);
				//Во второй закроемся
				else {
					window->close();
					exit(0);
				}
			}
			//Обработка кнопки "?"
			if (lastPressed == Buttons::BUTTON_TYPES::ABOUT) {
				//В первый раз переспросим (там просто огромное сообщение)
				if (lastPressedBuff != Buttons::BUTTON_TYPES::ABOUT)
					firePush(texturesHolder.get(Textures::PopupInfo), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "Press again", 80 * Globals::__W_SCALE__, 3, 3);
				//Во второй выведем информацию
				else
					firePush(texturesHolder.get(Textures::AboutText), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "", 80 * Globals::__W_SCALE__, 5, 15, 450);
			}
		}
		//Фиксируем движение мышки с зажатой клавишей для перемещения окна
		if (event.mouseButton.button == sf::Mouse::Right)
			grabbedOffset = window->getPosition() - sf::Mouse::getPosition();
	}
	//Не сделать возможности вводить цифры клавиатурой - кощунство
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
			lastPressed = buttons->processKBClick("0", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
			lastPressed = buttons->processKBClick("1", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
			lastPressed = buttons->processKBClick("2", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
			lastPressed = buttons->processKBClick("3", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
			lastPressed = buttons->processKBClick("4", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
			lastPressed = buttons->processKBClick("5", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
			lastPressed = buttons->processKBClick("6", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
			lastPressed = buttons->processKBClick("7", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
			lastPressed = buttons->processKBClick("8", placeholders);
		}
		else if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
			lastPressed = buttons->processKBClick("9", placeholders);
		}
		else if (event.key.code == sf::Keyboard::BackSpace || event.key.code == sf::Keyboard::Delete) {
			lastPressed = buttons->processKBClick("<<", placeholders);
		}
	}
	//Обработка перемещений мыши
	else if (event.type == sf::Event::MouseMoved) {
		buttons->processHover(sf::Mouse::getPosition(*window));
	}
	//Смещаем окно, если клавиша отпущена, и окно было в состоянии перемещения
	grabbedWindow = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (grabbedWindow)
		window->setPosition(sf::Mouse::getPosition() + grabbedOffset);
}

//Основная функция, вызывающая всю логику игры
void Game::run() {
	//Выведем сообщение о начале игры
	firePush(texturesHolder.get(Textures::PopupSuccess), sf::Color::White, fontsHolder.get(Fonts::LotusMono), "LETS START", 90 * Globals::__W_SCALE__, 3, 4);

	//Основной цикл приложения
	while (window->isOpen()) {
		processEvents();
		window->clear();
		background->step();
		placeholders->draw();
		buttons->draw();
		scoreBoard->draw();
		if (pushMessage != NULL)
			pushMessage->draw();
		if (gameResult != NULL)
			gameResult->draw();
		window->display();
	}
}