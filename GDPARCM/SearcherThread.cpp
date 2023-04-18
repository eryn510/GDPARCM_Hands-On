#include "SearcherThread.h"
#include "DataHandler.h"
#include "ArrowObject.h"
#include "ObjectManager.h"

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
		IETThread::sleep(500);
		
		srand(time(NULL));

		int randNum = rand() % data->DataList.size();
		int traverser = 0;

		for (traverser = 0; traverser < data->DataList.size(); traverser++)
		{
			IETThread::sleep(250);
			arrow->setPosition(data->ArrowList[holderIndex][traverser].posX, data->ArrowList[holderIndex][traverser].posY);
			//std::cout << "Traversing Number: " << traverser << std::endl;
			//std::cout << "Index Number: " << this->id << std::endl;
			if (traverser == randNum) 
			{
				IETThread::sleep(500);
				break;
			}
		}
	}
}
