#include "thread.h"
#include "myshell.h"
using namespace std;
/*
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
*/

// ======= control order of construction of initial threads  ========


// Create and run three concurrent Incrementers for the single 
// global SharableInteger, counter, as a test case.
/*
class ShellThread : Thread {
  public:
  //ShellThread ()
  void action (){
    thread_run (vector<string>tok);
  }
  private:
};
* 
*/ 
/// shell thread
class ShellThread : Thread {
  public:
  ShellThread (vector<string>tok)
  {
	  Thread("shell_thread", 10, tok);
  }
  void action (vector<string>tok){
    thread_run (tok);
  }
  private:
};
int main( int argc, char *argv[] ) {
  while ( ! cin.eof() ) {
    cout << "? " ;                                         // prompt.
	//testCompleteMe(); 
	// testCompleteMe(); 
    string temp = "";
    getline( cin, temp );
    cout.flush();
    if ( temp == "exit" ) break;                             // exit.

    stringstream ss(temp);      // split temp at white spaces into v.
    while ( ss ) {
      vector<string> v;
      string s;
      while ( ss >> s ) {
        v.push_back(s);
        if ( s == "&" || s == ";" ) break;    
      }
     // thread t(do_work);
      int status = doit( v );           // FIX make status available.
      //if ( errno ) cerr << "myshell: " << strerror(errno) << endl;
    } 

  }
  cout << "exit" << endl;
  return 0;                                                  // ex
}
