// packaged_task example
//Packaged task
//A packaged_task wraps a callable element and allows its result to be retrieved asynchronously.
//It is similar to std::function, but transferring its result automatically to a future object.

#include <iostream> // std::cout
#include <future> // std::packaged_task, std::future
#include <chrono> // std::chrono::seconds
#include <thread> // std::thread, std::this_thread::sleep_for
#include <functional>
class Functor_Class {
public:
	int operator()(int a, int b) {
		return pow(a, b);
	}
} f1;

void task_functor() {
	std::packaged_task<int(int, int)> task(f1);
	std::future<int> result = task.get_future();
	task(2, 13);
	std::cout << "task_functor:\t" << result.get() << '\n';
}

// unique function to avoid disambiguating the std::pow overload set 
int f(int x, int y) { return std::pow(x, y); }

void task_lambda() {
	std::packaged_task<int(int, int)> task([](int a, int b) { return std::pow(a, b); });
	std::future<int> result = task.get_future();
	task(2, 9);
	std::cout << "task_lambda:\t" << result.get() << '\n';
}

void task_bind() {
	std::packaged_task<int()> task(std::bind(f, 2, 11));
	std::future<int> result = task.get_future();
	task();
	std::cout << "task_bind:\t" << result.get() << '\n';
}

void task_thread() {
	std::packaged_task<int(int, int)> task(f);
	std::future<int> result = task.get_future();
	std::thread task_td(std::move(task), 2, 10);
	task_td.join(); std::cout << "task_thread:\t" << result.get() << '\n';
}

// count down taking a second for each value:
int countdown(int from, int to) {
	for (int i = from; i != to; --i) {
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Lift off!\n";
	return from - to;
}

int main()
{
	// Executing the calls that shows 4 different ways of implementing a packaged_task
	task_functor();
	task_lambda(); 
	task_bind(); 
	task_thread();
	// Example of package task using a countdown
	std::packaged_task<int(int, int)> tsk(countdown); // set up packaged_task
	//packaged_task behaves similarly to the keyword function discussed earlier
	std::future<int> ret = tsk.get_future(); // get future
	std::thread th(std::move(tsk), 10, 0); // spawn thread to count down from 10 to 0
	// ...
	int value = ret.get(); // wait for the task to finish and get result
	std::cout << "The countdown lasted for " << value << " seconds.\n";
	th.join();
	return 0;
}