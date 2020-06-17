#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("avx2")

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <bitset>
#include <sstream>
#include <deque>
#include <queue>
#include <random>
#include <cassert>

using namespace std;

#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define FIXED cout << fixed << setprecision(12)
#define RANDOM srand(94385)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define graph vector<vector<int>>
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define f first
#define s second
#define hashmap unordered_map
#define hashset unordered_set
#define eps 1e-9
#define mod 1000000007
#define inf 3000000000000000007ll
#define sz(a) signed(a.size())
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

template<class T, class U> inline void checkmin(T &x, U y) { if (y < x) x = y; }
template<class T, class U> inline void checkmax(T &x, U y) { if (y > x) x = y; }
template<class T, class U> inline bool ifmax(T &x, U y) { if (y > x) return x = y, true; return false; }
template<class T, class U> inline bool ifmin(T &x, U y) { if (y < x) return x = y, true; return false; }
template<class T> inline void sort(T &a) { sort(all(a)); }
template<class T> inline void rsort(T &a) { sort(rall(a)); }
template<class T> inline void reverse(T &a) { reverse(all(a)); }
template<class T, class U> inline istream& operator>>(istream& str, pair<T, U> &p) { return str >> p.f >> p.s; }
template<class T> inline istream& operator>>(istream& str, vector<T> &a) { for (auto &i : a) str >> i; return str; }
template<class T> inline T sorted(T a) { sort(a); return a; }

typedef int pnode;

mt19937 gen;

struct node {
    int cnt;
    int p;
    pnode l, r;
    int k;
    node() : k(0), cnt(0), p(0), l(0), r(0) {}
    node(int x) : k(x), cnt(1), p(gen()), l(0), r(0) {}
} t[int((2e5 + 2e5) * 18)];
int currptr = 0;

pnode newnode(int x) {
    t[++currptr] = x;
    return currptr;
}

inline int getcnt(pnode v) {
    return t[v].cnt;
}

inline void upd(pnode v) {
    if (v) t[v].cnt = getcnt(t[v].l) + getcnt(t[v].r) + 1;
}

inline pnode merge(pnode l, pnode r) {
    pnode root = 0;
    pnode *pr = &root;
    while (l && r) {
        if (t[l].p > t[r].p) {
            t[l].cnt += t[r].cnt;
            *pr = l;
            pr = &t[l].r;
            l = *pr;
        } else {
            t[r].cnt += t[l].cnt;
            *pr = r;
            pr = &t[r].l;
            r = *pr;
        }
    }
    *pr = l ? l : r;
    return root;
}

pnode cuts[100];
int currcut = -1;

inline void splitval(pnode n, int k, pnode &lans, pnode &rans) {
    pnode l = 0, r = 0;
    t[0].l = t[0].r = 0;
    while (n) {
        cuts[++currcut] = n;
        if (t[n].k < k) {
            t[l].r = n;
            l = n;
            n = t[n].r;
            t[l].r = 0;
        } else {
            t[r].l = n;
            r = n;
            n = t[n].l;
            t[r].l = 0;
        }
    }
    while (currcut >= 0) upd(cuts[currcut--]);
    lans = t[0].r, rans = t[0].l;
}


inline void splitind(pnode n, int ind, pnode &lans, pnode &rans) {
    pnode l = 0, r = 0;
    t[0].l = t[0].r = 0;
    while (n) {
        cuts[++currcut] = n;
        if (t[t[n].l].cnt < ind) {
            ind -= t[t[n].l].cnt + 1;
            t[l].r = n;
            l = n;
            n = t[n].r;
            t[l].r = 0;
        } else {
            t[r].l = n;
            r = n;
            n = t[n].l;
            t[r].l = 0;
        }
    }
    while (currcut >= 0) upd(cuts[currcut--]);
    lans = t[0].r, rans = t[0].l;
}

void insert(pnode &t, int x) {
    static pnode r;
    splitval(t, x, t, r);
    t = merge(t, newnode(x));
    t = merge(t, r);
}

void eraseone(pnode &t, int x) {
    static pnode mid, r;
    splitval(t, x, t, r);
    splitind(r, 1, mid, r);
    t = merge(t, r);
}

int getless(pnode v, int m) {
    int ans = 0;
    while (v) {
        if (t[v].k >= m) v = t[v].l;
        else ans += getcnt(t[v].l) + 1, v = t[v].r;
    }
    return ans;
}

void makeheap(pnode n) {
    if (!n) return;
    pnode mx = n;
    if (t[n].l && t[mx].p < t[t[n].l].p) mx = t[n].l;
    if (t[n].r && t[mx].p < t[t[n].r].p) mx = t[n].r;
    if (mx != n) {
        swap(t[n].p, t[mx].p);
        makeheap(mx);
    }
}

pnode buildtreap(vector<int> &val, int l, int r) {
    if (r < l) return 0;
    int mid = l + r >> 1;
    pnode ans = newnode(val[mid]);
    t[ans].l = buildtreap(val, l, mid - 1);
    t[ans].r = buildtreap(val, mid + 1, r);
    makeheap(ans);
    upd(ans);
    return ans;
}

struct Tree {
    static const int n = 1 << 18;
    pnode t[2 * n + 1];
    void build(vector<int> a) {
        for (int j = n, p = n << 1, len = 1; j > 0; p = j, j >>= 1, len <<= 1) {
            for (int i = j, from = 0; i < p; ++i, from += len) {
                int to = min(sz(a), from + len);
                int mid = min(from + (len >> 1), to);
                inplace_merge(a.begin() + from, a.begin() + mid, a.begin() + to);
                --to;
                t[i] = buildtreap(a, from, to);
            }
        }
    }
    void add(int r, int x) {
        r += n;
        for (; r > 0; r >>= 1)
            insert(t[r], x);
    }
    void del(int r, int x) {
        r += n;
        for (; r > 0; r >>= 1)
            eraseone(t[r], x);
    }
    int get(int l, int r, int m) { // [l, r] < m
        l += n;
        r += n + 1;
        int ans = 0;
        while (l < r) {
            if (l & 1) ans += getless(t[l++], m);
            if (r & 1) ans += getless(t[--r], m);
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
} tr;

struct query {
    int tp, x, l, r;
    friend istream& operator>>(istream& str, query &q) {
        str >> q.tp;
        if (q.tp == 1) {
            str >> q.l >> q.x;
            --q.l;
        } else {
            str >> q.x >> q.l >> q.r;
            --q.l, --q.r;
        }
        return str;
    }
};

signed main() {
    FAST; FIXED; RANDOM;
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    tr.build(a);
    int q;
    cin >> q;
    vector<query> que(q);
    cin >> que;
    for (int i = 0; i < q; ++i) {
        if (que[i].tp == 1) {
            int ind = que[i].l;
            tr.del(ind, a[ind]);
            a[ind] = que[i].x;
            tr.add(ind, a[ind]);
        } else {
            int l = que[i].l, r = que[i].r, m = que[i].x;
            int cntless = tr.get(l, r, m);
            int cntmore = (r - l + 1) - cntless;
            cout << max(0, cntmore - cntless) << '\n';
        }
    }
    return 0;
}