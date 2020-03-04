using namespace std;

void scan_parallel(int *In, int *Out, int *B, int *C, int n) {
    if (n == 0) return;
    if (n == 1) {
        Out[0] = In[0];
        return;
    }
    //cilk_for
    cilk_for (int i = 0; i < n / 2; i++)
        B[i] = In[2 * i] + In[2 * i + 1];

    scan_parallel(B, C, B + n / 2, C + n / 2, n / 2);
    Out[0] = In[0];

    //cilk_for
    cilk_for (int i = 1; i < n; i++) {
        if (i % 2) Out[i] = C[i / 2];
        else Out[i] = C[i / 2 - 1] + In[i];
    }
}

void scan_seq(int *In, int *Out, int *B, int *C, int n) {
    if (n == 0) return;
    if (n == 1) {
        Out[0] = In[0];
        return;
    }

    for (int i = 0; i < n / 2; i++)
        B[i] = In[2 * i] + In[2 * i + 1];

    scan_seq(B, C, B + n / 2, C + n / 2, n / 2);
    Out[0] = In[0];

    for (int i = 1; i < n; i++) {
        if (i % 2) Out[i] = C[i / 2];
        else Out[i] = C[i / 2 - 1] + In[i];
    }
}
