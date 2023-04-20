
#include "pcb.h"
#include "IOSTREAM.H"
#include "dos.h"
#include "SCHEDULE.H"


int PCB::lastID=0;
extern int syncPrintf(const char *format, ...);


PCB::PCB(StackSize stackSize, unsigned timeSlice, Thread* thread){
	bp=0;
	sp=0;
	ss=0;
	myThread=thread;
	this->stack=0;
	id=++lastID;
	this->timeSlice=timeSlice;
	this->stackSize=stackSize;
	start=0;
	finished=0;
	blocked=0;
	if(this->timeSlice==0) not_time_dependent=1;
	BlockedList=new Queue();
	if(stackSize!=0)	this->initialize();
	//if(stackSize==0) syncPrintf("main napravljen'");
	System::AllThreads->add(this);

}

void PCB::initialize(){
	if (stackSize > 65536)
		stackSize = 65536;

	stackSize/=sizeof(unsigned);
	this->stack=new unsigned[stackSize];
	stack[stackSize-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2]=FP_SEG(PCB::wrapped);
	stack[stackSize-3]=FP_OFF(PCB::wrapped);

	ss=FP_SEG(stack+stackSize-12);
	sp=FP_OFF(stack+stackSize-12);
	bp=sp;
#endif
	//syncPrintf("PCB napravljen\n");

}

PCB::~PCB(){
	lock

	System::AllThreads->remove(this);
	if(stack!=0) delete[] stack;
	delete BlockedList;
	stack=0;
	BlockedList=0;
	unlock
}

void PCB::startPCB(){
	lock
	start=1;
	if(this->getID()!=System::idle->getId()){
		Scheduler::put(this);
		//syncPrintf("PCB u Scheduler\n");
	}
	unlock
}

void PCB::wrapped(){
	lock
	System::running->myThread->run();
	System::running->finished=1;
	System::running->finishedPCB();
	//syncPrintf("OVDE\n");
	unlock
	dispatch();
}

void PCB::finishedPCB(){ //sta ako ceka na vise niti onda se ne odblokira odmah, mozda da se doda dodatan int koji broji velicinu niti koji su8 ga blokirali
	syncPrintf("%d nit gotova\n", getID());
	if(BlockedList->isEmpty()==1) return;
	lock

	while(BlockedList->isEmpty()!=1){

		PCB* help=BlockedList->get();
		//syncPrintf("%d nit dodata\n",help->getID());
		help->blocked=0;
		Scheduler::put(help);
	}
	unlock
}

void PCB::waitToCompletePCB(){
	if(this==System::running||this->finished==1 || this->start==0){
		return;
	}
	lock
	//syncPrintf("%d nit ceka %d\n",System::running->getID(),this->id);
	System::running->blocked=1;
	this->BlockedList->add(System::running);
	unlock
	dispatch();

}


