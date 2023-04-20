

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;

class KernelEv;

class IVTEntry{
public:

	IVTEntry(IVTNo ivtNo, pInterrupt newInt);
	~IVTEntry();

	void callOld();
	void signal();

	friend class KernelEv;

private:
	pInterrupt oldInt;
	IVTNo ivtNo;
	KernelEv *myEvent;

	static IVTEntry *IVT[256];
};



#endif /* IVTENTRY_H_ */
