#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
#define LL long long
#define PII pair<int, int>
const int MAXN = 1005;
using namespace std;

int N, a[MAXN], longest[MAXN], maxv[MAXN][MAXN], minv[MAXN][MAXN];
PII ans[MAXN];
vector<int> ed[MAXN];

PII* run(int _N, int *_a) {
	/* Copy the parameters for convenience of testing */
	N = _N;
	for (int i = 0; i < N; i++) {
		ed[i].clear();
		a[i] = _a[i];
	}
	
	/* Enumerate all possible interval */
	for (int i = 0; i < N; i++) {
		maxv[i][i] = minv[i][i] = a[i];
		for (int j = i; j >= 0; j--) {
			if (j != i) {
				maxv[j][i] = max(maxv[j][i - 1], a[i]);
				minv[j][i] = min(minv[j][i - 1], a[i]);
			}
			if (maxv[j][i] - minv[j][i] <= i - j + 1) {
				longest[i] = i - j + 1;
			}
		}
	}
	
	/* Sweepline */
	map<int, int> sweep;
	for (int i = N - 1; i >= 0; i--) {
		sweep[longest[i]]++;
		if (i - longest[i] >= 0) {
			ed[i - longest[i]].push_back(longest[i]);
		}
		for (int x : ed[i]) {
			sweep[x]--;
			if (sweep[x] == 0) {
				sweep.erase(sweep.find(x));
			}
		}
		
		ans[i] = *sweep.rbegin();
	}
	
	return ans;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	
	PII *output = run(N, a);
	for (int i = 0; i < N; i++) {
		cout << output[i].first << " " <<output[i].second << '\n';
	}
}
