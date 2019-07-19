#include <bits/stdc++.h>
#define LL long long
#define PII pair<int, int>
using namespace std;

namespace Large {
const int MAXN = 100005;
const int INF = (int) 1e9 + 5;
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
};

namespace Medium {
const int MAXN = 1005;

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
}

const int MAXN = 100005;
int N, a[MAXN];
mt19937 rng(time(NULL));

void rand_inc() {
	for (int i = 0; i < N; i++) {
		int dice = rng() % 10;
		if (dice == 0) {
			a[i] = a[i - 1] + 2;
		}
		else if (dice == 1) {
			a[i] = a[i - 1];
		}
		else {
			a[i] = a[i - 1] + 1;
		}
	}	
//	cout << "Get " << a[0] << " " << a[N - 1] << '\n';
}

void rand_partitioned_inc() {
	for (int i = 0; i < N; i++) {
		if (rng() % 10 == 0) {
			a[i] = a[i - 1] + rng() % 10;
		}
		else {
			int dice = rng() % 10;
			if (dice == 0) {
				a[i] = a[i - 1] + 2;
			}
			else if (dice == 1) {
				a[i] = a[i - 1];
			}
			else {
				a[i] = a[i - 1] + 1;
			}
		}
	}	
//	cout << "Get " << a[0] << " " << a[N - 1] << '\n';
}

void rand_weak_inc() {
//	cout << "B";
	int base = 0;
	for (int i = 0; i < N; i++) {
		if (rng() % 100 == 0) {
			a[i] = a[i - 1] + rng() % 100;
		}
		else {
			int dice = rng() % 6;
			if (dice == 0) {
				a[i] = a[i - 1] + 2;
			}
			else if (dice == 1) {
				a[i] = a[i - 1];
			}
			else if (dice == 2) {
				a[i] = a[i - 1] - 1;
			}
			else {
				a[i] = a[i - 1] + 1;
			}
		}
	}	
	if (rng() % 3) {
		for (int i = 0; i < N / 50; i++) {
			int j = rng() % N, k = rng() % 10;
			if (j + k <= N) {
				random_shuffle(a + j, a + j + k);
			}
		}
	}
}

void rand_gen() {
//	cout << "A";
	if (rng() % 2) {
		for (int i = 0; i < N; i++) {
			a[i] = rng() % 1000000;
		}
	}
	else {
		for (int i = 0; i < N; i++) {
			a[i] = rng() % (N + 5);
		}
	}
}

int main() {
//	ios_base::sync_with_stdio(0);
//	cin.tie(0);

	ofstream fout, fans;
	fout.open("in.in");
	fans.open("out.ans");
	
	int turn = 0;
	while (true) {
		N = rng() % 100000 + 1;
		if (turn % 4 == 0) rand_weak_inc();
		else if (turn % 4 == 1) rand_gen();
		else if (turn % 4 == 2) rand_inc();
		else rand_partitioned_inc();
		turn++;
		
//		cout << "Go test " << N << '\n';
//		for (int i = 0; i < N; i++) {
//			cout << a[i] << " \n"[i == N - 1];
//		}
//		PII *res1 = Medium::run(N, a);
		PII *res2 = Large::run(N, a);
		
		int mx = 0;
		set<PII> ps;
		for (int i = 0; i < N; i++) {
//			assert(res1[i] == res2[i]);
			ps.insert(res2[i]);
			mx = max(mx, res2[i].second);
		}
		
		if (ps.size() > 200) {
			cout << N << " " << ps.size() << ' ' << mx << " " << turn % 4 << '\n';
			if (mx <= 1 || ps.size() < 250) continue;
			fout << N << '\n';
			for (int i = 0; i < N; i++) {
				fout << a[i] << " \n"[i == N - 1];
			}
			for (int i = 0; i < N; i++) {
				fans << res2[i].first << ' ' << res2[i].second << '\n';
			}
			break;
		}
//		for (int i = 0; i < N; i++) {
//			cout << a[i] << ' ';
//		}
//		for (int i = 0; i < N; i++) {
//			cout << res1[i].first << " " << res2[i].first << '\n';
//		}
//		cout << '\n';
		
//		break;
	}
}
