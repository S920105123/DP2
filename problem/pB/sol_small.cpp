#include <iostream>
#include <vector>
#include <set>
#define LL long long
using namespace std;
const int MOD = 1000000007;
const int MAXN = 20;

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
        cout << "Get:";
		for (int x : v) {
            cout << " " << x;
			sum = sum + x;
		}
        cout << '\n';
	}

    return sum;
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
    	for (int i = 0; i < n; i++) {
    		cin >> a[i];
    	}
    	cout << run(n, a) << '\n';
    }

	return 0;
}
