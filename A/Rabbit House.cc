/**
 *	Author: Nachiket Kanore
 *	Created: Sunday 21 March 2021 09:58:14 AM IST
**/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <set>
#include <cstring>
#include <array>

#define int int64_t
#define pb push_back
#define sz(x) (int)(x.size())
#define ALL(x) (x).begin(),(x).end()
#define F0R(i,R) for(int i = (0); i < (R); ++i)
#define FOR(i,L,R) for(int i = (L); i <= (R); ++i)
using namespace std;

template<typename T> ostream& operator<<(ostream &os, const vector<T> &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T, size_t size> ostream& operator<<(ostream &os, const array<T, size> &arr) { os << '{'; string sep; for (const auto &x : arr) os << sep << x, sep = ", "; return os << '}'; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
 
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }

#ifdef DEBUG
#define see(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define see(...)
#endif

template<class T> bool cmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool cmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; } 

const int inf = 1e18;
const int N = 1000 + 5;
int n, m, mat[N][N], vis[N][N];

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

void solve() {
	cin >> n >> m;
	int mx = -1;
	memset(vis, 0, sizeof(vis));
	
	auto inside = [&](int i, int j) {
		return i >= 1 && i <= n && j >= 1 && j <= m;
	};
	int ans = 0;
	set< array<int,3> > Q;
	FOR (i,1,n) FOR (j,1,m) {
		cin >> mat[i][j];
		Q.insert({mat[i][j], i, j});
	}

	while (!Q.empty()) {
		auto [fk, i, j] = *Q.rbegin(); Q.erase(Q.find(*Q.rbegin()));
		see(i, j, fk);
		if (vis[i][j]) continue;
		vis[i][j] = 1;
		F0R (k,4) {
			int ni = i + dx[k];
			int nj = j + dy[k];
			if (!inside(ni, nj) || vis[ni][nj] || abs(mat[i][j] - mat[ni][nj]) <= 1) continue;
			assert(mat[i][j] >= mat[ni][nj]);
			ans += max(mat[i][j] - mat[ni][nj] - 1, (int)0);
			mat[ni][nj] = mat[i][j]-1;
			Q.insert({mat[ni][nj], ni, nj});
		}
	}
	cout << ans << '\n';
	FOR (i,1,n) FOR (j,1,m) cerr << mat[i][j] << " \n"[j==m];
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T; 
	FOR (tc,1,T) {
		cout << "Case #" << tc << ": ";
		solve();
	}
}
