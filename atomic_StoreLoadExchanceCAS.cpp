//+= or ++
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
using namespace std;

int main() {
	atomic<int> x{ 10 };//+= will also be atomic
	cout << x << endl; //10
	int y = x.load();
	cout << y << endl; //10
	y += 10;
	x.store(y);
	cout << "After Store" << endl;
	cout << x << endl; //20
	cout << y << endl; //20
	y = 100;
	int z = x.exchange(y);
	cout << "y = 100 \nAfter Exchange. . ." << endl;
	cout << x << endl; //100
	cout << y << endl; //100
	cout << z << endl; //20

	bool success = x.compare_exchange_strong(y, z);
	/*
		if x == y, make x = z and return true
		else y = x and return false
	*/
	cout << "After compare_exchange_strong" << endl;
	cout << x << endl; // 20
	cout << y << endl; // 100
	cout << z << endl; // 20
	cout << success << endl; // 1

	/*
		atomic<int> z{ 0 };
		int z0 = z;
		while(!z.compare_exchange_strong(z0, z0 + 1))
	*/
	return 0;
}
