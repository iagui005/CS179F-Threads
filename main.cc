#include "thread.h"

using namespace std;

class Incrementer : Thread {
  int priority() { return Thread::priority(); }            // high priority
  void action() {
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
//current threads pid and ppid
//thread local storage of own pid and ppid
class process_thread : Thread {
  int priority() { return Thread::priority(); }            // high priority
  void action(vector<string> v) {
    exec(v);
    cdbg << Me() << " done\n";
  }
public:
  process_thread( string name, int priority ) : Thread(name, priority) {;}
};

// ======= control order of construction of initial threads  ========


// Create and run three concurrent Incrementers for the single 
// global SharableInteger, counter, as a test case.
Incrementer t1( "Incrementer#1", 3);
Incrementer t2( "Incrementer#2", 2);
Incrementertwo v1( "Incrementertwo#1", 2);
Incrementer t3( "Incrementer#3", 1);

int main( int argc, char *argv[] ) {
  // shutting down the main thread
  interrupts.set( InterruptSystem::alloff );  // for this thread only
  pause();                           // stops until interrupt arrives
  assert( false );                            // and none ever should
}

