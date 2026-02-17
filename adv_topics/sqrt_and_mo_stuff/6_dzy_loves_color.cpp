#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

const int BLOCK_SIZE = 330;
const int MAXN = 100100;
const int MAXB = (MAXN + BLOCK_SIZE - 1) / BLOCK_SIZE;

int num_blocks;

int64 block_sum[MAXB];
int64 lazy_add[MAXB];
int block_color[MAXB];
bool uniform_color[MAXB];

int64 val[MAXN];
int color[MAXN];

inline int64 absll(int64 x) {
    return x >= 0 ? x : -x;
}

int64 range_sum(int l, int r) {
    int64 res = 0;

    for (int b = 0; b < num_blocks; b++) {
        int start = b * BLOCK_SIZE;
        int end = start + BLOCK_SIZE;

        if (end <= l || start >= r) continue;

        if (start >= l && end <= r) {
            res += block_sum[b];
            res += BLOCK_SIZE * lazy_add[b];
            continue;
        }

        int L = max(l, start);
        int R = min(r, end);

        res += lazy_add[b] * (R - L);
        for (int i = L; i < R; i++)
            res += val[i];
    }

    return res;
}

void recolor(int l, int r, int64 new_color) {
    for (int b = 0; b < num_blocks; b++) {
        int start = b * BLOCK_SIZE;
        int end = start + BLOCK_SIZE;

        if (end <= l || start >= r) continue;

        // Block is uniform
        if (uniform_color[b]) {
            if (block_color[b] == new_color) continue;

            if (start >= l && end <= r) {
                lazy_add[b] += absll(block_color[b] - new_color);
                block_color[b] = new_color;
                continue;
            }

            int L = max(l, start);
            int R = min(r, end);
            int64 diff = absll(block_color[b] - new_color);

            for (int i = L; i < R; i++) {
                val[i] += diff;
                block_sum[b] += diff;
                color[i] = new_color;
            }

            for (int i = start; i < L; i++) color[i] = block_color[b];
            for (int i = R; i < end; i++) color[i] = block_color[b];

            uniform_color[b] = false;
            block_color[b] = -1;
            continue;
        }

        // Block fully inside range
        if (start >= l && end <= r) {
            for (int i = start; i < end; i++) {
                int64 diff = absll(new_color - color[i]);
                val[i] += diff;
                block_sum[b] += diff;
            }
            block_color[b] = new_color;
            uniform_color[b] = true;
            continue;
        }

        // Partial overlap
        int L = max(l, start);
        int R = min(r, end);

        for (int i = L; i < R; i++) {
            int64 diff = absll(new_color - color[i]);
            val[i] += diff;
            block_sum[b] += diff;
            color[i] = new_color;
        }

        bool same = true;
        for (int i = start; i + 1 < end; i++) {
            if (color[i] != color[i + 1]) {
                same = false;
                break;
            }
        }

        if (same) {
            block_color[b] = new_color;
            uniform_color[b] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    num_blocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    for (int i = 0; i < n; i++)
        color[i] = i + 1;

    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        l--;

        if (t == 1) {
            int c;
            cin >> c;
            recolor(l, r, c);
        } else {
            cout << range_sum(l, r) << '\n';
        }
    }
}
