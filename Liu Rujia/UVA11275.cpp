//没有三角形共面的数据，这个代码也没判这种情况
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x > eps ? 1 : -1;
}
struct point {
	double x, y, z;
	point(double x=0, double y=0, double z=0): x(x), y(y), z(z){}
	point operator+(const point &t) const {
		return point(x+t.x, y+t.y, z+t.z);
	}
	point operator-(const point &t) const {
		return point(x-t.x, y-t.y, z-t.z);
	}
	point operator*(const double &t) const {
		return point(x*t, y*t, z*t);
	}
	double len() {
		return sqrt(x*x+y*y+z*z);
	}
	void in() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
}p[3], q[3];
int n;
point cross(point a, point b) {
	return point(a.y*b.z-b.y*a.z, a.z*b.x-b.z*a.x, a.x*b.y-b.x*a.y);
}
double dot(point a, point b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
double area(point a, point b, point c) {
	return cross(b-a, c-a).len();
}
double PointInTri(point p, point p1, point p2, point p3) {
	return !dcmp( area(p, p1, p2) + area(p, p2, p3) + area(p, p1, p3) - area(p1, p2, p3) );
}
bool triSegIntersect(point p1, point p2, point p3, point a, point b) {
	point n = cross(p2-p1, p3-p1);
	if(!dcmp(dot(b-a, n))) return 0;
	double t = dot(n, p1-a)/dot(n, b-a);
	if(t < -eps || t > 1+eps) return 0;
	point p = a+(b-a)*t;
	return PointInTri(p, p1, p2, p3);
}
bool triTriIntersect(point *p, point *q) {
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = i+1; j < 3; j++) {
			if(triSegIntersect(p[0], p[1], p[2], q[i], q[j])) return 1;
			if(triSegIntersect(q[0], q[1], q[2], p[i], p[j])) return 1;
		}
	return 0;
}
int main() {
	int i, j, cas;
	scanf("%d", &cas);
	while(cas--) {
		for(i = 0; i < 3; i++) p[i].in();
		for(i = 0; i < 3; i++) q[i].in();
		triTriIntersect(p, q) ? puts("1") : puts("0");
	}
	return 0;
}