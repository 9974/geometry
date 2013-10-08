#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
const double pi = acos(-1.0);
const double eps = 5*1e-13;
int n;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x > eps ? 1 : -1;
}
struct point {
	double x, y;
	void in() {
		scanf("%lf%lf", &x, &y);
	}
	point(double x=0, double y=0): x(x), y(y){}
	point operator-(const point &t) const {
		return point(x-t.x, y-t.y);
	}
	point operator+(const point &t) const {
		return point(x+t.x, y+t.y);
	}
	double len() {
		return sqrt(x*x+y*y);
	}
};
struct Circle {
	point o;
	double r;
	void in() {
		o.in();
		scanf("%lf", &r);
	}
}C[103];
double fix(double ct) {
	if(ct < -eps) ct += 2*pi;
	return ct;
}
double angle(point v) {
	return atan2(v.y, v.x);
}
void cirCirIntersect(Circle c1, Circle c2, vector <double> &sol) {
	point v = (c2.o-c1.o);
	double d = v.len();
	if(!dcmp(d)) return;
	if(d-c1.r-c2.r > eps) return;
	if(fabs(c1.r-c2.r)-d > eps) return;
	double ct = angle(v);
	double alf = acos((c1.r*c1.r+d*d-c2.r*c2.r)/(2*c1.r*d));
	sol.push_back(fix(ct+alf));
	sol.push_back(fix(ct-alf));
}
bool vis[103];
int top(point p) {
	for(int i = n-1; i >= 0; i--)
		if((p-C[i].o).len() < C[i].r) return i;
	return n;
}
int main() {
	int i, j;
	while(~scanf("%d", &n) && n) {
		for(i = 0; i < n; i++) C[i].in();
		memset(vis, 0, sizeof(vis));
		for(i = 0; i < n; i++) {
			vector <double> ans;
			ans.push_back(0);
			ans.push_back(2*pi);
			for(j = 0; j < n; j++)
				cirCirIntersect(C[i], C[j], ans);
			sort(ans.begin(), ans.end());
			for(j = 0; j < ans.size()-1; j++) {
				double mid = (ans[j]+ans[j+1])/2;
				for(int op = -1; op <= 1; op += 2) {
					double r = C[i].r+op*eps;
					point t = point(r*cos(mid), r*sin(mid))+C[i].o;
					vis[top(t)] = 1;
				}
			}
		}
		int ans = 0;
		for(i = 0; i < n; i++) ans += vis[i];
		printf("%d\n", ans);
	}
	return 0;
}