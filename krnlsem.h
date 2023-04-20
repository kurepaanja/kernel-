

#ifndef KRNLSEM_H_
#define KRNLSEM_H_

#include "queue.h"

class Queue;
class Semaphore;

class KernelSem{
public:
	KernelSem(int v, Semaphore *mySem);
	~KernelSem();

	int wait(int toBlock);
	void signal();

	int val() const { return value; }

private:
   int value;
   Queue *blockedList;
   Semaphore *mySem;
};




#endif /* KRNLSEM_H_ */
