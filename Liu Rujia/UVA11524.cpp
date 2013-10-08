#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
double r, m1, n1, m2, n2, m3, n3;
int main() {
	int i, j, cas;
	scanf("%d", &cas);
	while(cas--) {
		cin >> r >> m1 >> n1 >> m2 >> n2 >> m3 >> n3;
		double a = n1/m1+1, b = 1+m3/n3, c = n1/m1+(n1*n2)/(m1*m2);
		double p = (a+b+c)/2;
		double x = (a+b+c)*r*0.5/sqrt(p*(p-a)*(p-b)*(p-c));
		a *= x; b *= x; c *= x; p *= x;
		printf("%.4f\n", sqrt(p*(p-a)*(p-b)*(p-c)));
	}
	return 0;
}