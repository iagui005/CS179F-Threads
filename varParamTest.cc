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

void printXString(string s, int y)
{
	for (int i = 0; i < y; ++i)
	{
		cout << s <<"\n";
	}
	
}
template < typename Fn, typename... Args>
void testThread (Fn fn, Args... args)
{
	thread t1(fn, args...);
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
	testThread(printSum,1, 1);
	testThread(printXString, "Hello World!", 5);
	return 0;
}
