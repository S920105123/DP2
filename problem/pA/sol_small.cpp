#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cassert>
#define LL long long
#define PII pair<int, int> 
const int MAXN = 5;
const int INF = (int)1e9 + 5;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

namespace Small {
	
int N, M, H[MAXN][MAXN], P[MAXN][MAXN];
int rs, cs, rt, ct;

void input_assertion() {
	assert(N <= 3);
	assert(M <= 3);
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

int dfs(int r, int c, int profit) {
	if (r == rt && c == ct) {
		return profit;
	}
	
	int best = -INF;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (i == r || i + j == r + c || i - j == r - c) {
				if (H[i][j] > H[r][c]) {
					best = max(best, dfs(i, j, profit + P[i][j]));
				}
			}
		}
	}
	
	return best;
}

int run(int _N, int _M, PII _src, PII _tgt, mat _H, mat _P) {
	/* Copy the parameters for convenience of testing. */
	N = _N;
	M = _M;
	tie(rs, cs) = _src;
	tie(rt, ct) = _tgt;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			H[i][j] = _H[i][j];
			P[i][j] = _P[i][j];
 		}
	}
	input_assertion();
	
	/* Do DFS */
	return dfs(rs, cs, P[rs][cs]);
}	
	
}

int main() {
	// ios_base::sync_with_stdio(0); cin.tie(0);
	
	mat H, P;
	int N, M, rs, cs, rt, ct;
	
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
	
	int result = Small::run(N, M, PII(rs, cs), PII(rt, ct), H, P);
	if (result == -INF) {
		cout << "You are fired!\n";
	}
	else {
		cout << result << '\n';
	}
	
	return 0;
}

