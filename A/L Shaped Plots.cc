/**
 *	Author: Nachiket Kanore
 *	Created: Sunday 21 March 2021 09:34:55 AM IST
**/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>
#include <array>
#include <cstring>

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
const int N = 2e3 + 5;
int n, m;
int mat[N][N];
int dp[4][N][N];

bool inside(int i, int j) {
	return i >= 1 && i <= n && j >= 1 && j <= m;
}

int goUp(int i, int j) {
	if (!inside(i,j) || !mat[i][j]) return 0;
	int &ans = dp[0][i][j];
	if (~ans) return ans;
	ans = 1 + goUp(i-1, j);
	return ans;
}
int goDown(int i, int j) {
	if (!inside(i,j) || !mat[i][j]) return 0;
	int &ans = dp[1][i][j];
	if (~ans) return ans;
	ans = 1 + goDown(i+1, j);
	return ans;
}
int goLeft(int i, int j) {
	if (!inside(i,j) || !mat[i][j]) return 0;
	int &ans = dp[2][i][j];
	if (~ans) return ans;
	ans = 1 + goLeft(i, j-1);
	return ans;
}
int goRight(int i, int j) {
	if (!inside(i,j) || !mat[i][j]) return 0;
	int &ans = dp[3][i][j];
	if (~ans) return ans;
	ans = 1 + goRight(i, j+1);
	return ans;
}

void solve() {
	cin >> n >> m;
	int ans = 0;
	memset(dp, -1, sizeof(dp));
	FOR (i,1,n) FOR (j,1,m) cin >> mat[i][j];
	auto cnt = [&](int one, int two) {
		int ret = 0;
		if (min(one, two) <= 1) return int(0);
		for (int t = 2; t <= one; t++) {
			if (2 * t <= two) ++ret;
			else break;
		}
		for (int t = 2; t <= two; t++) {
			if (2 * t <= one) ++ret;
			else break;
		}
		return ret;
	};
	FOR (i,1,n) FOR (j,1,m) if (mat[i][j]) {
		int up = goUp(i,j);
		int down = goDown(i,j);
		int left = goLeft(i,j);
		int right = goRight(i,j);
		// see(i, j, up, down, left, right);
		ans += cnt(up, right);
		ans += cnt(right, down);
		ans += cnt(up, left);
		ans += cnt(left, down);
	}
	cout << ans << '\n';
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int T; cin >> T; 
	FOR (tc,1,T) {
		cout << "Case #" << tc << ": ";
		solve();
	}
}
