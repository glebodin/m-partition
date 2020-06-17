#pragma GCC target("avx2")
#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i : a) cin >> i;
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int i, x;
            cin >> i >> x;
            a[i - 1] = x;
        } else {
            int m, l, r;
            cin >> m >> l >> r;
            int cl = 0;
            for (int i = l - 1; i < r; ++i)
                cl += a[i] < m;
            cout << max(0, r - l + 1 - 2 * cl) << '\n';
        }
    }
    return 0;
}