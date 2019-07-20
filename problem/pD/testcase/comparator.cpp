#include <bits/stdc++.h>
#define LL long long
#define PII pair<int, int>
using namespace std;

namespace Small {
const int MAXK = 25;
const int MAXW = 1005;
const int MAXN = 1005;
int N, K, W, dp[MAXW], wei[MAXN], val[MAXN];

int run(int _K, int _W, int *_ws, vector<int> *_item) {
	/* Copy the parameters, it is for convenience of testing. */
	N = 0;
	K = _K, W = _W;
	fill(dp, dp + W + 1, 0);
	
	/* Extract all items, now we only need to solve a 0-1 knapsack. */
	for (int i = 1; i <= K; i++) {
		for (int v : _item[i]) {
			wei[N] = _ws[i];
			val[N] = v;
			N++;
		}
	}
	
	/* Do normal DP stuff. */
	for (int i = 0; i < N; i++) {
		for (int j = W; j >= wei[i]; j--) {
			dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
		}
	}
	
	return *max_element(dp, dp + W + 1);
}	
}

namespace Large {
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
}

namespace WA {
const int MAXK = 25;
const int MAXW = 1000005;

int K, W, dp[2][MAXW], wei[MAXK];
vector<int> item[MAXK], pref[MAXK];

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
	
	/* Do WA stuff. */
	for (int i = 1; i <= K; i++) {
		int w = wei[i];
		int *pre = dp[(i - 1) % 2], *cur = dp[i % 2];
		for (int j = 0; j <= W; j++) {
			cur[j] = 0;
			const int B = 300;
			for (int take = 0; take <= min(B, (int) item[i].size()) && w * take <= j; take++) {
				cur[j] = max(cur[j], pre[j - take * w] + pref[i][take]);
			}
			if (item[i].size() > B && j >= (B + 1) * w) {
				for (int k = 0; k < B; k++) {
//					cout <<"At " <<j / w <<' ' <<item[i].size()<<'\n';
//					cout << "MOD " << min((int)item[i].size(), j / w) - 200 <<'\n';
					assert((min((int)item[i].size(), j / w) - B) > 0);
					int take = rand() % (min((int)item[i].size(), j / w) - B) + B + 1;
//					cout << "Probe " << take <<'\n';
					cur[j] = max(cur[j], pre[j - take * w] + pref[i][take]);
				}
			}
		}
	}
	
	return *max_element(dp[K % 2], dp[K % 2] + W + 1);
}
}

const int MAXK = 25;
const int MAXW = 1000005;
const int MAXN = 1000005;
int N, K, W, wei[MAXK], p[MAXN], t[MAXN];
vector<int> item[MAXK];
mt19937 rng(time(NULL));

void rand_gen() {
	for (int i = 1; i <= K; i++) {
		if (rng() % 100 == 0 || W < 10) {
			wei[i] = rng() % W + 1;
		}
		else {
			wei[i] = rng() % min(W, 100) + 1;
		}
	}
}

int main() {
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);

	ofstream fout, fans;
	fout.open("in.in");
	fans.open("out.ans");

	int range = 1000;
	while (true) {
		W = rng() % range + 1, N = rng() % range + 1, K = rng() % 20 + 1;
		
		rand_gen();
		for (int i = 1; i <= K; i++) {
			item[i].clear();
		}
		for (int i = 0; i < N; i++) {
			p[i] = rng() % 1000 + 1, t[i] = rng() % K + 1;
			item[t[i]].push_back(p[i]);
		}
		
//		cout << "Go " << N << " " << W << " " << K << '\n';
		int ans1 = -1, ans2 = -1, wa = -1;
		ans1 = Small::run(K, W, wei, item);
		ans2 = Large::run(K, W, wei, item);
		wa = WA::run(K, W, wei, item);
//		cout << ans1 << " " << ans2 << " " <<wa <<'\n';
		
//		cout << "Get " << ans1 << " " << ans2 << '\n';
		if (ans1 != -1) assert(ans1 == ans2);
//		if (wa != -1) assert(wa == ans2);

		
		if (wa != ans2) {
			fout << N << " " << W << " " << K << '\n';
			for (int i = 1; i <= K; i++) {
				fout << wei[i] << " \n"[i == K];
			}
			for (int i = 0; i < N; i++) {
				fout << p[i] << " " << t[i] << '\n';
			}
			
			fans << ans2 << "\n";
			break;
		}
	}
	
	fout.close();
	fans.close();
}
