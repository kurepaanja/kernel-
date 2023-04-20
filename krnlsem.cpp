

#include "krnlsem.h"
#include "pcb.h"
#include "system.h"
#include "queue.h"
#include "SCHEDULE.H"


KernelSem::KernelSem(int v, Semaphore *mySem){
	value = v;
	this->mySem = mySem;
	blockedList = new Queue();
}

int KernelSem::wait(int toBlock){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(toBlock == 0){
		if(value <= 0){
			unlock
			return -1;
		}
		else{
			value--;
			unlock
			return 0;
		}
	}
	else {
		if(--value < 0){
			System::running->state = Blocked;
			blockedList->put(System::running);
			dispatch();
			unlock
			return 1;
		}
		else{
			unlock
			return 0;
		}
	}
#endif
}



void KernelSem::signal(){
	if(value++<0){
		PCB *p = blockedList->get();
		if(p == 0) return;
		p->state = Ready;
		Scheduler::put(p);
	}
}

KernelSem::~KernelSem(){
	while(value<0)
		signal();
	delete blockedList;
	blockedList = 0;
}


