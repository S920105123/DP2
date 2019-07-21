#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#define LL long long
#define PII pair<int, int>
const int MAXK = 25;
const int MAXW = 1005;
const int MAXN = 1005;
using namespace std;

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
}
