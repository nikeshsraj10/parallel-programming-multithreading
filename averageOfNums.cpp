#include <iostream>
#include <thread>
#include <vector>
using namespace std;


void average(vector<vector<int>>& A, vector<vector<int>>& B, int n, int r1, int r2, int c1, int c2) {
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			int N, E, S, W;
			N = (i - 1 >= 0)? A[i - 1][j] : 0;
			E = (j + 1 <= n - 1) ? A[i][j + 1] : 0;
			S = (i + 1 <= n - 1) ? A[i + 1][j] : 0;
			W = (j - 1 >= 0) ? A[i][j - 1] : 0;
			B[i][j] = (N + E + S + W) / 4;
		}
	}
}

int main() {
	int n;
	cout << "Enter matrix size" << endl;
	cin >> n;
	vector<vector<int>> A(n, vector<int>(n));

	for (auto &i : A) {
		for (auto &j : i) { j = rand() % 5; }
	}

	vector<vector<int>> B(n, vector<int>(n));
	thread t1{ average, ref(A), ref(B), n, 0, n / 2, 0, n / 2 }; //Using {} is more recent
	thread t2{ average, ref(A), ref(B), n, 0, n / 2,  n / 2+1, n-1 };
	thread t3{ average, ref(A), ref(B), n, n/2+1, n-1, 0, n / 2 };
	thread t4{ average, ref(A), ref(B), n, n/2+1, n-1, n/2+1, n-1 };
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	for (auto i : A) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (auto i : B) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
}