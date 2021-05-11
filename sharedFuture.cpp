// promise example
#include <iostream> // std::cout
#include <functional> // std::ref
#include <thread> // std::thread
#include <future> // std::promise, std::future
using namespace std;

int getVal(){
	return 10;
}
int main()
{
	future<int> fut = async(getVal);
	shared_future<int> shfut = fut.share();
	int i = 0;
	while (i < 5) {
		cout << shfut.get() << endl;
		i++;
	}
	// Below line will raise an exception as the future is already assigned to shared_future
	//cout << fut.get() << endl;
	return 0;
}
