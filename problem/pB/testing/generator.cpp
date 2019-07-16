#include <bits/stdc++.h>
#define PII pair<int, int>
#define LL long long
using namespace std;

namespace Small {
const int MAXN = 20;
const int MOD = 1000000007;

int n, a[MAXN];

bool is_subsequence(const vector<int> &v) {
	int ptr = 0;
	for (int i = 0; i < v.size(); i++) {
		while (ptr < n && v[i] != a[ptr]) {
			ptr++;
		}
		if (ptr == n) {
			return false;
		}
		ptr++;
	}
	return true;
}

int run(int _n, int* _a) {
    /* Copy the parameters, this is for convenience of testing. */
    n = _n;
    copy(_a, _a + n, a);

    /* Enumerate all posiible subsequence, and then put valid ones into set */
    set<vector<int>> all;
	for (int m = 0; m < (1 << n); m++) {
		vector<int> v;
		for (int i = 0; i < n; i++) {
			if (m >> i & 1) {
				v.push_back(a[i]);
			}
		}

		if (!is_subsequence(v)) {
			continue;
		}

		bool ok = true;
		for (int i = 0; i < n; i++) {
			v.push_back(a[i]);
			if (is_subsequence(v)) {
				ok = false;
				break;
			}
			v.pop_back();
		}

		if (ok) {
			all.insert(v);
		}
	}

	int sum = 0;
	for (const vector<int> &v : all) {
		for (int x : v) {
			sum = (sum + x) % MOD;
		}
	}

    return sum;
}
}; // End of namespace Small

namespace Medium {
const int MOD = 1000000007;
const int MAXN = 10005;

int n, a[MAXN], dp1[MAXN], dp2[MAXN];

int run(int _n, int* _a) {
    /* Copy the parameters, this is for convenience of testing. */
    n = _n;
    copy(_a, _a + n, a);
    fill(dp1, dp1 + n + 1, 0);
    fill(dp2, dp2 + n + 1, 0);

    /* dp1: count of diff. perfect subsequece, dp2: sum of diff. perfect subsequece.
     * Enumerate the first item in the subsequence, and do naively.
     */

    dp1[n] = 1, dp2[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        /* Use set here is to validate large testcase. */
        set<int> occ;
        for (int j = i; j < n; j++) {
            if (occ.find(a[j]) == occ.end()) {
                occ.insert(a[j]);
                dp1[i] = (dp1[i] + dp1[j + 1]) % MOD;
                dp2[i] = (dp2[i] + (LL) a[j] * dp1[j + 1] + dp2[j + 1]) % MOD;
            }
        }
    }

    return dp2[0];
}
}; // End of namespace Medium

namespace Large {
const int MOD = 1000000007;
const int MAXN = 1000005;

int n, a[MAXN], dp1[MAXN], dp2[MAXN], nxt[MAXN];

LL run(int _n, int* _a) {
    /* Copy the parameters, this is for convenience of testing. */
    n = _n;
    copy(_a, _a + n, a);
    fill(dp1, dp1 + n + 2, 0);
    fill(dp2, dp2 + n + 2, 0);
    for (int i = 0; i < n; i++) {
        nxt[a[i]] = n;
    }

    /* dp1: count of diff. perfect subsequece, dp2: sum of diff. perfect subsequece. */
    LL num = 0, sum = 0;
    dp1[n] = 1, dp2[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        num = (num - dp1[nxt[a[i]] + 1]) % MOD;
        sum = (sum - (LL) a[i] * dp1[nxt[a[i]] + 1] - dp2[nxt[a[i]] + 1]) % MOD;
        nxt[a[i]] = i;
        num = (num + dp1[nxt[a[i]] + 1]) % MOD;
        sum = (sum + (LL) a[i] * dp1[nxt[a[i]] + 1] + dp2[nxt[a[i]] + 1]) % MOD;

        num = (num + MOD) % MOD;
        sum = (sum + MOD) % MOD;
        dp1[i] = num;
        dp2[i] = sum;
    }

    return dp2[0];
}

}; // End of namespace Large

const int MAXN = 1000005;
int n, a[MAXN];

int main() {
//	ios_base::sync_with_stdio(0); cin.tie(0);
	
	int range_T, range_N = 12, range_A = 26;
	mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
	while (true) {
		n = rng() % range_N + 1;
		for (int i = 0; i < n; i++) {
			a[i] = rng() % range_A;
		}
		
		int ans1 = -1, ans2 = -1, ans3 = -1;
		ans1 = Small::run(n, a);
		ans2 = Medium::run(n, a);
		ans3 = Large::run(n, a);
//		cout << n << " get " << ans1 << " " << ans2 << " " << ans3 << '\n';

		if (ans1 != -1) assert(ans1 == ans2);
		if (ans2 != -1) assert(ans2 == ans3);
		assert(0 <= ans3 && ans3 < Small::MOD);
	}
	
	return 0;
}
