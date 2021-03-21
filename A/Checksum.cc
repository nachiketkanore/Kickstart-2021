/**
 *	Author: Nachiket Kanore
 *	Created: Sunday 21 March 2021 02:47:16 PM IST
**/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <string>
#include <array>
#include <cstring>

#define int long long
#define pb push_back
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(),(x).end()
#define F0R(i,R) for(int i = (0); i < (R); ++i)
#define FOR(i,L,R) for(int i = (L); i <= (R); ++i)
using namespace std;

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } 

const int inf = 1e18;
const int N = 505;

class DSU
{
public:
	int connected;
	vector<int> par, sz;
 
	void init(int n) 
	{
		par.resize(n+1);
		sz.resize(n+1);
		for(int i=1;i<=n;i++)
		{
			par[i]=i;
			sz[i]=1;
		}
		connected=n;
	}
 
	int getPar(int k)
	{
		while(k!=par[k])
		{
			par[k]=par[par[k]];
			k=par[k];
		}
		return k;
	}
 
	int getSize(int k)
	{
		return sz[getPar(k)];
	}

	bool same(int u , int v)
	{
		return (getPar(u) == getPar(v));
	}
 
	bool unite(int u, int v)
	{
		int par1=getPar(u), par2=getPar(v);
 
		if(par1==par2)
			return false;
 
		connected--;
 
		if(sz[par1]>sz[par2])
			swap(par1, par2);
 
		sz[par2]+=sz[par1];
		sz[par1]=0;
		par[par1]=par[par2];
		return true;
	}
};

int n, mat[N][N], cost[N][N], R[N], C[N];

void solve() {
	cin >> n;
	FOR (i,1,n) FOR (j,1,n) cin >> mat[i][j];
	vector<array<int, 3>> edges;
	int tot = 0, rem = 0;
	FOR (i,1,n) FOR (j,1,n) {
		cin >> cost[i][j];
		if (mat[i][j] == -1) {
			tot += cost[i][j];
			edges.push_back({cost[i][j], i, n+j});
		}
	}
	FOR (i,1,n) cin >> R[i];
	FOR (i,1,n) cin >> C[i];
	DSU dsu;
	dsu.init(2*n);
	sort(ALL(edges));	reverse(ALL(edges));
	for (auto [w, u, v] : edges) {
		if (dsu.unite(u, v)) rem += w;
	}
	cout << (tot - rem) << '\n';
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T; 
	FOR (tc,1,T) {
		cout << "Case #" << tc << ": ";
		solve();
	}
}
