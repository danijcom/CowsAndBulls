#include "CowsAndBulls.h"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

#ifndef ATTEMPTS
#define ATTEMPTS 30
#endif // !ATTEMPTS

//Конструктор
CowsAndBulls::CowsAndBulls() {
	this->secretNumber = makeSecret();
	std::cout << "SecretNumber: [" << this->secretNumber << "]" << std::endl;
	this->startTime = 0;
}

//Генератор случайного числа
std::string CowsAndBulls::makeSecret(int len) {
	//Лимит в 10 символов
	if (len > 10)
		throw std::runtime_error("You can not generate more then 10 numbers!");

	//Временная строка и массив цифр
	std::string tmp;
	std::vector<int> numbers = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	//Генератор случайных чисел из C++11
	std::random_device rd;
	//Тип генератора - mersenne twister
	std::mt19937 g(rd());

	//Перемешиваем цифры
	std::shuffle(numbers.begin(), numbers.end(), g);

	//Заполняем строку цифрами
	for (int i = 0; i < len; i++)
		tmp += std::to_string(numbers[i]);

	return tmp;
}

//Подсчет животных
std::tuple<int, int> CowsAndBulls::countAnimals(std::string combination) {
	std::string comb = combination;
	std::string secret = this->secretNumber;
	int cows = 0, bulls = 0;

	for (int i = 0; i < comb.length(); i++) {
		if (secret[i] == comb[i]) {
			bulls++;
			comb[i] = '*';
			secret[i] = '-';
		}
	}
	for (int i = 0; i < comb.length(); i++) {
		for (int j = 0; j < secret.length(); j++) {
			if (comb[i] == secret[j]) {
				cows++;
				comb[i] = '*';
				secret[j] = '-';
			}
		}
	}
	return { cows, bulls };
}
//Проверка введенного числа, сохранение его в массив ходов
Combinations::RESULT CowsAndBulls::check(std::string combination) {
	if (std::find(attempts.begin(), attempts.end(), combination) != attempts.end())
		return Combinations::RESULT::REPEAT;
	else {
		attempts.push_back(combination);
		if (secretNumber == combination)
			return Combinations::RESULT::CORRECT;
		else {
			if (attempts.size() >= ATTEMPTS)
				return Combinations::RESULT::ATTEMPTSMAX;
			else
				return Combinations::RESULT::INCORRECT;
		}

	}
}
//Проведенное время в игре в секундах
std::time_t CowsAndBulls::elapcedTime() {
	return std::time(0) - startTime;
}
//Кол-во сделанных попыток
int CowsAndBulls::getSteps() {
	return attempts.size();
}
//Получить секретное число
std::string CowsAndBulls::getSecret() {
	return secretNumber;
}
//Начата ли игра
bool CowsAndBulls::isStarted() {
	return startTime != 0;
}
//Начать игру
void CowsAndBulls::setStart() {
	this->startTime = std::time(0);
}