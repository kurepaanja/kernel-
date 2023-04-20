

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "system.h"
#include "queue.h"

class PCB{
private:
	StackSize stackSize;
	unsigned ss;
	unsigned sp;
	unsigned bp;
	unsigned* stack;
	unsigned timeSlice;
	int finished;
	int blocked;
	int not_time_dependent;
	static int lastID;
	int id;


	Queue* BlockedList;

	friend class System;

	void initialize();
	void finishedPCB();

public:
	PCB(StackSize stackSize=defaultStackSize,unsigned timeSlice=defaultTimeSlice,Thread* thread);
	~PCB();
	static void wrapped();
	int getID(){
		return id;
	}
	void startPCB();
	int start;
	void waitToCompletePCB();
	Thread* myThread;
};



#endif /* PCB_H_ */
