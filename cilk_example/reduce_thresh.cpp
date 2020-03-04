#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"
using namespace std;

int reduce_thresh(int* A, int n, int thresh) {
        if (n < thresh) {
            int ret = 0;
            for (int i = 0; i < n; i++) ret += A[i];
            return ret;
        }
        int L, R;
        L = cilk_spawn reduce_thresh(A, n/2, thresh);
        R = reduce_thresh(A+n/2, n-n/2, thresh);
        cilk_sync;
        return L+R;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Usage: ./reduce [num_elements]" << endl;
		return 0;
	}
	int n = atoi(argv[1]);
	int* A = new int[n];
	cilk_for (int i = 0; i < n; i++) A[i] = i;
	//timer t; t.start();
	cout << "[";
	for(int j = 100; j <= 10100; j += 500) {
		timer t; t.start();
		int x = reduce_thresh(A, n, j);
		t.stop();
		cout << t.get_total() << "," << endl;
		//cout << "time: " << t.get_total() << "\t" << j <<  endl;
	        //cout << n << endl;//"\t--\t" << x << "\t--\t" <<j << endl;
	}
	cout << "]" << endl;
	cout << " " << endl;
	//int x = reduce_thresh(A, n);
	//t.stop();
	//cout << "time: " << t.get_total() << endl;
	//cout << n << "\t--\t" << x << "\t--\t" << thresh << endl;
	//cout << x << endl;
	
	return 0;
}
