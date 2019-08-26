#include <SFML/Graphics.hpp>
#include <iostream>

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	IDLE
};

class Player : public sf::Transformable, public sf::Drawable
{
public:
	Player(float radius, sf::Vector2f startPosition)
	{
		playerSprite = sf::CircleShape(radius);
		setPosition(startPosition);
		playerSprite.setFillColor(sf::Color::Yellow);
		direction = IDLE;
		speed = 90.0f;
	}

	void update(sf::Time deltaTime)
	{
		float elapsed = deltaTime.asSeconds();
		if (direction == UP)
			move(0, -1* elapsed*speed);
		else if (direction == DOWN)
			move(0, 1 * elapsed*speed);
		else if (direction == LEFT)
			move(-1 * elapsed*speed, 0);
		else if (direction == RIGHT)
			move(1 * elapsed*speed, 0);
	}
private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform.translate(floorf(getPosition().x), floorf(getPosition().y));
		target.draw(playerSprite, states);
	}


	sf::CircleShape playerSprite;
	float speed;
public:
	Direction direction;
};




int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Pacman!");
	window.setFramerateLimit(650);
	Player player(15.0f, sf::Vector2f(400.0f, 300.0f));
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
					player.direction = UP;
				else if (event.key.code == sf::Keyboard::Down)
					player.direction = DOWN;
				else if (event.key.code == sf::Keyboard::Left)
					player.direction = LEFT;
				else if (event.key.code == sf::Keyboard::Right)
					player.direction = RIGHT;
			}
		}
		std::cout << deltaTime.asSeconds() << std::endl;
		player.update(deltaTime);
		window.clear();
		window.draw(player);
		window.display();
	}
	return 0;
}