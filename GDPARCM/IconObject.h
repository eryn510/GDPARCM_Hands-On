#pragma once
#include "AObject.h"

class IconObject : public AObject
{
public:
	IconObject(std::string name, int textureIndex);
	virtual void Update(sf::Time deltaTime) override;

public:
	sf::Sprite* getSprite();
	int getIndex();

private:
	int textureIndex = 0;

};

