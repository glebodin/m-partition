#include <iostream>
#include "testlib.h"

using namespace std;

const int maxx = 1e9;

using namespace std;

//usage se_gen n q l r

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    registerGen(argc, argv, 1);
    int n = atoi(argv[1]);
    int q = atoi(argv[2]);
    int l = atoi(argv[3]);
    int r = atoi(argv[4]);
    if (r < 0) {
        r = n + 1 + r;
    }
    cout << n << "\n";
    for (int i = 0; i < n; ++i) {
        cout << rnd.next(1, maxx);
        if (i < n - 1) {
            cout << " ";
        } else {
            cout << "\n";
        }
    }
    cout << q << "\n";
    for (int i = 0; i < q; ++i) {
        cout << "2 " << rnd.next(1, maxx) << " " << l << " " << r << "\n";
    }
    return 0;
}
