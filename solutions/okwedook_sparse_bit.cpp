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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct Fenv {
    static const int N = 4e5 + 10;
    gp_hash_table<int, int> fenv;
    void add(int r, int x) {
        for (; r < N; r |= r + 1)
            fenv[r] += x;
    }
    int get(int r) {
        int ans = 0;
        for (; r >= 0; r = (r & r + 1) - 1)
            if (fenv.find(r) != fenv.end())
                ans += fenv[r];
        return ans;
    }
};

vector<int> values;

void addvalues(const vector<int> &a) {
    for (auto i : a) values.pb(i);
}

void addvalue(int x) {
    values.pb(x);
}

void genvalues() {
    sort(values);
    values.resize(unique(all(values)) - values.begin());
}

int getind(int x) {
    return lower_bound(all(values), x) - values.begin();
}

struct Tree {
    static const int n = 1 << 18;
    Fenv t[2 * n + 1];
    void add(int r, int x) {
        r += n;
        for (; r > 0; r >>= 1)
            t[r].add(x, 1);
    }
    void del(int r, int x) {
        r += n;
        for (; r > 0; r >>= 1)
            t[r].add(x, -1);
    }
    int get(int l, int r, int m) { // [l, r] < m
        l += n;
        r += n + 1;
        int ans = 0;
        while (l < r) {
            if (l & 1) ans += t[l++].get(m);
            if (r & 1) ans += t[--r].get(m);
            l >>= 1;
            r >>= 1;
        }
        return ans;
    }
} t;

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
    addvalues(a);
    int q;
    cin >> q;
    vector<query> que(q);
    cin >> que;
    for (auto i : que) addvalue(i.x);
    genvalues();
    for (int i = 0; i < n; ++i)
        t.add(i, getind(a[i]));
    for (int i = 0; i < q; ++i) {
        if (que[i].tp == 1) {
            int ind = que[i].l;
            t.del(ind, getind(a[ind]));
            a[ind] = que[i].x;
            t.add(ind, getind(a[ind]));
        } else {
            int l = que[i].l, r = que[i].r, m = que[i].x;
            int cntless = t.get(l, r, getind(m) - 1);
            int cntmore = (r - l + 1) - cntless;
            cout << max(0, cntmore - cntless) << '\n';
        }
    }
    return 0;
}