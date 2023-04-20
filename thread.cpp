
#include "thread.h"
#include "pcb.h"
#include "system.h"
#include "SCHEDULE.H"

extern int syncPrintf(const char *format, ...);


Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(stackSize,timeSlice,this);
}

Thread::~Thread(){
	lock
	delete myPCB;
	unlock
	myPCB=0;
}
void dispatch(){
	syncPrintf("dispatch\n");
#ifndef BCC_BLOCK_IGNORE
	lock
	System::context_switch_on_demand=1;
	System::timer();
	unlock
#endif
}

int Thread::getId(){
	return myPCB->getID();
}

void Thread::start(){
	myPCB->startPCB();
}

void Thread::waitToComplete(){
	myPCB->waitToCompletePCB();
}

Thread* Thread::getThreadById(int id){
	if(System::AllThreads->find(id)){
		PCB* help=System::AllThreads->find(id);
		return help->myThread;
	}
	else return 0;
}
