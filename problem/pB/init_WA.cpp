#include <iostream>
#include <vector>
#include <set>
#define LL long long
using namespace std;
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
        nxt[i] = n;
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

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	
    while (cin >> n) {
    	for (int i = 0; i < n; i++) {
    		cin >> a[i];
    	}
    	cout << run(n, a) << '\n';
    }

	return 0;
}
