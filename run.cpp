

#include "system.h"

extern int syncPrintf(const char *format, ...);

int main(int argc, char *argv[]){

	System::init();

	lockThread
	MainThread *mainThread = (new MainThread(argc,argv));
	unlockThread

	mainThread->start();
	mainThread->waitToComplete();

	int ret = mainThread->getRet();

	delete mainThread;

	System::restore();

    syncPrintf("happy end");

	return ret;
}


