#include <bits/stdc++.h>
#define PII pair<int, int>
#define LL long long
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

namespace Small {

const int MAXN = 5;
const int INF = (int)1e9 + 5;
int N, M, H[MAXN][MAXN], P[MAXN][MAXN];
int rs, cs, rt, ct;

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
	
	/* Do DFS */
	return dfs(rs, cs, P[rs][cs]);
}
}; // End of namespace Small

namespace Medium {
const int INF = (int)1e9 + 5;
const int MAXN = 505;
const int MAXC = 100005;

int N, M, dp[MAXN][MAXN];
mat H, P;
vector<PII> rnk[MAXC];

int run(int _N, int _M, PII src, PII tgt, mat _H, mat _P) {
	/* Copy the parameters for convenience of testing. */
	N = _N;
	M = _M;
	H = move(_H);
	P = move(_P);
	for (int i = 0; i < MAXC; i++) {
		rnk[i].clear();
	}
	
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
}; // End of namespace Medium

namespace Large {
const int INF = (int)1e9 + 5;
const int MAXN = 100005;
const int MAXC = 100005;

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

}; // End of namespace Large

const int MAXN = 1000005;
const int INF = (int) 1e9 + 5;
const int range_A = 100000;
int N, M, rs, cs, rt, ct;
mat H, P;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

void rand_gen() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			H[i][j] = rng() % range_A;
			P[i][j] = rng() % 21 - 10;
		}
	}
}

void strong_pattern() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			H[i][j] = i * M + j;
			P[i][j] = 1;
		}
		
		int dice = rng() % 3;
		if (i % 2 == 1) {
			reverse(H[i].begin(), H[i].end());
		}
		else if (rng() % 15 == 0) {
			random_shuffle(H[i].begin(), H[i].end());
		}
	}
}

void weak_pattern() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			H[i][j] = (i * M + j * N) / 100 + rng() % 500;
			assert(H[i][j] < 10000);
			P[i][j] = rand() % 3 - 1;
		}
		
		int dice = rng() % 3;
		if (i % 2 == 1) {
			reverse(H[i].begin(), H[i].end());
		}
		else if (rng() % 15 == 0) {
			random_shuffle(H[i].begin(), H[i].end());
		}
	}
}

int main() {
//	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int range_N = 300;
	ofstream fout, fans;
	fout.open("in.in");
	fans.open("out.ans");
	
	while (true) {
		N = rng() % range_N + 1;
		M = rng() % range_N + 1;
		N = 287, M = 183;
		if (N == 1 && M == 1) continue;
		H = mat(N, vec(M));
		P = mat(N, vec(M));
		weak_pattern();
//		rs = rand() % N;
//		cs = rand() % M;
//		do {
//			rt = rand() % N;
//			ct = rand() % M;
//		} while (rs == rt && cs == ct);
		rs = 5, cs = 0;
		rt = N - 1, ct = M - 5;
		
		int ans1 = INF, ans2 = INF, ans3 = INF;
//		ans1 = Small::run(N, M, {rs, cs}, {rt, ct}, H, P);
		ans2 = Medium::run(N, M, {rs, cs}, {rt, ct}, H, P);
		ans3 = Large::run(N, M, {rs, cs}, {rt, ct}, H, P);
		cout << N << " " << M  << " get " << ans1 << " " << ans2 << " " << ans3 << '\n';

		if (ans1 != INF) assert(ans1 == ans2);
		if (ans2 != INF) assert(ans2 == ans3);
		if (ans3 > 250) {
			fans << ans3 << '\n';
			fout << N << " " << M << " " << rs << " " << cs << " " << rt << " " << ct << "\n\n";
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					fout << H[i][j] << " \n"[j == M - 1];
				}
			}
			fout << '\n';
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < M; j++) {
					fout << P[i][j] << " \n"[j == M - 1];
				}
			}
			break;
		}
	}
	
	fout.close();
	fans.close();
	
	return 0;
}
