#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;
#include<map>
#include<cmath>
#include <unordered_map>
#include <algorithm>
#include <math.h> 


long long solve(long long a, long long b, long long m) {
    a %= m, b %= m;
    long long k = 1, add = 0, g;
    while ((g = __gcd(a, m)) > 1) {
        if (b == k)
            return add;
        if (b % g)
            return -1;
        b /= g, m /= g, ++add;
        k = (k * 1ll * a / g) % m;
    }

    long long n = sqrt(m) + 1;
    long long an = 1;
    for (int i = 0; i < n; ++i)
        an = (an * 1ll * a) % m;

    unordered_map<int, int> vals;
    for (int q = 0, cur = b; q <= n; ++q) {
        vals[cur] = q;
        cur = (cur * 1ll * a) % m;
    }

    for (int p = 1, cur = k; p <= n; ++p) {
        cur = (cur * 1ll * an) % m;
        if (vals.count(cur)) {
            long long ans = n * p - vals[cur] + add;
            return ans;
        }
    }
    return -1;
}


int main(int argc,char** argv){
	long long A,B,M;
	FILE* fin = fopen(argv[1],"r");
	FILE* fout = fopen(argv[2],"w");

	if (fscanf(fin, "%lld%lld%lld", &A, &B, &M))
	{}

	long long x = 1;
	for(long long i = 0;i < M;++i){
		if(x == B){
			cout << i << endl;
			fprintf(fout,"%lld\n",i);
			break;
		}else{
			x = x * A % M;
		}
	}

    cout << solve(A, B, M) << endl; 

    //fprintf(fout, "%lld\n", );

	fclose(fin);
	fclose(fout);

	return 0;
}

