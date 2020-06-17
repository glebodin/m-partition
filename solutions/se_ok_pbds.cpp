#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


const size_t MEM = 512e6;

alignas(8) char buf[MEM];

size_t pos = 0;

void *operator new(size_t n) {
    pos += n;
    return buf + pos - n;
}

void operator delete(void *) {}

mt19937 rnd(42);

template<class T>
struct Treap {
    struct Node {
        Node *l = nullptr, *r = nullptr;
        unsigned sz = 1;
        T x;
        Node(T x): x(x) {}
        void upd() {
            sz = 1;
            if (l) {
                sz += l->sz;
            }
            if (r) {
                sz += r->sz;
            }
        }
    };
    static void split(Node *t, T x, Node *&l, Node *&r) {
        if (!t) {
            l = r = nullptr;
            return;
        }
        if (t->x < x) {
            l = t;
            split(l->r, x, l->r, r);
            l->upd();
        } else {
            r = t;
            split(r->l, x, l, r->l);
            r->upd();
        }
    }
    static Node *merge(Node *l, Node *r) {
        if (!l) {
            return r;
        }
        if  (!r) {
            return l;
        }
        if (rnd() % (l->sz + r->sz) < l->sz) {
            l->r = merge(l->r, r);
            l->upd();
            return l;
        } else {
            r->l = merge(l, r->l);
            r->upd();
            return r;
        }
    }
    Node *root = nullptr;
    int count(T x) {
        Node *l, *r;
        split(root, x, l, r);
        int ans = 0;
        if (l) {
            ans = l->sz;
        }
        root = merge(l, r);
        return ans;
    }
    void insert(T x) {
        Node *l, *r, *nn = new Node(x);
        split(root, x, l, r);
        root = merge(l, merge(nn, r));
    }
    void erase(T x) {
        Node *l, *r;
        split(root, x, l, r);
        Node *n = r;
        if (!n->l) {
            r = n->r;
        } else {
            while (n->l->l) {
                --n->sz;
                n = n->l;
            }
            --n->sz;
            n->l = n->l->r;
        }
        root = merge(l, r);
    }
    void add_tree(Node *n) {
        if (!n) {
            return;
        }
        insert(n->x);
        add_tree(n->l);
        add_tree(n->r);
    }
};

struct Segtree {
    int n;
    vector<ordered_set<pair<int, int>>> a;
    Segtree(const vector<int> &arr): n(arr.size()), a(n * 4) {
        build(arr, 0, 0, n);
    }
    void build(const vector<int> &arr, int v, int l, int r) {
        if (r - l == 1) {
            a[v].insert({arr[l], l});
        } else {
            int c = (l + r) / 2;
            build(arr, v * 2 + 1, l, c);
            build(arr, v * 2 + 2, c, r);
            a[v] = a[v * 2 + 1];
            for (auto x : a[v * 2 + 2])
                a[v].insert(x);
        }
    }
    int get(int ql, int qr, int m, int v = 0, int l = 0, int r = -1) {
        if (r == -1) {
            r = n;
        }
        if (l >= qr || ql >= r) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return a[v].order_of_key({m, 0});
        }
        int c = (l + r) / 2;
        return get(ql, qr, m, v * 2 + 1, l, c) + get(ql, qr, m, v * 2 + 2, c, r);
    }
    void upd(int p, int ox, int nx, int v = 0, int l = 0, int r = -1) {
        if  (r == -1) {
            r = n;
        }
        a[v].erase({ox, p});
        a[v].insert({nx, p});
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
    Segtree t(a);
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            t.upd(p, a[p], x);
            a[p] = x;
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