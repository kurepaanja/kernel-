

#include "system.h"
#include "SCHEDULE.H"

pointI System::Old60=0;
pointI System::OldRoutine=0;
int System::context_switch_on_demand=0;
int System::counter=0;
IdleThread* System::idle=0;
PCB* System::running=0;
Queue* System::AllThreads=0;
PCB* System::mainThread=0;


unsigned volatile tsp=0;
unsigned volatile tss=0;
unsigned volatile tbp=0;


extern int syncPrintf(const char *format, ...);

void interrupt System::timer(...){
	//syncPrintf("TIMER\n");
	//syncPrintf("%d\n",System::context_switch_on_demand);
	if(System::context_switch_on_demand==0){
		//syncPrintf("tik\n");
		if(!System::running->not_time_dependent)System::counter--;
		tick();
	}
	if(System::counter==0 || System::context_switch_on_demand==1){
		//syncPrintf("1\n");

#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp,sp;
			mov tss,ss;
			mov tbp, bp;
		}
#endif
		//syncPrintf("2\n");

		System::running->sp=tsp;
		System::running->ss=tss;
		System::running->bp=tbp;



		//syncPrintf("%d blok\n",System::running->blocked);
		//ako je nit blokirana ili idle nit ne stavljaj je u scheduler
		if(System::running->getID()!=System::idle->getId() && System::running->blocked!=1 && System::running->finished!=1){
			if(System::running->start==1){
				Scheduler::put(System::running);
			}
		}

		System::running=Scheduler::get();

		//syncPrintf("3\n");
		if(System::running->getID()==0){
			//syncPrintf("PRAZAN\n");
			System::running=System::idle->myPCB;
		}

		//syncPrintf("%d nit koja je uzeta\n",System::running->getID());
		tsp=System::running->sp;
		tss=System::running->ss;
		tbp=System::running->bp;

		System::counter=System::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
		asm{
			mov sp,tsp;
			mov ss,tss;
			mov bp,tbp;
		}
#endif
		System::context_switch_on_demand=0;
	}
	else System::context_switch_on_demand=1;
}

void System::initiation(){
	syncPrintf("INICIJALIZACIJA\n");

#ifndef BCC_BLOCK_IGNORE
	System::OldRoutine=getvect(0x08);
	setvect(0x08,System::timer);
	System::Old60=getvect(0x60);
	setvect(0x60,System::OldRoutine);
#endif
	System::mainThread=new PCB(0,2,0);
	System::mainThread->start=1;
	System::running=System::mainThread;
	System::AllThreads=new Queue();
	System::idle=new IdleThread();

}

void System::restore(){
	syncPrintf("RESTAURACIJA\n");
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08,System::OldRoutine);
	setvect(0x60,System::Old60);
#endif
	delete AllThreads;
	delete idle;
}


