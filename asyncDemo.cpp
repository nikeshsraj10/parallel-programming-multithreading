// future example
#include <iostream> // std::cout
#include <future> // std::async, std::future
#include <chrono> // std::chrono::milliseconds
// a non-optimized way of checking for prime numbers:
bool is_prime(int x) {
	for (int i = 2; i < x; ++i) if (x % i == 0) return false;
	return true;
}
int main()
{
	// call function asynchronously:
	std::future<bool> fut = std::async(is_prime, 444444443);
	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span(100);
	while (fut.wait_for(span) == std::future_status::timeout)
		std::cout << '.' << std::flush;
	bool x = fut.get(); // retrieve return value
	std::cout << "\n444444443 " << (x ? "is" : "is not") << "prime.\n";
	return 0;
}

// packaged_task immediately runs but the difference with async is that it supports deferred mode
// async has 3 different modes (has to be passed as first argument of async call)
/*
1. std::launch::async
2. std::launch::deferred
3. pass nothing, this indicates its "auto"mode and the compiler decides which among 1 or 2 is the best
*/


/*
wait_for returns 3 types of values
1. future_status::ready -> future object's value is available
2. future_status::timeout -> value not available even after timeout as occurred
3. future_status::deferred -> indicates that the future is in deferred mode
*/