#include "ArrowObject.h"
#include "TextureManager.h"
#include <iostream>

ArrowObject::ArrowObject(std::string name) : AObject(name)
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, 0);
	this->sprite->setTexture(*texture);
}

void ArrowObject::Update(sf::Time deltaTime)
{
}
