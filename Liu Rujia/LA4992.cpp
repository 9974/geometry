#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const double eps = 1e-6;
int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x > eps ? 1 : -1;
}
struct point {
	double x, y;
	point(double x = 0, double y = 0) :
			x(x), y(y) {
	}
	point operator+(const point &t) const {
		return point(x + t.x, y + t.y);
	}
	point operator-(const point &t) const {
		return point(x - t.x, y - t.y);
	}
	point operator*(const double &t) const {
		return point(x * t, y * t);
	}
	point operator/(const double &t) const {
		return point(x / t, y / t);
	}
	void in() {
		scanf("%lf%lf", &x, &y);
	}
} pt[50005], p[50005];
struct Line {
	point a, v;
	double ang;
	Line(point a, point v) :
			a(a), v(v) {
		ang = atan2(v.y, v.x);
	}
	Line() {
	}
	bool operator <(const Line &t) const {
		return ang < t.ang;
	}
} L[50005], q[50005];
double cross(const point &a, const point &b) {
	return a.x * b.y - a.y * b.x;
}
bool left(const Line &L, const point &a) {
	return cross(L.v, a - L.a) > eps;
}
point lineLineIntersect(const Line &a, const Line &b) {
	double t = cross(b.a - a.a, b.v) / cross(a.v, b.v);
	return a.a + a.v * t;
}
bool halfPlaneIntersect(Line *L, int n) {
	sort(L, L + n);
	int s = 0, t = 0;
	q[0] = L[0];
	int i;
	for (i = 1; i < n; i++) {
		while (s < t && !left(L[i], p[t - 1]))
			t--;
		while (s < t && !left(L[i], p[s]))
			s++;
		q[++t] = L[i];
		if (!dcmp(q[t - 1].ang - q[t].ang)) {
			t--;
			if (left(q[t], L[i].a))
				q[t] = L[i];
		}
		if (s < t)
			p[t - 1] = lineLineIntersect(q[t - 1], q[t]);
	}
	while (s < t && !left(q[s], p[t - 1]))
		t--;

	if (t - s <= 1)
		return 0;
	return 1;
}
int n, c;
int solve(int n) {
	if (n == 3)
		return 1;
	int l = 1, r = n - 3;
	while (l <= r) {
		int m = l + r >> 1;
		c = 0;
		for (int i = 0; i < n; i++)
			L[c++] = Line(pt[(i + m + 1) % n], pt[i] - pt[(i + m + 1) % n]);
		if (halfPlaneIntersect(L, c))
			l = m + 1;
		else
			r = m - 1;
	}
	return l;
}
int main() {
	int i, j;
	while (~scanf("%d", &n)) {
		for (i = 0; i < n; i++)
			pt[i].in();
		printf("%d\n", solve(n));
	}
	return 0;
}