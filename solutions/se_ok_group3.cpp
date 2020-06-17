#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            a[p] = x;
        } else {
            int l, r, m;
            cin >> m >> l >> r;
            --l;
            int ans = 0;
            for (int i = l; i < r; ++i) {
                if (a[i] < m) {
                    ++ans;
                }
            }
            ans = r - l - ans * 2;
            if (ans <= 0) {
                ans = 0;
            }
            cout << ans << "\n";
        }
    }
}