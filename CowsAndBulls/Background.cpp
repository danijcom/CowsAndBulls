#include "Background.h"
#include "array"

namespace Globals {
	extern int __W_HEIGHT__;
	extern int __W_WIDTH__;
	extern float __W_SCALE__;
}

//Конструктор
Background::Background(sf::RenderWindow* window, sf::Texture& textureBG, sf::Texture& textureWings, sf::Texture& textureCloud1, sf::Texture& textureCloud2, sf::Texture& textureCloud3, std::array<float, 3> cloudSpeeds) {
	//Создаем фон
	background = new MySprite(window, textureBG, false);

	//Создаем лопасти мельницы, помещаем их в нужное место
	wings = new Wings(window, textureWings);
	wings->setPosition(1124 * Globals::__W_SCALE__, 2215 * Globals::__W_SCALE__);

	//Создем все 3 облака, помещаем все в нужные места
	Cloud* cloud = new Cloud(window, textureCloud1, true, cloudSpeeds[0]);
	cloud->setPosition(0 - (cloud->getSize().x / 2), 1140 * Globals::__W_SCALE__);
	clouds.push_back(cloud);

	cloud = new Cloud(window, textureCloud2, true, cloudSpeeds[1]);
	cloud->setPosition(Globals::__W_WIDTH__ + (cloud->getSize().x / 2), 660 * Globals::__W_SCALE__);
	clouds.push_back(cloud);

	cloud = new Cloud(window, textureCloud3, true, cloudSpeeds[2]);
	cloud->setPosition(0 - (cloud->getSize().x / 2), 250 * Globals::__W_SCALE__);
	clouds.push_back(cloud);
}

//Шаг графики - рисуем фон, крутим и рисуем лопасти, двигаем и рисуем облака
void Background::step() {
	background->draw();
	wings->step();
	for (Cloud* cloud : clouds)
		cloud->step();
}