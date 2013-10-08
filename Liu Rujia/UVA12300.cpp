#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
int main() {
	int x1, y1, x2, y2, n;
	while (cin >> x1 >> y1 >> x2 >> y2 >> n) {
		if (!x1 && !y1 && !x2 && !y2 && !n)
			break;
		double len = sqrt(
				double((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
		double rad = 2 * acos(-1.0) / n;
		int m = n / 2;
		double r = sqrt(len * len / 2 / (1 - cos(m * rad)));
		double ans = n * r * r * sin(rad) / 2;
		printf("%.6f\n", ans);
	}
	return 0;
}