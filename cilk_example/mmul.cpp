#include <algorithm>
#include <iostream>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include "get_time.h"

using namespace std;

#define N 5000 
int Z[N][N];
int X[N][N];
int Y[N][N];

void mm_seq(int X[][N], int Y[][N], int Z[][N]) {
    int i, j, k;


    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            //Z[i][j] = 0;
            for (k = 0; k < N; k++) {
                Z[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
}

void mm_pr_orig(int X[][N], int Y[][N], int Z[][N]) {
    int temp[N];

    cilk_for(int i = 0; i < N; i++) {
        cilk_for (int j = 0; j < N; j++) {
            //Z[i][j] = 0;
            cilk_for (int k = 0; k < N; k++){
                temp[k] = X[i][k] * Y[k][j];
        	}
	}
    }
}

void mm_pr_v1(int X[][N], int Y[][N], int Z[][N]) {
    cilk_for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            cilk_for (int j = 0; j < N; j++) {
                //Z[i][j] = 0;
                Z[i][j] = X[i][k] * Y[k][j];
            }
        }
    }
}

void mm_pr_v2(int X[][N], int Y[][N], int Z[][N]) {
    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            cilk_for (int j = 0; j < N; j++) {
              //  Z[i][j] = 0;
                Z[i][j] = X[i][k] * Y[k][j];
            }
        }
    }
}

void mm_pr_v3(int X[][N], int Y[][N], int Z[][N]) {
    cilk_for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            for (int j = 0; j < N; j++) {
                //Z[i][j] = 0;
                Z[i][j] = X[i][k] * Y[k][j];
            }
        }
    }
}

//void mm_dc(int X[][N], int Y[][N], int Z[][N]) {
//	
//}




void printMatrix(int arr[][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << arr[i][j] << " \n"[j == N - 1];

}

int main(int argc, char **argv) {

    for (auto &row : X) {
        for (auto &col : row) {
            col = rand() % N + 1;
        }
    }

    for (auto &row : Y) {
        for (auto &col : row) {
            col = rand() % N + 1;
        }
    }
/*
    cout << "seq=[";   
    for (char j = 'a'; j < 'g'; j++) {
        timer t;
        t.start();
        mm_seq(X, Y, Z);
        t.stop();
        cout << t.get_total() << ", ";
    }
    cout << "]" << endl;
*/
    cout << "pr=[";
    for (char j = 'a'; j < 'g'; j++) {
        timer t;
        t.start();
        mm_pr_orig(X, Y, Z);
        t.stop();
        cout << t.get_total() << ", ";
    }
    cout << "]" << endl;
/*
    cout << "prv1=[";
    for (char j = 'a'; j < 'g'; j++) {
        timer t;
        t.start();
        mm_pr_v1(X, Y, Z);
        t.stop();
        cout << t.get_total() << ", ";
    }
    cout << "]" << endl;

    cout << "prv2=[";
    for (char j = 'a'; j < 'g'; j++) {
        timer t;
        t.start();
        mm_pr_v2(X, Y, Z);
        t.stop();
        cout << t.get_total() << ", ";
    }
    cout << "]" << endl;

    cout << "prv3=[";
    for (char j = 'a'; j < 'g'; j++) {
        timer t;
        t.start();
        mm_pr_v3(X, Y, Z);
        t.stop();
        cout << t.get_total() << ", ";
    }
    cout << "]" << endl;
*/
    return 0;
}

