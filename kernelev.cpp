
#include "event.h"
#include "kernelev.h"
#include "system.h"
#include "pcb.h"
#include "SCHEDULE.h"
#include "IVTEntry.h"

KernelEv::KernelEv(IVTNo ivtNo, Event *event){
	this->ivtNo = ivtNo;
	this->event = event;
	this->pcb = System::running;
	this->blocked = 0;

	if(IVTEntry::IVT[ivtNo] && IVTEntry::IVT[ivtNo]->myEvent == 0){
		IVTEntry::IVT[ivtNo]->myEvent = this;
		validEntry = 1;
	}
}

void KernelEv::signal(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(validEntry == 0){
		unlock
		return;
	}
	if(blocked == 1){
		blocked = 0;
		pcb->state = Ready;
		//System::running->state = Ready;
		Scheduler::put(pcb);
	}
	unlock
#endif
}

void KernelEv::wait(){
#ifndef BCC_BLOCK_IGNORE
	lock
	if(validEntry == 0 || pcb != System::running){
	   unlock
	   return;
	}
	else {
		blocked = 1;
		System::running->state = Blocked;
		dispatch();
	}
	unlock
#endif
}

KernelEv::~KernelEv(){
	if(blocked == 1)
		signal();
#ifndef BCC_BLOCK_IGNORE
	lock
	if(validEntry == 1){
		validEntry = 0;
		IVTEntry::IVT[ivtNo]->myEvent = 0;
	}
	unlock
#endif
	this->event = 0;
	this->pcb = 0;
}


