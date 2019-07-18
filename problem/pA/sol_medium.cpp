#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <tuple>
#define LL long long
#define PII pair<int, int> 
const int INF = (int)1e9 + 5;
const int MAXN = 305;
const int MAXC = 1000005;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int N, M, dp[MAXN][MAXN], rs, cs, rt, ct;
mat H, P;
vector<PII> rnk[MAXC];

void input_assertion() {
	assert(N <= 300 && M <= 300);
	assert(0 <= rs && rs < N);
	assert(0 <= cs && cs < M);
	assert(0 <= rt && rt < N);
	assert(0 <= ct && ct < M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			assert(-10 < P[i][j] && P[i][j] < 10);
			assert(0 <= H[i][j] && H[i][j] < 1000000);
		}
	}
}

int run(int _N, int _M, PII src, PII tgt, mat _H, mat _P) {
	/* Copy the parameters for convenience of testing. */
	N = _N;
	M = _M;
	H = move(_H);
	P = move(_P);
	for (int i = 0; i < MAXC; i++) {
		rnk[i].clear();
	}
	tie(rs, cs) = src;
	tie(rt, ct) = tgt;
	input_assertion();
	
	/* Find order */
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			rnk[H[i][j]].push_back({i, j});
		}
	}
	
	/* Do dp */
	for (int i = 0; i < MAXC; i++) {
		for (PII &coord : rnk[i]) {
			int r = coord.first, c = coord.second;
			if (r == src.first && c == src.second) {
				dp[r][c] = P[r][c];
				continue;
			}
			
			dp[r][c] = -INF;
			
			/* For every point in the same row */
			for (int j = 0; j < M; j++) {
				if (H[r][c] > H[r][j]) {
					dp[r][c] = max(dp[r][c], dp[r][j]);
				}
			}
			
			/* For every point in diagnal direction */
			int t = r + c;
			for (int j = 0; j < N; j++) {
				int pr = j, pc = t - pr;
				if (0 <= pc && pc < M && H[r][c] > H[pr][pc]) {
					dp[r][c] = max(dp[r][c], dp[pr][pc]);
				}
			}
			t = r - c;
			for (int j = 0; j < N; j++) {
				int pr = j, pc = pr - t;
				if (0 <= pc && pc < M && H[r][c] > H[pr][pc]) {
					dp[r][c] = max(dp[r][c], dp[pr][pc]);
				}
			}
			
			if (dp[r][c] != -INF) {
				dp[r][c] += P[r][c];
			}
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

