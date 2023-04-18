#pragma once
#include "IETThread.h"

class SearcherThread : public IETThread
{
public:
	SearcherThread(int id, int holderIndex);
	~SearcherThread();

	// Inherited via IETThread
	virtual void run() override;

private:
	int id = -1;
	int holderIndex = -1;
};

