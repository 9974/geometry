#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const double eps = 1e-8;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x > eps ? 1 : -1;
}
struct point {
	double x, y;
	point(double x=0, double y=0): x(x), y(y) {}
	point operator+(const point &t) const {
		return point(x+t.x, y+t.y);
	}
	point operator-(const point &t) const {
		return point(x-t.x, y-t.y);
	}
	point operator*(const double &t) const {
		return point(x*t, y*t);
	}
	point operator/(const double &t) const {
		return point(x/t, y/t);
	}
};
struct Line {
	point a, v;
	double ang;
	Line(point a, point v): a(a), v(v){
		ang = atan2(v.y, v.x);
	}
	Line(){}
	bool operator <(const Line &t) const {
		return ang < t.ang;
	}
};

double cross(point a, point b) {
	return a.x*b.y-a.y*b.x;
}
bool left(Line L, point a) {
	return cross(L.v, a-L.a) > eps;
}
point lineLineIntersect(Line a, Line b) {
	double t = cross(b.a-a.a, b.v) / cross(a.v, b.v);
	return a.a + a.v*t;
}
bool halfPlaneIntersect(vector <Line> &L) {
	sort(L.begin(), L.end());
	int n = L.size();
	point *p = new point[n];
	Line *q = new Line[n];
	int s = 0, t = 0;
	q[0] = L[0];
	int i;
	for(i = 1; i < n; i++) {
		while(s < t && !left(L[i], p[t-1])) t--;
		while(s < t && !left(L[i], p[s])) s++;
		q[++t] = L[i];
		if(!dcmp(q[t-1].ang-q[t].ang)) {
			t--;
			if(left(q[t], L[i].a)) q[t] = L[i];
		}
		if(s < t) p[t-1] = lineLineIntersect(q[t-1], q[t]);
	}
	while(s < t && !left(q[s], p[t-1])) t--;
	return t-s <=1 ? 0 : 1;
}
int n;
double u[103], v[103], w[103];
double tot = 10000;
int main() {
	int i, j;
	while(~scanf("%d", &n)) {
		for(i = 0; i < n; i++)
			scanf("%lf%lf%lf", &v[i], &u[i], &w[i]);
		for(i = 0; i < n; i++) {
			vector <Line> L;
			bool ok = 1;
			for(j = 0; j < n; j++) if(i != j) {
				if(v[i] <= v[j] && u[i] <= u[j] && w[i] <= w[j]) {ok = 0; break;}
				if(v[i] >= v[j] && u[i] >= u[j] && w[i] >= w[j]) continue;
				double a = tot/v[j]-tot/v[i]+tot/w[i]-tot/w[j];
				double b = tot/u[j]-tot/u[i]+tot/w[i]-tot/w[j];
				double c = tot/w[j]-tot/w[i];
				if(fabs(a) > fabs(b)) L.push_back(Line(point(-c/a, 0), point(b, -a)));
				else L.push_back(Line(point(0, -c/b), point(b, -a)));
			}
			if(ok) {
				L.push_back(Line(point(0, 0), point(0, -1)));
				L.push_back(Line(point(0, 0), point(1, 0)));
				L.push_back(Line(point(0, 1), point(-1, 1)));
				ok = halfPlaneIntersect(L);
			}
			ok ? puts("Yes") : puts("No");
		}
	}
	return 0;
}