//+= or ++
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
using namespace std;

int main() {
	// Increment opertion using atomic
	// Can also do multiply and other operations by using this method
	atomic<int> a{ 0 };
	int z0 = a;
	while(!a.compare_exchange_strong(z0, z0 + 1)){
		cout << a << endl;
		cout << "Inside loop" << endl;
	}

	cout << a << endl; // 1 (Increment a)

	z0 = a;
	while (!a.compare_exchange_strong(z0, z0 * 2)) {
		cout << a << endl;
		cout << "Inside loop" << endl;
	}
    // Difference btw a.compare_exchange_weak and strong is that weak may spuriously return false
    // Hardware to implent ce_weak is easier compared to ce_strong, infact very few hardwares supports ce_strong
    
	cout << a << endl; // 2 (Double the value of a)
	// More atomic special opertions
	std::atomic<int> x;
	int y = 1;
	cout << x << endl; //0
	cout << y << endl; /// 1
	cout << "before fetch_add" << endl;
	x.fetch_add(y); // x += y
	cout << "After fetch_add" << endl;
	cout << x << endl; // 1
	cout << y << endl; // 1
	int z = x.fetch_add(y); // z = (x += y) - y and x += y;
	cout << "After fetch_add && assigment to z" << endl;
	cout << z << endl; // 1
	cout << x << endl; // 2
	// There are more methods similar to this such as
	// fetch_sub, fetch_or, fetch_and, fetch_xor
	return 0;
}
