#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
struct point {
	ll x, y, z;
	point(ll x=0, ll y=0, ll z=0):x(x), y(y), z(z) {}
	point operator-(const point &t) {
		return point(x-t.x, y-t.y, z-t.z);
	}
	void in() {
		cin >> x >> y >> z;
	}
	int len() {
		return x*x+y*y+z*z;
	}
};
ll gcd(ll a, ll b) {
	return b ? gcd(b, a%b) : a;
}
ll lcm(ll a, ll b) {
	return a/gcd(a, b)*b;
}
struct node {
	ll a, b;
	node(){}
	node(ll a): a(a), b(1) {}
	node(ll aa, ll bb): a(aa), b(bb) {
		if(a < 0) a = -a, b = -b;
		//if(a == 0) b = 1;
		int t = gcd(a, b);
		if(t < 0 )t = -t;
		a /= t, b /= t;
	}
	node operator*(const node &t) const {
		return node(a*t.a, b*t.b);
	}
	node operator+(const node &t) const {
		ll x = lcm(b, t.b);
		return node(x/b*a+x/t.b*t.a, x);
	}
	node operator-(const node &t) const {
		ll x = lcm(b, t.b);
		return node(x/b*a-x/t.b*t.a, x);
	}
};
point cross(point a, point b) {
	return point(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}
ll dot(point a, point b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}
node disPointToSeg(point P, point A, point B) {
  if(!(A-B).len()) return (P-A).len();
  point v1 = B - A, v2 = P - A, v3 = P - B;
  if(dot(v1, v2) < 0) return v2.len();
  else if(dot(v1, v3) > 0) return v3.len();
  else return node(cross(v1, v2).len(), v1.len());
}
bool disLineLine(point a1, point v1, point a2, point v2, node &t) {
	int b = dot(v1, v1) * dot(v2, v2)-dot(v1, v2)*dot(v1, v2);
	if(!b) return 0;
	int a = dot(a1-a2, v2) * dot(v1, v2) - dot(a1-a2, v1)*dot(v2, v2);
	t = node(a, b);
	return 1;
}
node x1, x2, y1, y2, z1, z2, t1, t2;
void getPoint(point a, point v, node t, node &x, node &y, node &z) {
	x = node(a.x)+node(v.x)*t;
	y = node(a.y)+node(v.y)*t;
	z = node(a.z)+node(v.z)*t;
}
node Min(node a, node b) {
	if(a.a*b.b>=a.b*b.a) return b;
	return a;
}
node cal() {
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2);
}

node disPointToSeg2(point a, point l, point r) {
	if(!(l-r).len()) return node((a-l).len());
	if(dot(a-l, r-l) < 0) return node((a-l).len());
	else if(dot(a-r, l-r) < 0) return node((a-r).len());
	return node(cross(a-l, r-l).len(), (r-l).len());
}
point a, b, c, d;
int main() {
	int cas;
	scanf("%d", &cas);
	while(cas--) {
	    bool ok = 0;
		node ans = node(1000000000);
		a.in(), b.in(), c.in(), d.in();
		if(disLineLine(a, b-a, c, d-c, t1)) {
			if(t1.a > 0 && t1.a < t1.b) {
				if(disLineLine(c, d-c, a, b-a, t2))
					if(t2.a > 0 && t2.a < t2.b) {
					    ok = 1;
					  //  puts("234");
						getPoint(a, b-a, t1, x1, y1, z1);
						getPoint(c, d-c, t2, x2, y2, z2);
						node w =  cal();
						ans = Min(ans, cal());
					}
			}
		}
		if(!ok){
			ans = Min(ans, disPointToSeg(a, c, d));
			ans = Min(ans, disPointToSeg(b, c, d));
			ans = Min(ans, disPointToSeg(c, a, b));
			ans = Min(ans, disPointToSeg(d, a, b));
		}
		cout << ans.a << " " << ans.b << endl;
	}
	return 0;
}
/*
0 0 0 4 4 0
0 4 0 4 0 0
*/