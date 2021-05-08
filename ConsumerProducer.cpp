#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>

using namespace std;

// Global variables for each thread to access
int seed = rand() % 10;
vector<int> Vec;//max allowed size of Vec is 6.
mutex m1;
condition_variable cv1, cv2;


void consumer(int id) {
    unique_lock<mutex> u1(m1);
    //Will perform the following operations only when Vec.size == 6.
    while (Vec.size() < 6) { cv1.wait(u1); }
    int sum{ 0 }, average;
    for (int i = 0; i < 6; ++i) { sum += Vec[i]; }
    std::cout << "Consumer ID = " << id << "  Average = " << sum / 6 << endl;
    std::this_thread::sleep_for(std::chrono::microseconds(rand() % 1000));
    Vec.clear();
    cv2.notify_one();
}

void producer(int id) {
    unique_lock<mutex> u1(m1);
    //Will perform the following operatoins only when Vec.size < 6.
    while (Vec.size() == 6) { cv2.wait(u1); }
    srand(seed++);
    int numProduced = rand() % 200;
    Vec.push_back(numProduced);
    std::this_thread::sleep_for(std::chrono::microseconds(rand() % 1000));
    std::cout << "Producer ID = " << id << "  Added a value to Vec " << numProduced << endl;
    if (Vec.size() == 6) cv1.notify_one();
    if (Vec.size() != 6) cv2.notify_one();
}

int main()
{
    std::thread consumers[2], producers[12];
    for (int i = 0; i < 12; ++i) {
        producers[i] = std::thread(producer, i + 1);
    }
    for (int i = 0; i < 2; ++i) {
        consumers[i] = std::thread(consumer, i + 1);
    }
    for (int i = 0; i < 12; ++i) {
        producers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        consumers[i].join();
    }
    return 0;
}
