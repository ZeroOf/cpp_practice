
#include "EventfdThread.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
 
int test0(void)
{
	net::Eventfd efd([](){
		::srand(clock());
		int number = ::rand() % 100;
		cout << ">>> number = " << number << endl;
	});

	net::Thread thread(std::bind(&net::Eventfd::Start, &efd));
    thread.Start();

	::sleep(30);
    efd.Stop();
    thread.Join();
	return 0;
}

void test1(void)
{
	net::EventfdThread efd([](){
		::srand(clock());
		int number = ::rand() % 100;
		cout << ">>> number = " << number << endl;
	});

	efd.start();
	int cnt = 10;
	while(cnt--){
		efd.wakeup();
		sleep(1);
	}

	efd.stop();
}

int main(void)
{
	test1();
	return 0;
}
