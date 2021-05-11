//Centralized Version
//Example of a blocking queue by C-Y (Roger) Chen, Syracuse Univesity
//Note that I did not protect cout.
//For meaningful applications, the values
//will be stored somewhere, rather 
//than directly being printed to console.
#include <iostream>
#include <queue>  //deque combines the functionality of vector and list.  Supports index based random access
		  //and pop and push at both ends
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;
mutex m2;

class blocking_queue {
private:
	mutex m1;
	condition_variable cv1, cv2;
	queue<int> Queue;

public:
	void push(int k) {
		unique_lock<mutex> ulock(m1);
		while (Queue.size() == 5) cv1.wait(ulock);
		Queue.push(k);
		cv2.notify_one();
	}
	int pop() {
		{
			unique_lock<mutex> ulock(m1);
			while (Queue.empty()) cv2.wait(ulock);
			int temp;
			temp = Queue.front();
			Queue.pop();
			cv1.notify_one();
			return temp;
		}
	}
};

void putData(blocking_queue& b_queue, int id, int k) {

	b_queue.push(k);
	lock_guard<mutex> lg1(m2);
	cout << "putter " << id << " push value " << k << " to the blocking_queue" << endl;
}

void getData(blocking_queue& b_queue, int id) {
	int Pop = b_queue.pop();
	lock_guard<mutex> lg1(m2);
	cout << "getter " << id << " pop value " << Pop << endl;

}

int main() {

	blocking_queue b_queue;
	thread putter[10];
	thread getter[10];

	for (int i = 0; i < 10; i++) {
		getter[i] = thread(getData, ref(b_queue), i);
		putter[i] = thread(putData, ref(b_queue), i, 10 * i);
	}

	for (int i = 0; i < 10; i++) {

		putter[i].join();
		getter[i].join();
	}

	return 0;

}