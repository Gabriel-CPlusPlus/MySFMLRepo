#include <SFML/Graphics.hpp>

sf::Text setText(sf::Text& text)
{
	text.setOrigin({ 24.f, 24.f });
	text.setPosition({ 30.f, 25.f });
	return text;
}

sf::Text setPresentText(sf::Text& text)
{
	text.setOrigin({ 24.f, 24.f });
	text.setPosition({ 270.f, 25.f });
	text.setCharacterSize(20);
	return text;
}

sf::Text setHealthText(sf::Text& text)
{
	text.setOrigin({ 24.f, 24.f });
	text.setPosition({ 30.f, 50.f });
	return text;
}

sf::Text setRemainingHealthText(sf::Text& text)
{
	text.setOrigin({ 24.f, 24.f });
	text.setPosition({ 200.f, 50.f });
	text.setCharacterSize(20);
	return text;
}

sf::Text setEndText(sf::Text& text)
{
	text.setOrigin({ 100.f, 20.f });
	text.setPosition({ 400.f, 300.f });
	text.setFillColor(sf::Color::Blue);
	return text;
}