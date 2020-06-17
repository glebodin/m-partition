#include <bits/stdc++.h>

using namespace std;

const size_t MEM = 300e6;

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
        unsigned sz = 1, y;
        T x;
        Node(T x): y(rnd()), x(x) {}
        void upd() {
            sz = 1;
            if (l) {
                sz += l->sz;
            }
            if (r) {
                sz += r->sz;
            }
        }
        static Node* insert(Node *n, Node *nn) {
            if (!n) {
                return nn;
            } else if (nn->y > n->y) {
                split(n, nn->x, nn->l, nn->r);
                nn->upd();
                return nn;
            } else if (n->x < nn->x) {
                n->r = insert(n->r, nn);
            } else {
                n->l = insert(n->l, nn);
            }
            n->upd();
            return n;
        }
        static Node *erase(Node *n, const T &x) {
            if (n->x == x) {
                return merge(n->l, n->r);
            } else if (n->x < x) {
                n->r = erase(n->r, x);
            } else {
                n->l = erase(n->l, x);
            }
            n->upd();
            return n;
        }
        Node *cpy() const {
            Node *ans = new Node(*this);
            if (l) {
                ans->l = l->cpy();
            }
            if (r) {
                ans->r = r->cpy();
            }
            return ans;
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
        if (l->y > r->y) {
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
        root = Node::insert(root, new Node(x));
    }
    void erase(T x) {
        root = Node::erase(root, x);
    }
    void operator=(const Treap &other) {
        root = other.root->cpy();
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
    vector<Treap<pair<int, int>>> a;
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
            a[v].add_tree(a[v * 2 + 2].root);
        }
    }
    int get(int ql, int qr, int m, int v = 0, int l = 0, int r = -1) {
        if (r == -1) {
            r = n;
        }
        if (l >= qr || ql >= r) {
            return 0;
        } else if (l >= ql && r <= qr) {
            return a[v].count({m, 0});
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