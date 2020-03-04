using namespace std;
#include <math.h>

void scan_opt(int* In, int* Out, int* B, int* C, int n) {
	if (n==0) return;
	if (n == 1) {
		Out[0] = In[0];
		return;
	}
	/* 
 	* attempt 1 - could not get the right numbers to work
 	* sequential inclusive prefix scan
 	* it did speed it up though
 	*
 	* cilk_for (int i = 0; i<n; i++) {
 	* 	Out[i] = Out[i-1] + In[i];
 	* }
 	*/
	
	

	/*
 	* attempt 2 - could not get this to work at all
 	* tried to base off of Hillis and Steele algorithm but
 	* only first few numbers calculate
 	*/
	for (int i = 0; i < (log(n-1));i++) {
		cilk_for(int j = pow(2.0, i); j<n-1; j++){
			Out[i] = In[j] + In[j-int(pow(2.0, i))];
		}	
	}
//	*/

        scan_opt(B, C, B+n/2, C+n/2, n/2);
        Out[0] = In[0];


}
