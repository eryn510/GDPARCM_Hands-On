#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class AObject
{
public:
	AObject(std::string name);
	virtual ~AObject();

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates);

	std::string getName();

	virtual void setPosition(float x, float y);
	virtual void setScale(float x, float y);
	virtual sf::FloatRect getLocalBounds();
	virtual sf::Vector2f getPosition();
	virtual sf::Vector2f getScale();

protected:
	std::string name;
	sf::Sprite* sprite;
	sf::Texture* texture;

	float posX = 0.0f; float posY = 0.0f;
	float scaleX = 1.0f; float scaleY = 1.0f;

};

