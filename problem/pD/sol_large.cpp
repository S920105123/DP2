#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
<<<<<<< HEAD
#include <map>
#include <cassert>
#define LL long long
#define PII pair<int, int>
const int MAXN = 100005;
const int INF = (int) 1e9 + 5;
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N;
	assert(N <= 100000);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		assert(0 <= a[i] && a[i] < 1000000);
	}
	
	PII *output = run(N, a);
	for (int i = 0; i < N; i++) {
		cout << output[i].first << " " <<output[i].second << '\n';
	}
=======
#include <algorithm>
#include <cassert>
#define LL long long
#define PII pair<int, int>
const int MAXK = 25;
const int MAXW = 1000005;
using namespace std;

int K, W, dp[2][MAXW], wei[MAXK];
vector<int> item[MAXK], pref[MAXK];

void solve(int i, int w, int rem, int l, int r, int opt_l, int opt_r) {
	int m = (l + r) >> 1, j = m * w + rem;
	int best = 0, where = -1;
	int *pre = dp[(i - 1) % 2], *cur = dp[i % 2];
	int lb = max(opt_l * w + rem, j - (int) item[i].size() * w);
	int rb = min(j, opt_r * w + rem);
	for (int k = lb; k <= rb; k += w) {
		int relax = pre[k] + pref[i][(j - k) / w];
		if (where == -1 || relax > best) {
			best = relax;
			where = k / w;
		}
	}
	
	cur[j] = best;
	if (l < m) solve(i, w, rem, l, m - 1, opt_l, where);
	if (m < r) solve(i, w, rem, m + 1, r, where, opt_r);
}

int run(int _K, int _W, int *_ws, vector<int> *_item) {
	/* Copy the parameters, it is for convenience of testing. */
	K = _K, W = _W;
	fill(dp[0], dp[0] + W + 1, 0);
	
	/* Do prefix sums */
	for (int i = 1; i <= K; i++) {
		wei[i] = _ws[i];
		item[i] = _item[i];
		sort(item[i].begin(), item[i].end(), greater<int>());
		pref[i].resize(_item[i].size() + 1);
		for (int j = 0; j < item[i].size(); j++) {
			pref[i][j + 1] = pref[i][j] + item[i][j];
		}
	}
	
	/* Do D&C DP stuff. */
	for (int i = 1; i <= K; i++) {
		int w = wei[i];
		for (int r = 0; r < w; r++) {
			assert(W / w > 0);
			int upto = (W % w >= r ? W / w : W / w - 1);
			solve(i, w, r, 0, upto, 0, upto);
		}
	}
	
	return *max_element(dp[K % 2], dp[K % 2] + W + 1);
}

int _N, _K, _W, _wei[MAXK];
vector<int> _item[MAXK];

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
	cin >> _N >> _W >> _K;
	for (int i = 1; i <= _K; i++) {
		cin >> _wei[i];
	}
	for (int i = 0; i < _N; i++) {
		int p, t;
		cin >> p >> t;
		_item[t].push_back(p);
	}
	
	cout << run(_K, _W, _wei, _item) << '\n';
>>>>>>> 91f1b9c3f47e9b3c41a4de095f4332e0ce2d395d
}
