

#ifndef IDLE_H_
#define IDLE_H_
#include "thread.h"
#include "pcb.h"


extern int syncPrintf(const char *format, ...);


class IdleThread: public Thread{
private:
	volatile int work;
public:
	IdleThread():Thread(4096,1){
		work=1;
	}

	void run(){
		syncPrintf("Idle\n");
		while(work==1) dispatch();
	}


};


#endif /* IDLE_H_ */
