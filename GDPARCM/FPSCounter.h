#pragma once
#include "AObject.h"

class FPSCounter :    public AObject
{
	public:
		FPSCounter();
		~FPSCounter();
		void Update(sf::Time deltaTime) override;
		void Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates) override;
	
	private:
		sf::Time updateTime;
		sf::Text* statsText;
		int framesPassed = 0;

		void updateFPS(sf::Time elapsedTime);
		
};

