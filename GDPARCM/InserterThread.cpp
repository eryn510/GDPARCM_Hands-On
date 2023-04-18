#include "InserterThread.h"
#include "DataHandler.h"
#include "IconObject.h"
#include "ArrowObject.h"
#include "ObjectManager.h"

InserterThread::InserterThread(int id, int holderIndex)
{
	this->id = id;
	this->holderIndex = holderIndex;
}

void InserterThread::run()
{
	DataHandler* data = DataHandler::getInstance();

	ArrowObject* arrow = new ArrowObject("Inserter");
	arrow->setPosition(data->ArrowList[holderIndex][0].posX, data->ArrowList[holderIndex][0].posY);
	ObjectManager::getInstance()->addObject(arrow);

	while (true)
	{
		//Semaphore Acquire
		data->InsertSem->acquire();
		data->mutex->acquire();

		int index = -1;

		for (int i = 0; i < data->DataList.size(); i++) 
		{
			if (data->DataList[i].occupied == false) 
			{
				index = i;
				break;
			}
		}


		IconObject* icon = data->displayBank.front();

		icon->setPosition(data->DataList[index].posX, data->DataList[index].posY);
		arrow->setPosition(data->ArrowList[holderIndex][index].posX, data->ArrowList[holderIndex][index].posY);

		data->DataList[index].iconRef = icon;
		data->DataList[index].occupied = true;
		data->displayList.insert(data->displayList.begin() + index, icon);

		std::cout << "\n ==================== INSERTER ==================== " << std::endl;
		std::cout << "\nInserter Index: " << this->id << "\nInserted at index: " << index << std::endl;

		data->displayBank.pop();

		icon->setActive(true);

		//Semaphore Release
		data->mutex->release();
	}
}
