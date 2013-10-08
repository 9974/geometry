#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
struct point {
	double x, y;
	point(double x = 0, double y = 0) :
			x(x), y(y) {
	}
} p[3], v[3];
double ct[3], d[3];
double dis(point a, point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double angle(double a, double b, double c) {
	return acos((b * b + c * c - a * a) / (2 * b * c));
}
point a, b, c, pa, pb, pc;

int dcmp(double x) {
	if (fabs(x) < eps)
		return 0;
	return x > eps ? 1 : -1;
}
int main() {
	int i;
	while (true) {
		bool flag = 1;
		for (i = 0; i < 3; i++) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
			flag &= (p[i].x == 0) & (p[i].y == 0);
		}
		if (flag)
			break;
		for (i = 0; i < 3; i++)
			d[i] = dis(p[(i + 1) % 3], p[(i + 2) % 3]);
		for (i = 0; i < 3; i++)
			ct[i] = angle(d[i], d[(i + 1) % 3], d[(i + 2) % 3]) * 0.5;
		double l = 0, r = min(d[2], d[1])*tan(ct[0]), m;
		double R1, R2;
		while(l + 1e-8 < r) {
			m = (l+r)*0.5; // r0
			R1 = tan(ct[1])*(sqrt(m+(d[2]-m/tan(ct[0]))/tan(ct[1])) - sqrt(m));  //R1 = sqrt(r1);
			R2 = tan(ct[2])*(sqrt(m+(d[1]-m/tan(ct[0]))/tan(ct[2])) - sqrt(m));  //R2 = sqrt(r2);
			int t = dcmp(R1*R2*2 -(d[0]-R1*R1/tan(ct[1])-R2*R2/tan(ct[2])));
			if(!t) break;
			if(t <  0) r = m;
			else l = m;
		}
		printf("%.6f %.6f %.6f\n", m, R1*R1, R2*R2);
	}
	return 0;
}
