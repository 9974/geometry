#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const int maxn = 100005;
struct point {
	int x, y;
	void in() {
		scanf("%d%d", &x, &y);
	}
	point operator-(const point &t) const {
		return (point) {x-t.x, y-t.y};
	}
	bool operator<(const point &t) const {
		return y < t.y || (y==t.y && x < t.x);
	}
	bool operator == (const point &t) const {
        return x == t.x && y == t.y;
	}
};
int cross(point a, point b) {
	return a.x*b.y-a.y*b.x;
}
vector <point> p;
vector <point> convex(vector <point> &p) {
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	int m = 0, i, n = p.size();
	vector <point> ch(n+1);
	for(i = 0; i < n; i++) {
		while(m > 1 && cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	int t = m;
	for(i = n-2; i >= 0; i--) {
		while(m > t && cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
		ch[m++] = p[i];
	}
	if(n > 1) m--;
	//printf("m = %d\n", m);
	ch.resize(m);
	return ch;
}
int dis2(point a, point b) {
	return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int rotating_calipers(vector <point> p) {
    int n = p.size();
	if(n <= 1) return 0;
	if(n == 2) return dis2(p[0], p[1]);
	p.push_back(p[0]);
	int i, j = 1;
	int ans = 0;
	for(i = 0; i < n; i++) {
		while(cross(p[i+1]-p[i], p[j+1]-p[i]) > cross(p[i+1]-p[i], p[j]-p[i]))
			j = (j+1)%n;
		ans = max(ans, max(dis2(p[i], p[j]), dis2(p[i+1], p[j+1])));
	}
	return ans;
}
int n;
int main() {
	int i, cas, x, y, w;
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d", &n);
		p.clear();
		for(i = 0; i < n; i++) {
			scanf("%d%d%d", &x, &y, &w);
			p.push_back((point) {x, y});
			p.push_back((point) {x+w, y});
			p.push_back((point) {x, y+w});
			p.push_back((point) {x+w, y+w});
		}
		printf("%d\n", rotating_calipers(convex(p)));

	}
	return 0;
}