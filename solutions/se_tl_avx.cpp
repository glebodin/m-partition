#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

const int N = 2e5, B = 16;

int a[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    while (q--) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            a[p] = x;
        } else {
            int l, r, m;
            cin >> m >> l >> r;
            --l;
            int ans = 0;
            for (int i = r - (r - l) % B; i < r; ++i) {
                if (a[i] < m) {
                    ++ans;
                }
            }
            __m256i mm = _mm256_set1_epi32(m);
            __m256i ansm = _mm256_set1_epi32(0);
            for (int i = l; i + B <= r; i += B) {
                __m256i b0 = _mm256_lddqu_si256(reinterpret_cast<__m256i *>(a + i));
                __m256i b1 = _mm256_lddqu_si256(reinterpret_cast<__m256i *>(a + i + 8));
                b0 = _mm256_cmpgt_epi32(mm, b0);
                b1 = _mm256_cmpgt_epi32(mm, b1);
                ansm = _mm256_sub_epi32(ansm, b0);
                ansm = _mm256_sub_epi32(ansm, b1);
            }
            ans += _mm256_extract_epi32(ansm, 0);
            ans += _mm256_extract_epi32(ansm, 1);
            ans += _mm256_extract_epi32(ansm, 2);
            ans += _mm256_extract_epi32(ansm, 3);
            ans += _mm256_extract_epi32(ansm, 4);
            ans += _mm256_extract_epi32(ansm, 5);
            ans += _mm256_extract_epi32(ansm, 6);
            ans += _mm256_extract_epi32(ansm, 7);
            ans = r - l - ans * 2;
            if (ans <= 0) {
                ans = 0;
            }
            cout << ans << "\n";
        }
    }
}