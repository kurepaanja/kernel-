
#include <IOSTREAM.H>
#include "system.h"

extern int syncPrintf(const char *format, ...);


volatile Time ts;

void tick()
{
	syncPrintf("timeSlice=%d\n",ts);
}

class TestThread : public Thread
{
private:
	Time myTimeSlice;
public:

	TestThread(StackSize stackSize, Time timeSlice): Thread(stackSize,timeSlice), myTimeSlice(timeSlice) {};
	~TestThread()
	{
		waitToComplete();
	}
protected:

	void run();

};

void TestThread::run()
{
	for(unsigned i=0;i<320;i++)
	{
		for(unsigned int j=0;j<320;j++)
		{
			//syncPrintf("timeSlice=%d\n",ts);
			ts = myTimeSlice;

		}
	}
}


int userMain(int argc, char** argv)
{
	syncPrintf("Test starts.\n");
	TestThread t1(64,1), t2(4096,32), t3(1024,16), t4(4096,0);
	t1.start();
	t2.start();
	t3.start();
	t4.start();
	t1.waitToComplete();
	t2.waitToComplete();
	t3.waitToComplete();
	t4.waitToComplete();
	syncPrintf("Test ends.\n");
	return 0;
}


int main(int argc, char *argv[]) {

	System::initiation();
	lock
	userMain(argc,argv);
	unlock
	System::restore();
	return 1;
}


