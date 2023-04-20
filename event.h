
#ifndef EVENT_H_
#define EVENT_H_

#include "IVTEntry.h"

typedef unsigned char IVTNo;
class KernelEv;


#define PREPAREENTRY(numEntry, calllOld)\
	void interrupt inter##numEntry(...);\
	IVTEntry newEntry##numEntry(numEntry, inter##numEntry);\
	void interrupt inter##numEntry(...) {\
		if (calllOld)\
			newEntry##numEntry.callOld();\
		newEntry##numEntry.signal();\
	}



class Event {
public:
	Event (IVTNo ivtNo);
	~Event ();

	void wait();

protected:
	friend class KernelEv;
	void signal();

private :
	KernelEv *myImpl;
};



#endif /* EVENT_H_ */
