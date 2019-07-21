#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
#include <cassert>
#define LL long long
#define PII pair<int, int>
const int MAXN = 100005;
const int INF = (int) 1e9 + 5;
using namespace std;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> N;
	assert(N <= 100000);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		assert(0 <= a[i] && a[i] < 1000000);
	}
	
	PII *output = run(N, a);
	for (int i = 0; i < N; i++) {
		cout << output[i].first << " " <<output[i].second << '\n';
	}
}
