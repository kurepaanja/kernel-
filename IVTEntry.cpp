

#include "IVTEntry.h"
#include "system.h"
#include <dos.h>
#include "kernelev.h"

IVTEntry* IVTEntry::IVT[256];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newInt){
	myEvent = 0;
	oldInt = 0;
	this->ivtNo = ivtNo;

#ifndef BCC_BLOCK_IGNORE
	lock
	oldInt = getvect(ivtNo);
	setvect(ivtNo, newInt);
	IVTEntry::IVT[ivtNo] = this;
	unlock
#endif
}

IVTEntry::~IVTEntry(){
#ifndef BCC_BLOCK_IGNORE
	lock
	setvect(ivtNo,oldInt);
	IVTEntry::IVT[ivtNo] = 0;
	myEvent = 0;
	unlock
#endif
}

void IVTEntry::callOld(){
	if(oldInt)
		oldInt();
}

void IVTEntry::signal(){
	if(myEvent)
		myEvent->signal();
}
