#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
#include <cassert>
#define LL long long
#define PII pair<int, int>
const int MAXN = 1000005;
const int INF = (int) 1e9 + 5;
using namespace std;

struct Segment_tree {
	int minv[4*MAXN], add[4*MAXN];
	
	void init(int l, int r, int idx) {
		add[idx] = 0;
		minv[idx] = INF;
		if (l == r) {
			add[idx] = INF;
			return;
		}
		int m = (l + r) >> 1;
		init(l, m, idx << 1);
		init(m + 1, r, idx << 1 | 1);
	}
	
	void range_add(int ql, int qr, int val, int l, int r, int idx) {
		if (ql <= l && r <= qr) {
			add[idx] += val;
			minv[idx] += val;
			return;
		}
		int m = (l + r) >> 1;
		if (ql <= m) range_add(ql, qr, val, l, m, idx << 1);
		if (qr >  m) range_add(ql, qr, val, m + 1, r, idx << 1 | 1);
		minv[idx] = min(minv[idx << 1], minv[idx << 1 | 1]) + add[idx];
	}
	
	int search_for(int bound, int added, int l, int r, int idx) {
		if (l == r) {
			assert(minv[idx] + added <= bound);
			return l;
		}
		
		added += add[idx];
		int left_mi = minv[idx << 1] + added, right_mi = minv[idx << 1 | 1] + added, m = (l + r) >> 1;
//		cout << "Tree " << bound << " " << l << " " << r << " " << left_mi << " " << right_mi << '\n';
		if (right_mi <= bound) {
			return search_for(bound, added, m + 1, r, idx << 1 | 1);
		}
		else {
			assert(left_mi <= bound);
			return search_for(bound, added, l, m, idx << 1);
		}
	}
} tree;

int N, a[MAXN], longest[MAXN];
PII ans[MAXN];
vector<int> ed[MAXN], stk1, stk2;

PII* run(int _N, int *_a) {
	/* Copy the parameters for convenience of testing */
	N = _N;
	stk1.clear();
	stk2.clear();
	tree.init(1, N, 1);
	for (int i = N; i >= 1; i--) {
		ed[i].clear();
		a[i] = _a[i - 1];
	}
	
	/* Put everything into data structure, and mix them up. */
	for (int i = N; i >= 1; i--) {
//		cout << "At " << i << " " << a[i] << '\n';
		while (!stk1.empty() && a[i] >= a[stk1.back()]) {
			int pos = stk1.back(), rb;
			stk1.pop_back();
			rb = stk1.empty() ? N : stk1.back() - 1;
			tree.range_add(pos, rb, a[i] - a[pos], 1, N, 1);
		}
		stk1.push_back(i);
		while (!stk2.empty() && a[i] <= a[stk2.back()]) {
			int pos = stk2.back(), rb;
			stk2.pop_back();
			rb = stk2.empty() ? N : stk2.back() - 1;
			tree.range_add(pos, rb, -a[i] - (-a[pos]), 1, N, 1);
		}
		stk2.push_back(i);
		tree.range_add(i, i, -INF - i, 1, N, 1);
		
		longest[i] = tree.search_for(1 - i, 0, 1, N, 1) - i + 1;
	}
	
	/* Sweep line */
	map<int, int> sweep;
	for (int i = 1; i <= N; i++) {
		sweep[longest[i]]++;
		ed[i + longest[i]].push_back(longest[i]);
		for (int x : ed[i]) {
			sweep[x]--;
			if (sweep[x] == 0) {
				sweep.erase(sweep.find(x));
			}
		}
		
		ans[i] = *sweep.rbegin();
	}
	
	/* Tada! */
	return ans + 1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N;
	assert(N <= 1000000);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		assert(0 <= a[i]);
		assert(a[i] < 10000000);
	}
	
	PII *output = run(N, a);
	for (int i = 0; i < N; i++) {
		cout << output[i].first << " " <<output[i].second << '\n';
	}
}
