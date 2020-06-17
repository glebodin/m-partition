#pragma GCC target("avx,avx2")

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;

const int N = 2e5, B = 32;

const int K = 1 << 15;

int a[N], tmp[K * 2];

alignas(32) int16_t comp[N];

int get(int l, int r, int16_t m) {
    int ans = 0;
    for (int i = r - (r - l) % B; i < r; ++i) {
        if (comp[i] < m) {
            ++ans;
        }
    }
    __m256i mm = _mm256_set1_epi16(m);
    __m256i ansm = _mm256_setzero_si256();
    for (int i = l; i + B <= r; i += B) {
        __m256i b0 = _mm256_load_si256(reinterpret_cast<__m256i *>(comp + i));
        __m256i b1 = _mm256_load_si256(reinterpret_cast<__m256i *>(comp + i + 16));
        b0 = _mm256_cmpgt_epi16(mm, b0);
        b1 = _mm256_cmpgt_epi16(mm, b1);
        ansm = _mm256_sub_epi16(ansm, b0);
        ansm = _mm256_sub_epi16(ansm, b1);
    }
    ans += (uint16_t) _mm256_extract_epi16(ansm, 0);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 1);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 2);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 3);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 4);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 5);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 6);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 7);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 8);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 9);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 10);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 11);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 12);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 13);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 14);
    ans += (uint16_t) _mm256_extract_epi16(ansm, 15);
    return ans;
}

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
    vector<array<int, 4>> qs(q);
    for (auto &x : qs) {
        cin >> x[0];
        if (x[0] == 2) {
            cin >> x[3] >> x[1] >> x[2];
        } else {
            cin >> x[1] >> x[3];
        }
        x[1]--;
    }
    vector<int> ans(q);
    for (int i = 0; i < n; i += K) {
        for (int j = 0; j < q; j += K) {
            for (int j = i; j < min(n, i + K); ++j) {
                tmp[j - i] = a[j];
            }
            for (int k = j; k < min(j + K, q); ++k) {
                tmp[K + k - j] = qs[k][3];
            }
            sort(tmp, tmp + K * 2);
            for (int k = i; k < min(i + K, n); ++k) {
                comp[k] = lower_bound(tmp, tmp + K * 2, a[k]) - tmp - K;
            }
            for (int k = j; k < min(j + K, q); ++k) {
                if (qs[k][0] == 1 && qs[k][1] >= i && qs[k][1] < i + K) {
                    a[qs[k][1]] = qs[k][3];
                    comp[qs[k][1]] = lower_bound(tmp, tmp + K * 2, qs[k][3]) - tmp - K;
                } else if (qs[k][0] == 2 && qs[k][1] < i + K && qs[k][2] > i) {
                    ans[k] += get(max(qs[k][1], i), min(qs[k][2], i + K),
                        lower_bound(tmp, tmp + K * 2, qs[k][3]) - tmp - K);
                }
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (qs[i][0] == 2) {
            ans[i] = qs[i][2] - qs[i][1] - ans[i] * 2;
            if (ans[i] <= 0) {
                ans[i] = 0;
            }
            cout << ans[i] << "\n";
        }
    }
}