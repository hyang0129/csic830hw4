#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<vector>

#include<iostream>
using namespace std;
#include<map>
#include<cmath>



int Power(int a, int b, int c)
{
	int buf = 1;
	int jx = 0;
	while (jx < c)
	{
		buf *= a;
		buf %= b;
		jx++;
	}
	return buf;
}
map<int, int> decomposition(int n)
{
	map<int, int> nums;
	for (int i = 2; n > 1; i++)
	{
		while (n % i == 0)
		{
			nums[i]++;
			n /= i;
		}
	}
	return nums;
}

int xModP(int n, int b, int y, int p, int h)
{
	int x = 0;
	int buf;
	map<int, int> r;
	for (int ix = 0; ix < p; ix++)
	{
		buf = Power(b, n, (n - 1) / p * ix);
		r[buf] = ix;
		cout << endl << "r" << p << "," << ix << "=" << buf;
	}
	cout << endl << endl << "x = ";
	for (int i = 0; i < h; i++)
		cout << pow(p, i) << "x" << i << " + ";
	cout << endl << endl;
	for (int ix = 0; ix < h; ix++)
	{
		buf = Power(y, n, (n - 1) / pow(p, ix + 1));
		cout << endl << "r(p,x) = " << buf << endl << endl;
		x += pow(p, ix) * r[buf];
		cout << "x" << " = " << x << endl;
		buf = -r[buf];
		while (buf < 0)
			buf += n - 1;
		buf = Power(b, n, pow(p, ix) * buf);
		y = y * buf;
		y %= n;
		cout << "y" << ix + 1 << " = " << y << endl;
	}
	buf = pow(p, h);
	return x % buf;
}

int ext_euclid(int a, int b, int& x, int& y)
{
	int d;
	if (b == 0)
	{
		d = a;
		x = 1;
		y = 0;
		return d;
	}
	int q, r, x1 = 0, x2 = 1, y1 = 1, y2 = 0;
	while (b > 0)
	{
		q = a / b, r = a - q * b;
		x = x2 - q * x1;
		y = y2 - q * y1;
		a = b;
		b = r;
		x2 = x1;
		x1 = x;
		y2 = y1;
		y1 = y;
	}
	d = a;
	x = x2;
	y = y2;
	return d;
}

int ChiResTheory(vector<int> a, map<int, int> nums, int n)
{

	std::cout.setstate(std::ios_base::failbit);
	int x = 0, M = 1;
	vector<int> b;
	for (auto it = nums.begin(); it != nums.end(); it++)
	{
		b.push_back(pow(it->first, it->second));
	}
	for (int i = 0; i < b.size(); i++)
		M *= b[i];
	int q, z;
	for (int i = 0; i < a.size(); i++)
	{
		ext_euclid(M / b[i], b[i], q, z);
		cout << "BACK element to " << M / b[i] << " is " << q << endl;
		x += a[i] * M / b[i] * q;
		if (x > n - 1)
			x %= (n - 1);
		while (x < 0)
		{
			x += n - 1;
		}
	}

	std::cout.clear();
	return x;
}

int SPH(int n, int b, int y)
{	

	std::cout.setstate(std::ios_base::failbit);

	map<int, int> nums = decomposition(n - 1);
	vector<int> x;
	cout << n - 1 << " = ";
	for (auto it = nums.begin(); it != nums.end(); it++)
		cout << it->first << "^" << it->second << " * ";
	for (auto it = nums.begin(); it != nums.end(); it++)
		x.push_back(xModP(n, b, y, it->first, it->second));
	cout << endl;
	for (int i = 0; i < x.size(); i++)
		cout << x[i] << endl;

	std::cout.clear();
	return ChiResTheory(x, nums, n);
}





int main(int argc,char** argv){
	long long A,B,M;
	FILE* fin = fopen(argv[1],"r");
	FILE* fout = fopen(argv[2],"w");

	if (fscanf(fin, "%lld%lld%lld", &A, &B, &M))
	{
	}


	cout << SPH(A, B, M);

	long long x = 1;
	for(long long i = 0;i < M;++i){
		if(x == B){
			cout << i;
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

