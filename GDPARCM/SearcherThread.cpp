#include "SearcherThread.h"
#include "DataHandler.h"
#include "ArrowObject.h"
#include "ObjectManager.h"
#include <random>

SearcherThread::SearcherThread(int id, int holderIndex)
{
	this->id = id;
	this->holderIndex = holderIndex;
}

void SearcherThread::run()
{
	DataHandler* data = DataHandler::getInstance();

	ArrowObject* arrow = new ArrowObject("Searcher");
	arrow->setPosition(data->ArrowList[holderIndex][0].posX, data->ArrowList[holderIndex][0].posY);
	ObjectManager::getInstance()->addObject(arrow);
	
	while (true) 
	{
		static thread_local std::mt19937 generator(std::random_device{}());
		std::uniform_int_distribution<int> distribution(0, 9);

		int traverser = 0;
		int randNumber = distribution(generator);

		for (traverser = 0; traverser < data->DataList.size(); traverser++)
		{
			//Sleep for arrow traverse
			IETThread::sleep(250);
			arrow->setPosition(data->ArrowList[holderIndex][traverser].posX, data->ArrowList[holderIndex][traverser].posY);
			if (traverser == randNumber)
			{
				//Sleep for traversal stop
				IETThread::sleep(500);
				break;
			}
		}
	}
}
