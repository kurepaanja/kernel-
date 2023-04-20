

#include "event.h"
#include "kernelev.h"
#include "system.h"

Event::Event(IVTNo ivtNo){
	lockThread
	myImpl = new KernelEv(ivtNo, this);
	unlockThread
}

Event::~Event(){
	lockThread
	delete myImpl;
	unlockThread
	myImpl = 0;
}

void Event::signal(){
	myImpl->signal();
}

void Event::wait(){
	myImpl->wait();
}






