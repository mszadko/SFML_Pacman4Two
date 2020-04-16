#include "player.h"


Player::Player(float radius, sf::Vector2f startPosition, float speed)
{
	playerSprite = sf::CircleShape(radius);
	setPosition(startPosition);
	playerSprite.setFillColor(sf::Color::Yellow);
	direction = LEFT;
	this->speed = speed;
	collider.bounds = playerSprite.getGlobalBounds();
	collider.owner = this;
}
void Player::processEvents(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Up)
		direction = UP;
	else if (event.key.code == sf::Keyboard::Down)
		direction = DOWN;
	else if (event.key.code == sf::Keyboard::Left)
		direction = LEFT;
	else if (event.key.code == sf::Keyboard::Right)
		direction = RIGHT;
}

void Player::update(sf::Time deltaTime)
{
	float elapsed = deltaTime.asSeconds();
	if (direction == UP)
		move(0, -1 * elapsed*speed);
	else if (direction == DOWN)
		move(0, 1 * elapsed*speed);
	else if (direction == LEFT)
		move(-1 * elapsed*speed, 0);
	else if (direction == RIGHT)
		move(1 * elapsed*speed, 0);
	collider.bounds = playerSprite.getGlobalBounds();
	playerSprite.setPosition(floorf(getPosition().x), floorf(getPosition().y));
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(playerSprite, states);
}