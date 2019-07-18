#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define LL long long
#define PII pair<int, int> 
const int INF = (int)1e9 + 5;
const int MAXN = 1000005;
const int MAXC = 1000005;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int N, M, from_r[MAXN], from_d1[2 * MAXN], from_d2[2 * MAXN];
mat H, P, dp;
vector<PII> rnk[MAXC];

int run(int _N, int _M, PII src, PII tgt, mat _H, mat _P) {
	/* Copy the parameters for convenience of testing. */
	N = _N;
	M = _M;
	H = move(_H);
	P = move(_P);
	dp = mat(N, vec(M, -INF));
	fill(from_r, from_r + MAXN, -INF);
	fill(from_d1, from_d1 + 2 * MAXN, -INF);
	fill(from_d2, from_d2 + 2 * MAXN, -INF);
	for (int i = 0; i < MAXC; i++) {
		rnk[i].clear();
	}
	
	/* Find order */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			rnk[H[i][j]].push_back({i, j});
		}
	}
	
	/* Do dp[i][j]: Maximum profit to reach here from (rs, cs). */
	for (int i = 0; i < MAXC; i++) {
		for (PII coord : rnk[i]) {
			int r = coord.first, c = coord.second;
			if (coord == src) {
				dp[r][c] = 0;
			}
			else {
				dp[r][c] = max({from_r[r], from_d1[r + c], from_d2[r - c + (M - 1)]});
			}
			
			if (dp[r][c] != -INF) {
				dp[r][c] += P[r][c];
			}
		}
		for (PII coord : rnk[i]) {
			int r = coord.first, c = coord.second;
			from_r[r] = max(from_r[r], dp[r][c]);
			from_d1[r + c] = max(from_d1[r + c], dp[r][c]);
			from_d2[r - c + (M - 1)] = max(from_d2[r - c + (M - 1)], dp[r][c]);
		}
	}
	
	return dp[tgt.first][tgt.second];
}

int main() {
	// ios_base::sync_with_stdio(0); cin.tie(0);
	
	int rs, cs, rt, ct;
	cin >> N >> M >> rs >> cs >> rt >> ct;
	H = mat(N, vec(M));
	P = mat(N, vec(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> H[i][j];
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> P[i][j];
		}
	}
	
	int result = run(N, M, PII(rs, cs), PII(rt, ct), H, P);
	if (result == -INF) {
		cout << "You are fired!\n";
	}
	else {
		cout << result << '\n';
	}
	
	return 0;
}

