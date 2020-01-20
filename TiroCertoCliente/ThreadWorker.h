#pragma once
class ThreadWorker
{
public:
	ThreadWorker(void);
	virtual ~ThreadWorker(void);
	virtual void run() = 0;
};