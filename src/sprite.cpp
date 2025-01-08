#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>

sf::Sprite setPlayerSprite(sf::Sprite& sprite)
{
	sprite.setOrigin({ 32.f, 32.f });
	sprite.setPosition({ 400.f, 550.f });
	return sprite;
}

sf::Sprite setOtherSprite(sf::Sprite& sprite)
{
	float randomNum = rand() % 801;
	sprite.setOrigin({ 16.f, 16.f });
	sprite.setPosition({ randomNum, 20.f });
	return sprite;
}