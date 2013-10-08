#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double pi = acos(-1.0);
double c[505];
int n;
double r, ans;
int main() {
	int i, j, k;
	while(~scanf("%d%lf", &n, &r)) {
		if(!n && r == 0) break;
		for(i = 0; i < n; i++) {
			scanf("%lf", &c[i]);
			c[i] = c[i]*pi/180;
		}
		sort(c, c+n);
		ans = 0;
		for(i = 0; i < n; i++)
			for(j = i+1; j < n; j++) {
				k = j-i+1;
				ans += (n-k*2+2)*sin(c[j]-c[i]);
			}
		printf("%.0f\n", r*r*ans/2);
	}
	return 0;
}