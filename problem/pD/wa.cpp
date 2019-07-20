#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include <cassert>
#define LL long long
#define PII pair<int, int>
using namespace std;
const int MAXK = 25;
const int MAXW = 100005;

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
		pref[i].resize(item[i].size() + 1);
		for (int j = 0; j < item[i].size(); j++) {
			pref[i][j + 1] = pref[i][j] + item[i][j];
		}
	}
	
	/* Do WA stuff. */
	for (int i = 1; i <= K; i++) {
		int w = wei[i];
		int *pre = dp[(i - 1) % 2], *cur = dp[i % 2];
		for (int j = 0; j <= W; j++) {
			const int B = 500;
			cur[j] = 0;
			for (int take = 0; take <= min(B, (int) item[i].size()) && w * take <= j; take++) {
//				cout << "Take " << " " << B << " " << item[i].size() << " " << take << '\n';
				cur[j] = max(cur[j], pre[j - take * w] + pref[i][take]);
			}
			if (item[i].size() > B && j >= (B + 1) * w) {
				for (int k = 0; k < B; k++) {
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

int _N, _K, _W, _wei[MAXK];
vector<int> _item[MAXK];

int main() {
//	ios_base::sync_with_stdio(0); cin.tie(0);
	
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
}
