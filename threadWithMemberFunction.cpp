#include <iostream>
#include <thread>
#include <chrono>
using namespace std;


class MyClass {
public:

	int value;
	MyClass() { } //default constructor
	MyClass(int i) : value(i) {} //constructor
	void f1(int& a, int b) {
		value++;
		a++;
		cout << a * b << endl;
	}
};

class MyFunctor {
public:
	int value;
	MyFunctor() {}
	MyFunctor(int i) : value(i) {} 
	void operator() (int& a, int b) {
		value++;
		a++;
		cout << a + b << endl;
	}
};


int main() {
	int x{ 10 }, y{ 20 };
	MyClass m1(100);
	thread t1{ &MyClass::f1, ref(m1), ref(x), y };//&m1 will also work for call (pass) by ref
	//m1 with ref or & will be call (pass) by ref;
	//m1 without ref or & will be call (pass) by value

	//Replaing ref(x) with &ref will cause errors.


	this_thread::sleep_for(chrono::seconds(1));

	cout << "value = " << m1.value << " " << "x = " << x << endl;
	t1.join();

	MyFunctor m2(1000);
	thread t2{ ref(m2), ref(x), y };
	//m2 without ref will give you call (pass) by value
	//m2 with ref will give you call (pass) by ref

	//&m2 will lead to error
	t2.join();
	cout << "value = " << m2.value << " " << "x = " << x << endl;


	MyClass* p1 = new MyClass(500);
	thread t3{ &MyClass::f1, ref(*p1), ref(x), y };
	//p1 and ref(*p1) will both give you call by ref
	//*p1 will give you call by value

	t3.join();
	//detach before child thread completes can lead to unpredictable results. 
	cout << "value = " << p1->value << " " << "x = " << x << endl;

	return 0;
}