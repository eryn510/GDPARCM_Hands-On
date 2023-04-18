#include "FPSCounter.h"
#include <iostream>
#include "MainLoop.h"

FPSCounter::FPSCounter(): AObject("FPSCounter")
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(MainLoop::WINDOW_WIDTH - 300, MainLoop::WINDOW_HEIGHT - 200);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AObject::~AObject();
}

void FPSCounter::Update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
	//std::cout << this->statsText->getString().toAnsiString() << std::endl;
}

void FPSCounter::Draw(sf::RenderWindow* targetWindow, sf::RenderStates renderStates)
{
	AObject::Draw(targetWindow, renderStates);

	if (this->statsText != nullptr) {
		targetWindow->draw(*this->statsText);
	}
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	float fps = floor(1.0f / elapsedTime.asSeconds());
	char str[40];
	sprintf(str, "%.1f", fps);
	std::string strFPS = str;
	this->statsText->setString("FPS: " + strFPS);
}
