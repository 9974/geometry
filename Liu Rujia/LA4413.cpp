#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;
struct point {
	double x, y;
	point(double x=0, double y=0) : x(x), y(y) {}
	point operator-(const point &t) const {
		return point(x-t.x, y-t.y);
	}
	point operator+(const point &t) const {
		return point(x+t.x, y+t.y);
	}
	point operator*(const double &t) const {
		return point(x*t, y*t);
	}
	void in() {
		cin >> x >> y;
	}
}P,Q,R,A,B,C;

double m1, m2, m3, m4, m5, m6, k1, k2, t, x, y;
int main() {
	int i, j, cas;
	scanf("%d", &cas);
	while(cas--) {
		P.in(), Q.in(), R.in();
		cin >> m1 >> m2 >> m3 >> m4 >> m5 >> m6;
		x = m5*(m1+m2), y = m6*m2, k1 = x/(x+y);
		x = m3*m1, y = m4*(m1+m2), k2 = x/(x+y);
		t = k1/(1-k1-k2), A = R+(R-P)*t;

		x = (m3+m4)*m1, y = m2*m4, k1 = x/(x+y);
		x = m3*m5, y = (m3+m4)*m6, k2 = x/(x+y);
		t = k1/(1-k1-k2), B = P+(P-Q)*t;

		x = (m5+m6)*m3, y = m4*m6, k1 = x/(x+y);
		x = m1*m5, y = (m5+m6)*m2, k2 = x/(x+y);
		t = k1/(1-k1-k2), C = Q+(Q-R)*t;
		printf("%.8f %.8f %.8f %.8f %.8f %.8f\n", A.x, A.y, B.x, B.y, C.x, C.y);
	}
	return 0;
}