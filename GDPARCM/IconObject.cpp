#include "IconObject.h"
#include "TextureManager.h"
#include "MainLoop.h"
#include <iostream>

IconObject::IconObject(std::string name, int textureIndex) : AObject(name), textureIndex(textureIndex)
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	this->sprite->setTexture(*texture);
}

void IconObject::Update(sf::Time deltaTime)
{
	
}

sf::Sprite* IconObject::getSprite()
{
	return this->sprite;
}
