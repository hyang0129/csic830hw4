#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<vector>
#include<iostream>
using namespace std;
#include<map>
#include<cmath>





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

	fclose(fin);
	fclose(fout);

	return 0;
}

