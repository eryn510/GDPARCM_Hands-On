#pragma once
#include "AObject.h"
class BGObject : public AObject
{
public:
	BGObject(std::string name);
	virtual void Update(sf::Time deltaTime) override;

private:
	const float SPEED_MULTIPLIER = 100.0f;
};

