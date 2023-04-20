
#include "krnlsem.h"
#include "semaphor.h"
#include "system.h"

Semaphore::Semaphore(int init){
	myImpl = new KernelSem(init,this);
}

Semaphore::~Semaphore(){
	lockThread
	delete myImpl;
	unlockThread
	myImpl = 0;
}

int Semaphore::val() const{
	return myImpl->val();
}

int Semaphore::wait(int toBlock){
	return myImpl->wait(toBlock);
}

void Semaphore::signal(){
	myImpl->signal();
}
