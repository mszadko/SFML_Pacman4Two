#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	IDLE
};
enum FoodType
{
	EMPTY = 0,
	POWERUP = 2,
	REGULAR = 3
};
enum GameState
{
	STOPPED,
	RUNNING
};

static const int mapWidth = 28;
static const int mapHeight = 31;
static const int tileSize = 16;
static const float ftileSize = 16.0f;

template<typename T>
T VectorDifferenceMagnitue(sf::Vector2<T> from, sf::Vector2<T> to)
{
	sf::Vector2<T> diff = to - from;
	T distance = T(std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2)));
	return distance;
}
