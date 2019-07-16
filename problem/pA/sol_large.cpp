#include <iostream>
#define LL long long
const int INF = (int)1e9 + 5;
const int MAXN = 100005;
using namespace std;

typedef vector<int> vec;
typedef vector<vec> mat;

int N, M, strat_r[MAXN], strat_d1[2*MAXN], strat_d2[2*MAXN];
mat w, p;
vector<pair<int, int>> ord;

int main() {
	// ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> N >> M;
	w = mat(N, vec(M));
	p = mat(N, vec(M));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> w[i][j];
			ord.push_back({w[i][j], i * M + j});
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> p[i][j];
		}
	}
	
	sort(ord.begin(), ord.end());
	for (pair<int, int> p : ord) {
		
	}
	
	
	return 0;
}
