/*
Emaxx 
 complexity O(V^2E)

*/
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const int INF = 1000000000; 
 
struct edge {
    int a, b, cap, flow;
};
 
int n, s=0, t, d[MAXN], ptr[MAXN], q[MAXN];
vector<edge> e;
vector<int> g[MAXN];
 
void add_edge (int a, int b, int cap) {
    edge e1 = { a, b, cap, 0 };
    edge e2 = { b, a, 0, 0 };
    g[a].push_back ((int) e.size());
    e.push_back (e1);
    g[b].push_back ((int) e.size());
    e.push_back (e2);
}
 
bool bfs() {
    int qh=0, qt=0;
    q[qt++] = s;
    //memset (d, -1, n * sizeof d[0]);
    for(int i=s;i<=t;i++){
        d[i] = -1;
    }
    d[s] = 0;
    while (qh < qt && d[t] == -1) {
        int v = q[qh++];
        for (size_t i=0; i<g[v].size(); ++i) {
            int id = g[v][i],
                to = e[id].b;
            if (d[to] == -1 && e[id].flow < e[id].cap) {
                q[qt++] = to;
                d[to] = d[v] + 1;
            }
        }
    }
    return d[t] != -1;
}
 
int dfs (int v, int flow) {
    if (!flow)  return 0;
    if (v == t)  return flow;
    for (; ptr[v]<(int)g[v].size(); ++ptr[v]) {
        int id = g[v][ptr[v]],
            to = e[id].b;
        if (d[to] != d[v] + 1)  continue;
        int pushed = dfs (to, min (flow, e[id].cap - e[id].flow));
        if (pushed) {
            e[id].flow += pushed;
            e[id^1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}
 
int dinic() {
    int flow = 0;
    for (;;) {
        if (!bfs())  break;
        //memset (ptr, 0, n * sizeof ptr[0]);
        for(int i = s;i<=t;i++){
            ptr[i] = 0;
        }
        while (int pushed = dfs (s, INF))
            flow += pushed;
            //cout<<flow<<"\n";
    }
    return flow;
}
int32_t main()
{

    int m;
    cin >> n >> m;   // number of nodes and edges respectively
    s=1;    // source 
    t=n;   // sink 
    for(int i=1;i<=m;i++){
        int x,y,z;
        //x--;y--;
        cin >> x >> y >> z;
        add_edge(x, y,z);
    }
    cout<<dinic()<<"\n";
}

/*
adjancy matrix implementation
*/

onst int MAXN = ...; // число вершин
const int INF = 1000000000; // константа-бесконечность
 
int n, c[MAXN][MAXN], f[MAXN][MAXN], s, t, d[MAXN], ptr[MAXN], q[MAXN];
 
bool bfs() {
	int qh=0, qt=0;
	q[qt++] = s;
	memset (d, -1, n * sizeof d[0]);
	d[s] = 0;
	while (qh < qt) {
		int v = q[qh++];
		for (int to=0; to<n; ++to)
			if (d[to] == -1 && f[v][to] < c[v][to]) {
				q[qt++] = to;
				d[to] = d[v] + 1;
			}
	}
	return d[t] != -1;
}
 
int dfs (int v, int flow) {
	if (!flow)  return 0;
	if (v == t)  return flow;
	for (int & to=ptr[v]; to<n; ++to) {
		if (d[to] != d[v] + 1)  continue;
		int pushed = dfs (to, min (flow, c[v][to] - f[v][to]));
		if (pushed) {
			f[v][to] += pushed;
			f[to][v] -= pushed;
			return pushed;
		}
	}
	return 0;
}
 
int dinic() {
	int flow = 0;
	for (;;) {
		if (!bfs())  break;
		memset (ptr, 0, n * sizeof ptr[0]);
		while (int pushed = dfs (s, INF))
			flow += pushed;
	}
	return flow;
}
