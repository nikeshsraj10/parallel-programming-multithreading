#include <iostream>
#include <thread>
#include <vector>
#include <atomic> // Tool of lock-free programming
#include <mutex>
using namespace std;
mutex m1;

void Sumup(atomic<int>& Sum, vector<int>& myVector, int Start, int End) {
	for (int i = Start; i <= End; ++i) {
		//Sum = Sum+ myVector[i];// + is not atomic
		Sum += myVector[i];//+=  operator is now atomic
	}
	cout << Sum << endl;
}


void sumup(int& sum, vector<int>& myVector, int Start, int End) {
	for (int i = Start; i <= End; ++i) {
		//Sum = Sum+ myVector[i];
		// Here value of sum before operation can be accessed by multiple threads
		// sum is thread is not safe and therefore the value calculated may be incorrect
		sum += myVector[i];
	}
	cout << sum << endl;
}
void sumup1(int& sum, vector<int>& myVector, int Start, int End) {
	for (int i = Start; i <= End; ++i) {
		//Sum = Sum+ myVector[i];
		lock_guard<mutex> Lock(m1);
		// locking the thread and taking control of m1 here makes sure that
		// no two threads are accessing sum variable at a time
		sum += myVector[i];
	}
	cout << sum << endl;
}


int main() {
	int sum{ 0 };
	vector<int> myVector;
	for (int i = 0; i < 40000; ++i) {
		myVector.emplace_back(rand() % 100);
	}
	for (int i = 0; i < 40000; ++i) {
		sum += myVector[i];
	}
	cout << "sequential sum = " << sum << endl;
	//Calculating sum with sumup function will not be the same as sum calculated sequentially
	// This is because, ref(sum) is not protected by any lock and hence 
	//multiple threads can have same value before their operation
	// This is the kind of scenario where atomic will be useful
	// Atomic provides synchronization control without using locks
	sum = 0;
	thread T[4];
	T[0] = thread(sumup, ref(sum), ref(myVector), 0, 9999);
	T[1] = thread(sumup, ref(sum), ref(myVector), 10000, 19999);
	T[2] = thread(sumup, ref(sum), ref(myVector), 20000, 29999);
	T[3] = thread(sumup, ref(sum), ref(myVector), 30000, 39999);

	for (int i = 0; i < 4; ++i) T[i].join();


	cout << "sum = " << sum << endl;
	cout << "*****************" << endl;
	sum = 0;
	// sumup1 function uses a traditional lock to over come error described above
	T[0] = thread(sumup1, ref(sum), ref(myVector), 0, 9999);
	T[1] = thread(sumup1, ref(sum), ref(myVector), 10000, 19999);
	T[2] = thread(sumup1, ref(sum), ref(myVector), 20000, 29999);
	T[3] = thread(sumup1, ref(sum), ref(myVector), 30000, 39999);

	for (int i = 0; i < 4; ++i) T[i].join();


	cout << "sum1 = " << sum << endl;

	atomic<int> Sum{ 0 };//+= will also be atomic

	T[0] = thread(Sumup, ref(Sum), ref(myVector), 0, 9999);
	T[1] = thread(Sumup, ref(Sum), ref(myVector), 10000, 19999);
	T[2] = thread(Sumup, ref(Sum), ref(myVector), 20000, 29999);
	T[3] = thread(Sumup, ref(Sum), ref(myVector), 30000, 39999);

	for (int i = 0; i < 4; ++i) T[i].join();


	cout << "Sum = " << Sum << endl;




	return 0;
}

/*
for increment
loads the value from memory to a register
increments the content of the register
saves the register back to memory.

*/

/*
what types can be made atomic??
--> All trivially copyable type can be made atomic (Primitive variables)

What operations can be done?
-> assigment, ++, +=, |=
*= is not supported on atomic variables
there are some special atomic operations as well, for eg: load, store, exchange
I'll add a code describing their applications

atomicity is hardware dependent.

*/