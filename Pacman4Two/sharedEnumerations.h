#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>


enum PacketTag
{
	Empty,
	ToServerClientPressedButton,
	ToClientPlayerNewWalkInfo,
	ToClientPositionCorrection
};

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

enum ConnectionType
{
	NONE,
	CLIENTONE,
	CLIENTTWO,
	SERVER
};

enum PlayerNumer
{
	FIRST = 0,
	SECOND = 1
};

enum WalkableID
{
	GHOSTONE,
	GHOSTTWO,
	GHOSTTHREE,
	GHOSTFOUR,
	PLAYERONE,
	PLAYERTWO
};

enum GhostType
{
	RED,
	PINK,
	BLUE,
	ORANGE
};
enum GhostFrightenedState
{
	NOTFRIGHTENED,
	FRIGHTENED,
	FRIGHTENEDENDING
};

static const int mapWidth = 28;
static const int mapHeight = 31;
static const int tileSize = 16;
static const float ftileSize = 16.0f;

const unsigned short serverPort = 54000;
const unsigned short clientOnePort = 54001;
const unsigned short clientTwoPort = 54002;

template<typename T>
T VectorDifferenceMagnitue(sf::Vector2<T> from, sf::Vector2<T> to)
{
	sf::Vector2<T> diff = to - from;
	T distance = T(std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2)));
	return distance;
}
