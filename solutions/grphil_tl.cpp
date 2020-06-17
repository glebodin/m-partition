#include <bits/stdc++.h>

using namespace std;

int s[200000];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	int m;
	cin >> m;
	int t, a, b, c, ans;
	for (int i = 0; i < m; i++) {
		cin >> t >> a >> b;
		if (t == 1) {
			s[a - 1] = b;
		} else {
			cin >> c;
			ans = 0;
			for (int i = b - 1; i < c; i++) {
				if (s[i] < a) {
					ans--;
				} else {
					ans++;
				}
			}
			if (ans < 0) {
				ans = 0;
			}
			cout << ans << '\n';
		}
	}
}