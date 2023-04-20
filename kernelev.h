
#ifndef KERNELEV_H_
#define KERNELEV_H_

typedef unsigned char IVTNo;

class Event;
class PCB;

class KernelEv{
public:

	KernelEv(IVTNo ivtNo, Event *event);
	~KernelEv();

	void wait();
	void signal();

private:

	Event *event;
	int blocked;
	IVTNo ivtNo;
	PCB *pcb;
	int validEntry;
};



#endif /* KERNELEV_H_ */
