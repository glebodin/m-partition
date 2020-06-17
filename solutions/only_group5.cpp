#include <bits/stdc++.h>

using namespace std;

struct Segtree {
    int n;
    vector<vector<int>> a;
    Segtree(const vector<int> &arr): n(arr.size()), a(n * 4) {
        build(arr, 0, 0, n);
    }
    void build(const vector<int> &arr, int v, int l, int r) {
        if (r - l == 1) {
            a[v].push_back(arr[l]);
        } else {
            int c = (l + r) / 2;
            build(arr, v * 2 + 1, l, c);
            build(arr, v * 2 + 2, c, r);
            merge(a[v * 2 + 1].begin(), a[v * 2 + 1].end(),
                a[v * 2 + 2].begin(), a[v * 2 + 2].end(),
                back_inserter(a[v]));
        }
    }
    int get(int ql, int qr, int m, int v = 0, int l = 0, int r = -1) {
        if (r == -1) {
            r = n;
        }
        if (l >= qr || ql >= r) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return lower_bound(a[v].begin(), a[v].end(), m) - a[v].begin();
        }
        int c = (l + r) / 2;
        return get(ql, qr, m, v * 2 + 1, l, c) + get(ql, qr, m, v * 2 + 2, c, r);
    }
};

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
    Segtree t(a);
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            return 0;
            --p;
            a[p] = x;
            t = Segtree(a);
        } else {
            int l, r, m;
            cin >> m >> l >> r;
            --l;
            int ans = t.get(l, r, m);
            ans = r - l - ans * 2;
            if (ans <= 0) {
                ans = 0;
            }
            cout << ans << "\n";
        }
    }
}