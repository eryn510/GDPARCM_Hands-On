#pragma once
#include "AObject.h"
class ArrowObject : public AObject
{
public:
	ArrowObject(std::string name);
	virtual void Update(sf::Time deltaTime) override;
};

