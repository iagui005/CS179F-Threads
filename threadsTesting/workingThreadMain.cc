#include "thread.h"
#include <unistd.h>
#include <string.h>
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

/*
//current threads pid and ppid
//thread local storage of own pid and ppid
class process_thread : Thread {
  int priority() { return Thread::priority(); }            // high priority
  void action(vector<string> v) {
    execvp(v);
    cdbg << Me() << " done\n";
  }
public:
  process_thread( string name, int priority ) : Thread(name, priority) {;}
};
*/
// ======= control order of construction of initial threads  ========

class pseudoProcess : Thread {
	vector<string> exec_data;
	int priority() {return Thread::priority(); }
	void action()
	{
		
		char* argv[exec_data.size()+1];
		int i = 0;
		for ( i = 0; i < exec_data.size(); ++i)
		{
			argv[i] = new char ('\0');
			strcpy(argv[i], exec_data[i].c_str());
		}
		argv[i] = 0; // Null terminating argv for execvp
		int pid;
		if ((pid = fork()) < 0) { // Fork
			cerr << "Fork failed.\n";
			exit(1);
		}
		else if (pid == 0) {      // Child    
			if (execvp(argv[0], argv) < 0) {     
				cerr << "Exec failed.\n";
				exit(1);
			}
		}
		else // Parent
		{
			//Delete all the dynamically allocated pointers for this argv
			for (int i = 0 ; i < exec_data.size() ; ++i)
			{
				delete argv[i];
			}
			cerr << Me() << " has executed the command \n";
			//threadGraveyard.thread_cancel(); // cancel parent thread;
		}
	}
	
	public:
		pseudoProcess(string name, int priority, vector<string> v)
		:exec_data(v), Thread(name, priority)
		{}
		
};

// Create and run three concurrent Incrementers for the single 
// global SharableInteger, counter, as a test case.
Incrementer t1( "Incrementer#1", 6);
Incrementer t2( "Incrementer#2", 5);
//Incrementertwo v1( "Incrementertwo#1", 2);
Incrementer t3( "Incrementer#3", 4);

int main( int argc, char *argv[] ) {
  //ls_test.join();
  vector<string> dummy;
	dummy.push_back("ls");
	dummy.push_back("-l");
	dummy.push_back("-r");
	pseudoProcess ls_test( "LsProcess", 3, dummy);

  // shutting down the main thread
  interrupts.set( InterruptSystem::alloff );  // for this thread only
  pause();                           // stops until interrupt arrives
  assert( false );                            // and none ever should
}

