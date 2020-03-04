#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <algorithm>
#include <random>
#include <chrono>
#include "get_time.h"
#include "qsort.h"

using namespace std;

inline uint32_t hash32(uint32_t a) {
    a = (a + 0x7ed55d16) + (a << 12);
    a = (a ^ 0xc761c23c) ^ (a >> 19);
    a = (a + 0x165667b1) + (a << 5);
    a = (a + 0xd3a2646c) ^ (a << 9);
    a = (a + 0xfd7046c5) + (a << 3);
    a = (a ^ 0xb55a4f09) ^ (a >> 16);
    if (a < 0) a = -a;

    return a;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        cout << "Usage: ./qsort [num_elements]" << endl;
        return 0;
    }

    int numElements = atoi(argv[1]);
    int *A = new int[numElements];
	

	// original array value creation
    //cilk_for (int i = 0; i < numElements; i++) A[i] = (hash32(i)) % (numElements * 2);



	
	// random distinct array value creation
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
/*
	for (int i = 0; i < numElements; i++) {
	    A[i] = i+1;
    }
    
	// we create integer from 1 to number of elements,
	// then we shuffle them to get distinct random numbers in array	
    shuffle(&A[0], &A[numElements], std::default_random_engine(seed));
*/

	
	// inputs with heavy duplicates
	for (int i = 0; i < numElements; i++) {
		A[i] = (i % (numElements/(numElements/20)))+1;	
	}
	
	shuffle(&A[0], &A[numElements], std::default_random_engine(seed));





    A2 = new int[numElements];
    B = new int[numElements];
    F = new int[numElements];
    e1 = new int[numElements];
    e2 = new int[numElements];

/*	
//for running sequentially
	
	for (char j = 'a'; j< 'j'; j++) {
		cout << j << "=[";
		timer t;
		t.start();
		qsort_seq(A, 0, numElements);
		t.stop();
		cout << t.get_total() << "]" << endl;
	}
*/	
   
 
    for (char j = 'a'; j < 'c'; j++) {
	cout << j << "=[";
        for (int k = 100; k <= 10100; k += 1000) {
            timer t;
            t.start();
	    	qsort_parallel(A, 0, numElements, k);
            t.stop();
            cout << t.get_total() << "," << endl;
        }
        cout << "]" << endl;
        cout << " " << endl;
    }
    return 0;
}
