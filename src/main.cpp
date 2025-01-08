#include "sprite.h"
#include "text.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void movement(sf::Sprite& sprite, float speed, float delta);
void borderColision(sf::Sprite& santa, sf::Sprite& present, sf::Sprite& coal);

int main()
{
	sf::Texture backgrdTexture{ "images/background.jpg" };
	sf::Sprite background(backgrdTexture);

	sf::Texture santaTexture{ "images/santa.png" };
	sf::Sprite santa{ santaTexture };
	setPlayerSprite(santa);

	sf::Texture coalTexture{ "images/coal.png" };
	sf::Sprite coal{ coalTexture };
	setOtherSprite(coal);

	sf::Texture presentTexture{ "images/present.png" };
	sf::Sprite present{ presentTexture };
	setOtherSprite(present);

	sf::Font font{ "fonts/Arial.ttf" };
	sf::Text text(font, "REGALOS RECOGIDOS: ", 20);
	setText(text);

	sf::Text presentsCollected(font);
	setPresentText(presentsCollected);

	sf::Text healthRemaining(font, "VIDA RESTANTE:", 20);
	setHealthText(healthRemaining);

	sf::Text santaHealth(font);
	setRemainingHealthText(santaHealth);

	sf::Text defeat(font, "PERDISTE", 40);
	setEndText(defeat);

	sf::Text victory(font, "GANASTE", 40);
	setEndText(victory);


	// window for the game with the format ({WIDTH, HEIGHT}), "TITLE"
	auto window = sf::RenderWindow(sf::VideoMode({ 800, 600 }), "NOEL SALVA LA NAVIDAD");

	// Speed in pixels per second
	float speed{ 500.f };
	// Clock to time frames
	sf::Clock clock;

	// Variable for the presents collected amd for santa's health
	int collected{ 0 }, health{ 5 };

	// The game loop
	while (window.isOpen())
	{
		// Updates the number of presents that have been collected by santa
		presentsCollected.setString(std::to_string(collected));
		santaHealth.setString(std::to_string(health));

		// Sets boxes around the sprites to check if santa has picked them up
		sf::FloatRect santaHitbox = santa.getGlobalBounds();
		sf::FloatRect presentHitbox = present.getGlobalBounds();
		sf::FloatRect coalHitbox = coal.getGlobalBounds();

		// Event handler
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		// If santa hits a present, the number of presents collected increases
		if (const std::optional intersection = santaHitbox.findIntersection(presentHitbox))
		{
			setOtherSprite(present);
			collected += 1;
		}
		// If santa hits a bag of coal, his life decreases
		if (const std::optional intersection = santaHitbox.findIntersection(coalHitbox))
		{
			setOtherSprite(coal);
			health -= 1;
		}

		// Checks if the sprites have reached the border of the screen and sends them to the other side
		borderColision(santa, present, coal);

		// Elapsed time
		float delta = clock.restart().asSeconds();

		// Checks for user imput to move santa
		movement(santa, speed, delta);

		// Present and charcoal falls
		present.move({ 0.f, speed * delta });
		coal.move({ 0.f, speed * delta });

		window.clear();
		window.draw(background);
		window.draw(present);
		window.draw(coal);
		if (health <= 0)
			window.draw(defeat);
		if (collected >= 50)
			window.draw(victory);
		window.draw(santa);
		window.draw(text);
		window.draw(healthRemaining);
		window.draw(santaHealth);
		window.draw(presentsCollected);
		window.display();
	}
}

void borderColision(sf::Sprite& santa, sf::Sprite& present, sf::Sprite& coal)
{
	// If santa reaches one edge of the screen, it will throw it to the other side
	if (santa.getPosition().x > 800.f)
		santa.setPosition({ 0.f, 550.f });
	else if (santa.getPosition().x < 0.f)
		santa.setPosition({ 800.f, 550.f });

	// If the present or charcoal falls out of the screen, it will reaperar on another place on the sky
	if (present.getPosition().y > 600.f)
		setOtherSprite(present);
	if (coal.getPosition().y > 600.f)
		setOtherSprite(coal);
}

void movement(sf::Sprite& sprite, float speed, float delta)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		sprite.move({ -speed * delta, 0.f });
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		sprite.move({ speed * delta, 0.f });
	}
}