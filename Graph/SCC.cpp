 #include <bits/stdc++.h>
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
     
    using namespace std;
    using namespace __gnu_pbds;
     
    #define fi first
    #define se second
    #define mp make_pair
    #define pb push_back
     
    typedef long long ll;
    typedef pair<ll,ll> ii;
    typedef vector<int> vi;
    typedef unsigned long long ull;
    typedef long double ld; 
    typedef tree<ii, null_type, less<ii>, rb_tree_tag, tree_order_statistics_node_update> pbds;
     
    struct SCC
    {
    	const int INF = int(1e9);
    	vector<vector<int> > vec;
    	int index;
    	vector<int> idx;
    	vector<int> lowlink;
    	vector<bool> onstack;
    	stack<int> s;
    	vector<int> sccidx;
    	int scccnt;
    	vi topo;
    	
    	//lower sccidx means appear later
    	void init(int n)
    	{
    		idx.assign(n,-1);
    		index = 0;
    		onstack.assign(n,0);
    		lowlink.assign(n,INF);
    		while(!s.empty()) s.pop();
    		sccidx.assign(n,-1);
    		scccnt = 0;
    		vec.clear();
    		topo.clear();
    		vec.resize(n);
    	}
    	
    	void addedge(int u, int v) //u -> v
    	{
    		vec[u].pb(v);
    	}
    	
    	void connect(int u)
    	{
    		idx[u] = index;
    		lowlink[u] = index;
    		index++;
    		s.push(u);
    		onstack[u] = true;
    		for(int i = 0; i < vec[u].size(); i++)
    		{
    			int v = vec[u][i];
    			if(idx[v] == -1)
    			{
    				connect(v);
    				lowlink[u] = min(lowlink[u], lowlink[v]);
    			}
    			else if(onstack[v])
    			{
    				lowlink[u] = min(lowlink[u], idx[v]);
    			}
    		}
    		if(lowlink[u] == idx[u])
    		{
    			while(1)
    			{
    				int v = s.top();
    				s.pop();
    				onstack[v] = false;
    				sccidx[v] = scccnt;
    				if(v == u) break;
    			}
    			scccnt++;
    		}
    	}
    	
    	void tarjan()
    	{
    		for(int i = 0; i < vec.size(); i++)
    		{
    			if(idx[i] == -1)
    			{
    				connect(i);
    			}
    		}
    	}
    	
    	void toposort() //if graph is a DAG and i just want to toposort
    	{
    		tarjan();
    		int n = vec.size();
    		topo.resize(n);
    		vector<ii> tmp;
    		for(int i = 0; i < n; i++)
    		{
    			tmp.pb(mp(sccidx[i],i));
    		}
    		sort(tmp.begin(),tmp.end());
    		reverse(tmp.begin(),tmp.end());
    		for(int i = 0; i < n; i++)
    		{
    			topo[i]=tmp[i].se;
    			if(i>0) assert(tmp[i].fi!=tmp[i-1].fi);
    		}
    	}
    };



//  kosarajju's algorithms

vector<int> g[N], newg[N], rg[N], todo;
int comp[N], indeg[N]; 
bool vis[N];
vector<int> gr[N];

void dfs(int k)
{
	vis[k]=1;
	for(auto it:g[k])
	{
		if(!vis[it])
			dfs(it);
	}
	todo.push_back(k);
}

void dfs2(int k, int val)
{
	comp[k]=val;
	for(auto it:rg[k])
	{
		if(comp[it]==-1)
			dfs2(it, val);
	}
}

void sccAddEdge(int from, int to)
{
	g[from].push_back(to);
	rg[to].push_back(from);
}

void scc()
{
	for(int i=1;i<=n;i++)
		comp[i]=-1;

	for(int i=1;i<=n;i++)
	{
		if(!vis[i])
			dfs(i);
	}

	reverse(todo.begin(), todo.end());

	for(auto it:todo)
	{
		if(comp[it]==-1)
		{
			dfs2(it, ++grp);
		}
	}
}

///  https://www.spoj.com/problems/CAPCITY/
/// solution : https://pastebin.com/xkHu0Rub

///https://www.spoj.com/problems/TOUR/
/// https://pastebin.com/5EZF4DfN
