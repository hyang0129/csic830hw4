#include <stdio.h>
#include<iostream>
using namespace std;

const long n = 10000019 - 1, N = n + 1;  /* N = 1019 -- prime     */
const long alpha = 68093;            /* generator             */
const long beta = 836856;             /* 2^{10} = 1024 = 5 (N) */

void new_xab(long& x, long& a, long& b) {
    switch (x % 3) {
    case 0: x = x * x % N;  a = a * 2 % n;  b = b * 2 % n;  break;
    case 1: x = x * alpha % N;  a = (a + 1) % n;                  break;
    case 2: x = x * beta % N;                  b = (b + 1) % n;  break;
    }
}

long main(void) {
    long x = 1, a = 0, b = 0;
    long X = x, A = a, B = b;
    for (long i = 1; i < n; ++i) {
        new_xab(x, a, b);
        new_xab(X, A, B);
        new_xab(X, A, B);
        prlongf("%3d  %4d %3d %3d  %4d %3d %3d\n", i, x, a, b, X, A, B);
        if (x == X) break;



    }
    cout << ((a - A) % n) / (B - b);

    return 0;
}