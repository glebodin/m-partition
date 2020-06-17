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
            for (int i = 0; i < (1 << (r - l - 1)); ++i) {
                vector<int> b;
                bool f = 1;
                for (int j = 0; j < r - l; ++j) {
                    b.push_back(a[l + j]);
                    if ((i & (1 << j)) || j == r - l - 1) {
                        sort(b.begin(), b.end());
                        int pos = b.size() / 2;
                        if (b.size() % 2 == 0)
                            --pos;
                        if (b[pos] < m) {
                            f = 0;
                            break;
                        }
                        b.clear();
                    }
                }
                if (f) {
                    ans = max(ans, __builtin_popcount(i) + 1);
                }
            }
            cout << ans << "\n";
        }
    }
}