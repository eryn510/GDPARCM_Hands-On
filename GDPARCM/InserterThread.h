#pragma once
#include "IETThread.h"

class InserterThread : public IETThread
{
public:
	InserterThread(int id, int holderIndex);
	~InserterThread();

	// Inherited via IETThread
	virtual void run() override;

private:
	int id = -1;
	int holderIndex = -1;
};

