#include <bits/stdc++.h>
#include "testlib.h"

using namespace std;
const int MAXN[6] = {5, 100, 10000, (int)2e5, (int)2e5, (int)2e5};
int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int group = atoi(validator.group().c_str());
    int maxn = MAXN[group - 1];
    int n = inf.readInt(1, maxn, "n");
    inf.readEoln();
    int a[n];
    for (int i = 0; i < n; i++) {
        inf.readInt(1, (int)1e9, "a[i]");
        if (i != n - 1) {
            inf.readSpace();
        }
    }
    inf.readEoln();
    int q = inf.readInt(1, maxn, "q");
    inf.readEoln();
    int lastm = -1;
    while (q--) {
        int t = inf.readInt(1, 2, "t");
        ensuref(!(group == 5 && t == 1), "wrong type for group 5");
        inf.readSpace();
        if (t == 1) {
            int ind = inf.readInt(1, n, "ind");
            inf.readSpace();
            int x = inf.readInt(1, (int)1e9, "x");
        }
        else {
            int m = inf.readInt(1, (int)1e9, "m");
            inf.readSpace();
            ensuref(!(group == 4 && lastm != -1 && lastm != m), "two or more different m");
            lastm = m;
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(l, n, "r");
        }
        inf.readEoln();
    }
    inf.readEof();
}
