#include <algorithm>
#include "scan.h"

using namespace std;

int *A2;
int *B;
int *F;
int *e1;
int *e2;


void qsort_seq(int *A, int start, int end) {
    if (start >= end - 1) return;
    int pivot = A[start];


    for (int i = start; i < end; i++) A2[i] = A[i];


    for (int i = start; i < end; i++) {
        if (A2[i] < pivot) F[i] = 1; else F[i] = 0;
    }

    scan_seq(F + start, B + start, e1 + start, e2 + start, end - start);


    for (int i = start + 1; i < end; i++) {
        if (F[i]) A[start + B[i] - 1] = A2[i];
    }


    int x = B[end - 1];
    A[start + x] = pivot;


    for (int i = start + 1; i < end; i++) {
        if (A2[i] >= pivot) F[i] = 1; else F[i] = 0;
    }

    scan_seq(F + start, B + start, e1 + start, e2 + start, end - start);

    for (int i = start + 1; i < end; i++) {
        if (F[i]) A[start + x + B[i]] = A2[i];
    }


    qsort_seq(A, start, start + x);
    qsort_seq(A, start + x + 1, end);
}

void qsort_parallel(int *A, int start, int end, int threshold) {
    if (start >= end - 1) return;

	int len = sizeof(A) / sizeof(A[0]);
    if (end - 1 - start < threshold) {
	// this is for part 4.1. a
        //qsort_seq(A, start, end);
	// this is for part 4.1 b
	sort(A, A + len);
    } else {
	
/*
	choosing different pivots:
	u: start 
	v: end
	w: mid
	x: median of three (start, end, mid)
*/
	int u = int(len/4);
	int v = int((3*len)/4);
	int mid = start + (end - start)/2;
	int med3 = max(min(start, end), min(max(start, end), mid)); 
	//https://stackoverflow.com/questions/23392321/most-efficient-way-to-find-median-of-three-integers


        int pivot = A[mid];

        
        cilk_for (int i = start; i < end; i++) A2[i] = A[i];

        cilk_for (int i = start; i < end; i++) {
            if (A2[i] < pivot) F[i] = 1; else F[i] = 0;
        }
        scan_parallel(F + start, B + start, e1 + start, e2 + start, end - start);

        cilk_for (int i = start + 1; i < end; i++) {
            if (F[i]) A[start + B[i] - 1] = A2[i];
        }

        int x = B[end - 1];
        A[start + x] = pivot;

        cilk_for (int i = start + 1; i < end; i++) {
            if (A2[i] >= pivot) F[i] = 1; else F[i] = 0;
        }
        scan_parallel(F + start, B + start, e1 + start, e2 + start, end - start);

        cilk_for (int i = start + 1; i < end; i++) {
            if (F[i]) A[start + x + B[i]] = A2[i];
        }

        cilk_spawn
        qsort_parallel(A, start, start + x, threshold);
        qsort_parallel(A, start + x + 1, end, threshold);
        cilk_sync;
    }
}

