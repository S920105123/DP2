#include <iostream>
#include <vector>
#include <set>
#define LL long long
using namespace std;
const int MOD = 1000000007;
const int MAXN = 1005;

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
