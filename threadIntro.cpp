//Threaded Programming
#include <iostream>
#include <thread>

using namespace std;

void f1(int i, int k) { for (int j = 0; j < i; j++) cout << j * k; }
void f2(int& i) { i++; }

int main() {
	thread t1(f1, 1000, 7);//t1 starts execution
	thread t2(f1, 1000, 3);
	thread t3(f1, 1000, 5);
	t1.join();//for main thread to pause and wait until t1 completes.
	t2.join();
	t3.detach();//remove any information between main thread and t3
	//All threads require either join or detach.
	//It is dangerous if a thread has neither of them.
	//Once detached, it can no longer be joined

	thread t4;
	t4 = thread(f1, 1000, 8);//t4 starts execution
	t4.join();
	thread T[100];
	for (int i = 0; i < 100; i++) {
		T[i] = thread(f1, i, 11);
	}

	for (int i = 0; i < 100; i++) {
		T[i].join();
	}


	thread t5([](int i) {for (int j = 0; j < i; j++) { cout << j * 1000; }}, 50);
	t5.join();
	int k = 100;
	thread t6(f2, ref(k));//ref for call by reference arguments
	t6.join();

	//Call by reference can easily create trouble to threaded programming.
	//You should be extra carefull in using it.

	return 0;
}