#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int (i)=0;(i)<(int)(n);(i)++)
#define REPO(i,n) for(int (i)=1; (i)<=(int)(n); (i)++)
#define SZ(v) ((int)(v).size())
#define ALL(v) (v).begin(),(v).end()
#define one first
#define two second
typedef long long ll;
typedef pair<int, int> pi;
const int INF = 0x3f2f1f0f;
const ll LINF = 1ll * INF * INF;


const int MAX_V = 1e3 + 10;

struct ED {
	int to, fl, co, re;
	ED(int t, int f, int c, int r) :to(t), fl(f), co(c), re(r) {}
};
int N, M, St, En;
vector<ED> Ed[MAX_V];
void addEdge(int fr, int to, int fl, int co) {
	Ed[fr].push_back(ED(to, fl, +co, Ed[to].size()));
	Ed[to].push_back(ED(fr, 0, -co, Ed[fr].size()-1));
}

void initGraph() {

}
void deleteGraph() {
	for(int i=St; i<=En; i++) {
		vector<ED> temp;
		Ed[i].swap(temp);
	}
}
int Dis[MAX_V], Wh[MAX_V], Ix[MAX_V]; bool inQ[MAX_V];
bool spfa() {
	for(int i=St; i<=En; i++) Dis[i] = 1e9, inQ[i] = false;
	queue<int> Q; Q.push(St); Dis[St] = 0, inQ[St] = true;
	while(!Q.empty()) {
		int v = Q.front(); Q.pop(); inQ[v] = false;
		for(int i=0; i<Ed[v].size(); i++) {
			ED &e = Ed[v][i];
			if(e.fl > 0 && Dis[e.to] > Dis[v] + e.co) {
				Dis[e.to] = Dis[v] + e.co;
				Wh[e.to] = v; Ix[e.to] = i;
				if(inQ[e.to] == false) inQ[e.to] = true, Q.push(e.to);
			}
		}
	}
	return Dis[En] != 1e9;
}
int main() {
	int TC = 1;
	for(int tc=1; tc<=TC; tc++) {
		initGraph();
		int flow = 0, cost = 0;
		while(spfa()) {
			int minF = 1e9;
			for(int w=En, i, v, r; w!=St; w=v) {
				v=Wh[w], i=Ix[w], r=Ed[v][i].re;
				minF = min(minF, Ed[v][i].fl);
			}
			for(int w=En, i, v, r; w!=St; w=v) {
				v=Wh[w], i=Ix[w], r=Ed[v][i].re;
				Ed[v][i].fl -= minF;
				Ed[w][r].fl += minF;
			}
			flow += minF;
			cost += minF * Dis[En];
		}
		printf("%d\n", cost);
		deleteGraph();
	}
	return 0;
}
