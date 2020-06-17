#include <bits/stdc++.h>

using namespace std;

int m;

struct Segtree {
    int n;
    vector<int> a;
    Segtree(const vector<int> &arr): n(arr.size()), a(n * 4) {
        build(arr, 0, 0, n);
    }
    void build(const vector<int> &arr, int v, int l, int r) {
        if (r - l == 1) {
            if (arr[l] < m) {
                a[v] = 1;
            }
        } else {
            int c = (l + r) / 2;
            build(arr, v * 2 + 1, l, c);
            build(arr, v * 2 + 2, c, r);
            a[v] = a[v * 2 + 1] + a[v * 2 + 2];
        }
    }
    int get(int ql, int qr, int v = 0, int l = 0, int r = -1) {
        if (r == -1) {
            r = n;
        }
        if (l >= qr || ql >= r) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return a[v];
        }
        int c = (l + r) / 2;
        return get(ql, qr, v * 2 + 1, l, c) + get(ql, qr, v * 2 + 2, c, r);
    }
    void upd(int p, int ox, int nx, int v = 0, int l = 0, int r = -1) {
        if (r == -1) {
            r = n;
        }
        if (ox < m)
            --a[v];
        if (nx < m)
            ++a[v];
        if (r - l == 1) {
            return;
        }
        int c = (l + r) / 2;
        if (p < c) {
            upd(p, ox, nx, v * 2 + 1, l, c);
        } else {
            upd(p, ox, nx, v * 2 + 2, c, r);
        }
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
    Segtree *t = nullptr;
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            if (t) {
                t->upd(p, a[p], x);
            }
            a[p] = x;
        } else {
            int l, r;
            cin >> m >> l >> r;
            if (!t) {
                t = new Segtree(a);
            }
            --l;
            int ans = t->get(l, r);
            ans = r - l - ans * 2;
            if (ans <= 0) {
                ans = 0;
            }
            cout << ans << "\n";
        }
    }
}