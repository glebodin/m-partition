#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 200;

bool can[N][N];
int n, q, a[N], dp[N];

void solve(int m, int l, int r) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			can[i][j] = 0;
		}
	}
	for (int i = 1; i <= n; i++) {
    	int cnt = 0;
    	for (int j = i; j <= n; j++) {
    		if (a[j] >= m) {
        		cnt++;
    		}
    		int sz = j - i + 1;
    		int mid = sz / 2;
    		int need = sz - mid;
    		if (sz % 2 == 0) {
    			need++;
    		}
    		if (cnt >= need) {
    			can[i][j] = 1;
    		}
    	}
    }
    dp[l - 1] = 0;
    for(int i = l; i <= r; i++){
		dp[i] = -1e9;
		for(int j = l - 1; j < i; j++){
			if(can[j + 1][i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
    cout << max(dp[r], 0) << "\n";
}

int main() {
	ios_base::sync_with_stdio(0);
	cin >> n;
    if (n > 150) {
        return 0;
    }
	for (int i = 1; i <= n; i++) {
    	cin >> a[i];
    }
    cin >> q;
    while (q--) {
    	int t;
    	cin >> t;
    	if (t == 1) {
    		int ind, x;
    		cin >> ind >> x;
    		a[ind] = x;
    	}
    	else {
    		int m, l, r;
    		cin >> m >> l >> r;
    		solve(m, l, r);
    	}
    }
    return 0;
}