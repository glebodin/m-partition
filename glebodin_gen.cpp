#include <iostream>
#include "testlib.h"

using namespace std;
const int maxx = 1e9;
const int N[6] = {5, 100, 10000, (int)2e5, (int)2e5, (int)2e5};
using namespace std;

//usage glebodin_gen n q group type
//n = -1 or q = -1 mean n and q belongs to this group and will be random
//type = 0(random test)
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int q = atoi(argv[2]);
    int group = atoi(argv[3]);
    int type = atoi(argv[4]);
    if (n == -1) {
        n = rnd.next(1, N[group - 1]);
    }
    if (q == -1) {
        q = rnd.next(1, N[group - 1]);
    }
    int M = rnd.next(1, n);
    cout << n << "\n";
    int a[n];
    for (int i = 0; i < n; i++) {
        if (i) {
            cout << " ";
        }
        a[i] = rnd.next(1, maxx);
        cout << a[i];
    }
    cout << "\n" << q << "\n";
    for (int i = 0; i < q; i++) {
        int t = 2;
        if (group != 5) {
            t = rnd.next(1, 2);
        }
        if (t == 2) {
            int l = rnd.next(1, n), r = rnd.next(1, n), m;
            if (l > r) {
                swap(l, r);
            }
            if (type == 0) {
                m = rnd.next(1, maxx);
            }
            if (group == 4) {
                m = M;
            }
            cout << t << " " << m << " " << l << " " << r << "\n";
        } 
        else {
            int ind = rnd.next(1, n), r = rnd.next(1, n);
            cout << t << " " << ind << " " << r << "\n";
        }
    }
    return 0;
}
