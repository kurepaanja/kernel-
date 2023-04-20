
#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <iostream.h>
#include <dos.h>
#include "pcb.h"
#include "idle.h"
#include "queue.h"
#include "thread.h"

#define lock{asm {pushf; cli;}}
#define unlock asm popf;
typedef void interrupt(*pointI)(...);

class Queue;
class PCB;
class IdleThread;


class System {
public:
	static PCB* running;
	static PCB *mainPCB;
	static Queue *allThreads;
	static IdleThread* idle;

	static volatile int DispatchCalled;
	static volatile int ThreadLocked;
	static volatile int counter;

	static const int mainID;
	static const int idleID;

	static void init();
	static void restore();
	static void interrupt timer(...);

	static pointI oldInt;
	static pointI int60h;

};



extern void tick();

extern int userMain(int, char *[]);

class MainThread : public Thread{
public:
	MainThread(int argc, char **argv) : Thread() {
		this->argc = argc;
		this->argv = argv;
		ret = 0;
	}

	virtual ~MainThread() { waitToComplete(); }

	int getRet() { return ret; }

	virtual void run() {
		ret = userMain(argc,argv);
	}


private:
	int argc;
	char **argv;
	int ret;
};

#endif /* SYSTEM_H_ */