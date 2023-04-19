#include "DeleterThread.h"
#include "DataHandler.h"
#include "IconObject.h"
#include "ArrowObject.h"
#include "ObjectManager.h"
#include <random>
#include <fstream>

DeleterThread::DeleterThread(int id, int holderIndex)
{
	this->id = id;
	this->holderIndex = holderIndex;
}

void DeleterThread::run()
{
	DataHandler* data = DataHandler::getInstance();

	ArrowObject* arrow = new ArrowObject("Deleter");
	arrow->setPosition(data->ArrowList[holderIndex][0].posX, data->ArrowList[holderIndex][0].posY);
	ObjectManager::getInstance()->addObject(arrow);

	system("cls");

	while (true) 
	{
		IETThread::sleep(500);

		//Semaphore Acquire
		data->mutex->acquire();

		static thread_local std::mt19937 generator(std::random_device{}());
		std::uniform_int_distribution<int> distribution(0, 9);

		int randNum = distribution(generator);

		while (data->DataList[randNum].occupied == false) 
		{
			randNum = distribution(generator);
		}

		IconObject* icon = data->DataList[randNum].iconRef;
		arrow->setPosition(data->ArrowList[holderIndex][randNum].posX, data->ArrowList[holderIndex][randNum].posY);
		data->displayList.erase(data->displayList.begin() + randNum);
		data->displayBank.push(icon);

		//Append Deleter cout to txt file
		std::ofstream ofs("logs.txt", std::ios::app);
		std::streambuf* old_cout_buf = std::cout.rdbuf();
		std::cout.rdbuf(ofs.rdbuf());

		std::cout << "\n ==================== DELETER ==================== " << std::endl;
		std::cout << "\nDeleted at index: " << randNum << std::endl;

		std::cout.rdbuf(old_cout_buf);
		ofs.close();

		icon->setActive(false);

		data->DataList[randNum].iconRef = nullptr;
		data->DataList[randNum].occupied = false;

		//Semaphore Release
		data->InsertSem->release();
		data->mutex->release();
	}
	
}
