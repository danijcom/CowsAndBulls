#pragma once
#include "vector"
#include "iostream"
#include "random"
#include "string"
#include "tuple"

//Идентификаторы комбинаций
namespace Combinations {
	enum RESULT {
		CORRECT,    //Комбинация отгадана
		INCORRECT,  //Не отгадана
		REPEAT,     //Уже вводилась
		ATTEMPTSMAX //Достингут лимит попыток
	};
}

//Основной класс, реализующий базовую логику игры
class CowsAndBulls {
public:
	//Секретное число (строкой)
	std::string secretNumber;
	//Массив попыток
	std::vector<std::string> attempts;
	//Время начала игры
	std::time_t startTime;

	//Генератор случайного числа
	std::string makeSecret(int = 4);
public:
	//Конструктор
	CowsAndBulls();
	//Подсчет животных
	std::tuple<int, int> countAnimals(std::string);
	//Проверка введенного числа, сохранение его в массив ходов
	Combinations::RESULT check(std::string);
	//Проведенное время в игре в секундах
	std::time_t elapcedTime();
	//Кол-во сделанных попыток
	int getSteps();
	//Получить секретное число
	std::string getSecret();
	//Начата ли игра
	bool isStarted();
	//Начать игру
	void setStart();
};
