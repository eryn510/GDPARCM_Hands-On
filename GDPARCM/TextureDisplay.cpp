#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "MainLoop.h"
#include "ObjectManager.h"
#include "IconObject.h"
#include "DataHandler.h"

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
		if (this->numDisplayed < this->maxLoad) 
		{
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadSingleStreamAsset(this->numDisplayed, this);
			this->numDisplayed++;
		}
		
	}
}

void TextureDisplay::onFinishedExecution()
{
	spawnObject();
}

void TextureDisplay::spawnObject()
{
	DataHandler* data = DataHandler::getInstance();

	std::string objectName = "Icon_" + std::to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	if (iconObj->getIndex() < 10) 
	{
		data->displayList.push_back(iconObj);
		iconObj->setPosition(data->DataList[iconObj->getIndex()].posX, data->DataList[iconObj->getIndex()].posY);
		data->DataList[iconObj->getIndex()].iconRef = iconObj;
		data->DataList[iconObj->getIndex()].occupied = true;
	}
	else 
	{
		DataHandler::getInstance()->displayBank.push(iconObj);
		iconObj->setActive(false);
	}

	std::cout << iconObj->getIndex() << std::endl;

	ObjectManager::getInstance()->addObject(iconObj);

	if (iconObj->getIndex() == maxLoad - 1) 
	{
		data->initializeThreads(2,4);
	}
}

