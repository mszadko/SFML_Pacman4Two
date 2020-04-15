#pragma once
#include <SFML/Graphics.hpp>



class Map : public sf::Drawable
{
public:
	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Texture m_tileset;
	sf::VertexArray m_vertices;


};