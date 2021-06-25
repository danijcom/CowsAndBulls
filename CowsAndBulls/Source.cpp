#include "conio.h"
#include "Game.h"
#define ATTEMPTS 30

int main(){
	try {
		Game myGame;
		myGame.run();
	}
	catch (std::exception &error) {
		std::cout << error.what();
		_getch();
	}
	return 0;
}