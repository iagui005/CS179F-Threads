#include "thread.h"

using namespace std;

class Incrementer : Thread {
  int priority() { return Thread::priority(); }            // high priority
  void action() {
	if (priority() == 2)
	{
		cdbg << Me() <<" is cancelling itself.\n";
		threadGraveyard.thread_cancel();
	} 
	if (priority() == 3)
	{
		cdbg << Me() <<" is cancelling itself.\n";
		threadGraveyard.thread_cancel();
	}
    cdbg << "New incrementer running.\n";
    for(int i= 0; i < 120; ++i) {
      for(int i=0;i<12000000;++i) {}  // delay
      counter.increment();
      cdbg << " Counter : " << counter.show() << endl;
    }
    cdbg << Me() << " done\n";
  }
public:
  Incrementer( string name, int priority ) : Thread(name, priority) {;}
};


// ======= control order of construction of initial threads  ========


// Create and run three concurrent Incrementers for the single 
// global SharableInteger, counter, as a test case.
Incrementer t1( "Incrementer#1", 2);
Incrementer t2( "Incrementer#2", 3);
Incrementer t3( "Incrementer#3", INT_MAX-1);

int main( int argc, char *argv[] ) {
  // shutting down the main thread
  interrupts.set( InterruptSystem::alloff );  // for this thread only
  pause();                           // stops until interrupt arrives
  assert( false );                            // and none ever should
}

