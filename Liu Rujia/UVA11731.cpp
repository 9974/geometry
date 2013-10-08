#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
const double pi = acos(-1.0);
double a, b, c, A, B, C, D, E, F;
double angle(double &a, double &b, double &c) {
	return acos((b*b+c*c-a*a)/(2*b*c));
}
double area(double a, double b, double c) {
	double p = (a+b+c)/2;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}
double areaTri(double a, double B, double C) {
	double A = pi-B-C, b, c;
	b = a/sin(A)*sin(B);
	c = a/sin(A)*sin(C);
	return area(a, b, c);
}
double areaCir(double a, double B, double C) {
	double A = pi-B-C, b, c;
	b = a/sin(A)*sin(B);
	c = a/sin(A)*sin(C);
	double r = area(a, b, c)*2/a;
	return r*r*A*0.5;
}
int main() {
	int i, j, ca = 1;
	while(~scanf("%lf%lf%lf", &a, &b, &c)) {
		if(a==0 && b==0 && c ==0) break;
		A = angle(a, b, c), B = angle(b, a, c), C = angle(c, a, b);
		printf("Case %d: ", ca++);
		printf("%.2f ", area(a, b, c) + areaTri(a, (pi-B)*0.5, (pi-C)*0.5)+
				areaTri(b, (pi-A)*0.5, (pi-C)*0.5) + areaTri(c, (pi-A)*0.5, (pi-B)*0.5));
		printf("%.2f\n", areaCir(a, (pi-B)*0.5, (pi-C)*0.5)+
				areaCir(b, (pi-A)*0.5, (pi-C)*0.5) + areaCir(c, (pi-A)*0.5, (pi-B)*0.5));
	}
	return 0;
}