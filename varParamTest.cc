#include <thread>
#include <iostream>
#include <cstdarg>
#include <vector>
using namespace std;


template <class... Args>
void printSum (int x, int y)
{
	cerr << x+y << "\n";
}

template < typename... Args>
void testThread (Args&&... args)
{
	thread t1(printSum, args...);
	t1.join();
	
	/*
	va_list args;
	va_start(args, fn);
	vector<T> argVect;
	while (args)
	{
		argVect.push_back(va_arg(args, T));
		
	}
	va_end(args);
	switch(argVect.size())
	{
		case 1:
			cerr << "1 Argument\n";
			thread test(fn, argVect[0]);
			break;
		case 2:
			cerr <<"2 Arguments\n";
			thread test2(fn, argVect[0], argVect[1]);
			break;
		default:
			cerr << "wat\n";
			break;
	}
	* */
}

int main()
{
	int args[2] = {1,1};
	testThread(1, 1);
	return 0;
}
