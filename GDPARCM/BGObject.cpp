#include "BGObject.h"
#include "TextureManager.h"
#include "MainLoop.h"
#include <iostream>

BGObject::BGObject(std::string name) : AObject(name)
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap("Desert", 0);
	texture->setRepeated(true);
	this->sprite->setTexture(*texture);
	sf::Vector2u textureSize = this->sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	this->sprite->setTextureRect(sf::IntRect(0,0,MainLoop::WINDOW_WIDTH, MainLoop::WINDOW_HEIGHT * 8));
	this->setPosition(0, -MainLoop::WINDOW_HEIGHT * 7);
}

void BGObject::Update(sf::Time deltaTime)
{
	//make BG scroll slowly
	sf::Vector2f position = this->getPosition();
	position.y += this->SPEED_MULTIPLIER * deltaTime.asSeconds();
	this->setPosition(position.x, position.y);

	sf::Vector2f localPos = this->sprite->getPosition();
	if (localPos.y * deltaTime.asSeconds() > 0) {
		//reset position
		this->setPosition(0, -MainLoop::WINDOW_HEIGHT * 7);
	}
	else {

	}
}
