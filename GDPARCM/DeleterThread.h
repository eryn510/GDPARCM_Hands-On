#pragma once
#include "IETThread.h"

class DeleterThread : public IETThread
{
public:
	DeleterThread(int id, int holderIndex);
	~DeleterThread();

	// Inherited via IETThread
	virtual void run() override;

private:
	int id = -1;
	int holderIndex = -1;
};

