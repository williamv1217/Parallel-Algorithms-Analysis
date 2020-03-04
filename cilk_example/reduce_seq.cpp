#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
using namespace std;

int reduce(int* A, int n) {
	if (n == 1) return A[0];
	int L, R;
	L = reduce(A, n/2);
	R = reduce(A+n/2, n-n/2);
	return L+R;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: ./reduce [num_elements]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	int* A = new int[n];
	for (int i = 0; i < n; i++) A[i] = i;
	timer t; t.start();
	int x = reduce(A, n);
	t.stop();
	cout << "time: " << t.get_total() << endl;
	cout << n << "\t--\t" << x << endl;	
	
	return 0;
}
