#include "level.h"
#include "intersection.h"
#include <iostream>

Level::Level()
{	
	m_tileset.loadFromFile("Textures/mapspritesheet.png");
	processIntersectionArray();
	reinit();
}

Level::~Level()
{
	for (size_t i = 0; i < mapWidth; i++)
	{
		for (size_t j = 0; j < mapHeight; j++)
		{
			if (intersections[i*mapWidth+j])
			{
				delete intersections[i*mapWidth + j];
				intersections[i*mapWidth + j] = nullptr;
			}
		}
	}
}

void Level::reinit()
{
	foodArray = foodArrayStartingValue;
}

void Level::update(sf::Time deltaTime)
{
	recalculateSum();
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(mapWidth*mapHeight * 4);

	for (size_t i = 0; i < mapWidth; i++)
	{
		for (size_t j = 0; j < mapHeight; j++)
		{
			int tileNumber = sumArray[i + j * mapWidth];

			int tu = tileNumber % (m_tileset.getSize().x / tileSize);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize);

			sf::Vertex* quad = &m_vertices[(i + j * mapWidth) * 4];

			quad[0].position = sf::Vector2f(i*ftileSize, j*ftileSize);
			quad[1].position = sf::Vector2f((i + 1) * ftileSize, j * ftileSize);
			quad[2].position = sf::Vector2f((i + 1) * ftileSize, (j + 1) * ftileSize);
			quad[3].position = sf::Vector2f(i * ftileSize, (j + 1) *ftileSize);


			quad[0].texCoords = sf::Vector2f(tu * ftileSize, tv * ftileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * ftileSize, tv * ftileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * ftileSize, (tv + 1) * ftileSize);
			quad[3].texCoords = sf::Vector2f(tu * ftileSize, (tv + 1) * ftileSize);
		}
	}
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_tileset;
	target.draw(m_vertices, states);
}

void Level::processIntersectionArray()
{
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		if (intersectionsArray[i])
		{
			Intersection* inter = new Intersection();
			intersections[i] = inter;
			inter->type = intersectionsArray[i];
			inter->intersectionPosition = sf::Vector2i(i % mapWidth, i / mapWidth);
		}
		else
		{
			intersections[i] = nullptr;
		}
	}
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		if (intersections[i] != nullptr)
		{
			int type = intersections[i]->type;
			int column = i % mapWidth;
			int row = i / mapWidth;


			if ((type & 1) == 1)
			{
				for (int r = row - 1; r >= 0; r--)
				{
					if (intersections[r*mapWidth + column] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[r*mapWidth + column]);
						intersections[i]->directions.push_back(Direction::UP);
						break;
					}
				}
			}
			if ((type & 2) == 2)
			{
				for (size_t r = row + 1; r <= mapHeight; r++)
				{
					if (intersections[r*mapWidth + column] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[r*mapWidth + column]);
						intersections[i]->directions.push_back(Direction::DOWN);
						break;
					}
				}
			}
			if ((type & 4) == 4)
			{
				for (int c = column - 1; c >= 0; c--)
				{
					if (intersections[row*mapWidth + c] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[row*mapWidth + c]);
						intersections[i]->directions.push_back(Direction::LEFT);
						break;
					}
				}
			}
			if ((type & 8) == 8)
			{
				for (size_t c = column + 1; c < mapWidth; c++)
				{
					if (intersections[row*mapWidth + c] != nullptr)
					{
						intersections[i]->neighbours.push_back(intersections[row*mapWidth + c]);
						intersections[i]->directions.push_back(Direction::RIGHT);
						break;
					}
				}
			}
		}
	}
	//add portal intersection connections
	intersections[392]->neighbours.push_back(intersections[419]);
	intersections[392]->directions.push_back(Direction::LEFT);
	intersections[419]->neighbours.push_back(intersections[392]);
	intersections[419]->directions.push_back(Direction::RIGHT);
}

Intersection* Level::GetIntersectionAt(int x, int y)
{
	if (x > mapWidth || y > mapHeight)
		return nullptr;
	int index = x + y * mapWidth;
	return intersections[index];
}

Intersection* Level::GetIntersectionAt(sf::Vector2i location)
{
	return GetIntersectionAt(location.x, location.y);
}

Intersection* Level::GetIntersectionAt(sf::Vector2f location)
{
	sf::Vector2i locationToMapCoords((int)roundf(location.x / ftileSize), (int)roundf(location.y / ftileSize));
	return GetIntersectionAt(locationToMapCoords);
}
	

void Level::recalculateSum()
{
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		sumArray[i] = levelArray[i] + foodArray[i];
	}
}

FoodType Level::ConsumeFood(sf::Vector2i location)
{
	if (location.x >= 0 &&location.x<=mapWidth&& location.y >= 0 &&location.y<=mapHeight )
	{
		int index = location.x + location.y*mapWidth;
		if (foodArray[index] == REGULAR)
		{
			foodArray[index] = 0;
			return REGULAR;
		}
		else if (foodArray[index] == POWERUP)
		{
			foodArray[index] = 0;
			return POWERUP;
		}
	}	
	return EMPTY;
}

int Level::GetFoodLeft()
{
	int amount = 0;
	for (size_t i = 0; i < foodArray.size(); i++)
	{
		if (foodArray[i])
		{
			amount++;
		}
	}
	return amount;
}
