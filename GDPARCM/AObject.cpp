#include "AObject.h"
#include <iostream>

AObject::AObject(std::string name) : name(name)
{

}

AObject::~AObject() 
{
	if (this->sprite != NULL) {
		delete this->sprite;
	}	
}

std::string AObject::getName() 
{
	return name;
}

void AObject::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) 
{
	if (this->sprite != NULL) {
		this->sprite->setPosition(this->posX, this->posY);
		this->sprite->setScale(this->scaleX, this->scaleY);
		targetWindow->draw(*this->sprite);
	}
}

void AObject::Update(sf::Time deltaTime) 
{
	// Add Implementation here
}

void AObject::setPosition(float x, float y)
{
	this->posX = x;
	this->posY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setPosition(this->posX, this->posY);
	}
}

void AObject::setScale(float x, float y)
{
	this->scaleX = x;
	this->scaleY = y;

	if (this->sprite != nullptr)
	{
		this->sprite->setScale(this->scaleX, this->scaleY);
	}
}

sf::Vector2f AObject::getPosition()
{
	return this->sprite->getPosition();
}

sf::Vector2f AObject::getScale()
{
	return this->sprite->getScale();
}

sf::FloatRect AObject::getLocalBounds()
{
	return this->sprite->getLocalBounds();
}

