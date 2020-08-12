#include "level.h"
#include "intersection.h"
#include <iostream>

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

bool Level::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
	if (!m_tileset.loadFromFile(tileset))
		return false;
	
	//this is really redundant. 
	recalculateSum();
	processIntersectionArray();

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width*height*4);

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			int tileNumber = sumArray[i + j * width];

			int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
			int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

			sf::Vertex* quad = &m_vertices[(i + j * width)*4];

			quad[0].position = sf::Vector2f(i*tileSize.x, j*tileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		}
	}
	return true;
}
void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = &m_tileset;
	states.transform.scale(2, 2, 0, 0);
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
						intersections[i]->directions.push_back(sf::Vector2f(0.0f, -1.0f));
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
						intersections[i]->directions.push_back(sf::Vector2f(0.0f, 1.0f));
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
						intersections[i]->directions.push_back(sf::Vector2f(-1.0f, 0.0f));
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
						intersections[i]->directions.push_back(sf::Vector2f(1.0f, 0.0f));
						break;
					}
				}
			}
		}
	}
	//add portal intersection connections
	intersections[392]->neighbours.push_back(intersections[419]);
	intersections[392]->directions.push_back(sf::Vector2f(-1.0f, 0.0f));
	intersections[419]->neighbours.push_back(intersections[392]);
	intersections[419]->directions.push_back(sf::Vector2f(1.0f, 0.0f));
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

void Level::recalculateSum()
{
	for (size_t i = 0; i < mapWidth*mapHeight; i++)
	{
		sumArray[i] = levelArray[i] + foodArray[i];
	}
}

bool Level::ConsumeFood(sf::Vector2i location)
{
	if (location.x >= 0 &&location.x<=mapWidth&& location.y >= 0 &&location.y<=mapHeight )
	{
		int index = location.x + location.y*mapWidth;
		if (foodArray[index] == 3)
		{
			foodArray[index] = 0;
			return true;
		}
	}	
	return false;
}