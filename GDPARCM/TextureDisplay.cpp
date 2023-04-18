#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "MainLoop.h"
#include "ObjectManager.h"
#include "IconObject.h"
TextureDisplay::TextureDisplay(): AObject("TextureDisplay")
{
	
}


void TextureDisplay::Update(sf::Time deltaTime)
{
	this->ticks += MainLoop::TIME_PER_FRAME.asMilliseconds();
	
	if (this->streamingType == StreamingType::BATCH_LOAD && !this->startedStreaming && this->ticks > this->STREAMING_LOAD_DELAY) 
	{
		this->startedStreaming = true;
		this->ticks = 0.0f;
		TextureManager::getInstance()->loadStreamingAssets();

		/*
		while (this->numDisplayed < 50) 
		{
			this->onFinishedExecution();
			this->numDisplayed++;
		}
		*/
	}
	else if (this->streamingType == StreamingType::SINGLE_STREAM && this->ticks > this->STREAMING_LOAD_DELAY) 
	{
		//if (this->numDisplayed < 10) 
		//{
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
			this->numDisplayed++;
		//}
		
	}
}

void TextureDisplay::onFinishedExecution()
{
	spawnObject();
}

void TextureDisplay::spawnObject()
{
	std::string objectName = "Icon_" + std::to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;
	iconObj->setPosition(x, y);

	std::cout << "Set position: " << x << " " << y << std::endl;

	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}

	ObjectManager::getInstance()->addObject(iconObj);
}

