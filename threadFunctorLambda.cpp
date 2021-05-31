#include <iostream>
#include <thread> 
#include <chrono>

using namespace std;

bool f1(int a, int b) { return a > b; }

class MyComparator {
public:
	bool operator()(int a, int b) { return a % 2 > b % 2; }

} f3;


int main() {
	MyComparator f2;//f2 is a functor
	cout << f2(100, 201) << endl;//functo
	thread t1(f1, 1000, 2000);
	thread t2(f2, 1000, 2000);
	thread t3([](int a, int b) {return a % 3 > b % 3; }, 1000, 2000);
	this_thread::sleep_for(chrono::milliseconds(100));
	if (t1.joinable()) t1.join();
	t2.join();
	t3.join();

	return 0;
}