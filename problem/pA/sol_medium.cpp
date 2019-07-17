#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#define LL long long
#define PII pair<int, int> 
const int INF = (int)1e9 + 5;
const int MAXN = 45;
const int MAXC = 100005;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

struct Edge {
	int r1, c1, r2, c2, w;
};

int N, M, dist[MAXN][MAXN];
mat H, P;
vector<Edge> es;

int run(int _N, int _M, PII src, PII tgt, mat _H, mat _P) {
	/* Copy the parameters for convenience of testing. */
	N = _N;
	M = _M;
	H = move(_H);
	P = move(_P);
	es.clear();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			dist[i][j] = -INF;
		}
	}
	
	/* Construct graph */
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			/* For every point in the same row */
			for (int i = 0; i < M; i++) {
				if (H[r][c] < H[r][i]) {
					es.push_back({r, c, r, i, P[r][i]});
				}
			}
			
			/* For every point in diagnal direction 1 */
			int t = r - c;
			for (int i = 0; i < N; i++) {
				int j = i - t;
				if (0 <= j && j < M && H[r][c] < H[i][j]) {
					es.push_back({r, c, i, j, P[i][j]});
				}
			}
			
			/* For every point in diagnal direction 2 */
			for (int i = 0; i <= min(N, M); i++) {
				if (r + i < N && c - i >= 0 && H[r][c] < H[r + i][c - i]) {
					es.push_back({r, c, r + i, c - i, P[r + i][c - i]});
				}
				if (r - i >= 0 && c + i < M && H[r][c] < H[r - i][c + i]) {
					es.push_back({r, c, r - i, c + i, P[r - i][c + i]});
				}
			}
		}
	}
	
	int V = N * M;
	dist[src.first][src.second] = P[src.first][src.second];
	for (int i = 0; i < V - 1; i++) {
		for (const Edge &e : es) {
			int relax = dist[e.r1][e.c1] + e.w;
			if (dist[e.r1][e.c1] != -INF && relax > dist[e.r2][e.c2]) {
				dist[e.r2][e.c2] = relax;
			}
		}
	}
	
	return dist[tgt.first][tgt.second];
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

