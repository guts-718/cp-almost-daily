#include <bits/stdc++.h>
using namespace std;

/*
    SQRT DECOMPOSITION WITH LAZY PROPAGATION TEMPLATE
    -----------------------------------------------
    Supports:
        range_add(l, r, val)
        range_sum(l, r)

    HOW IT WORKS:
    - Array split into blocks of size ~sqrt(n)
    - Each block stores:
        sum  -> sum of elements in block
        lazy -> value to add to whole block

    QUERY/UPDATE LOGIC:
        For each block:
            if fully inside range -> use block info
            else -> push lazy and handle individually

    MODIFY THESE IF YOU WANT:
        - operation type (min/max/xor etc.)
        - update type
*/

struct SqrtDecomp {
    int n, block_size, num_blocks;
    vector<long long> arr;
    vector<long long> block_sum;
    vector<long long> lazy;

    SqrtDecomp(vector<long long> &input) {
        arr = input;
        n = arr.size();
        block_size = sqrt(n) + 1;
        num_blocks = (n + block_size - 1) / block_size;

        block_sum.assign(num_blocks, 0);
        lazy.assign(num_blocks, 0);

        for (int i = 0; i < n; i++)
            block_sum[i / block_size] += arr[i];
    }

    // push lazy value to actual elements
    void push(int b) {
        if (lazy[b] == 0) return;
        int start = b * block_size;
        int end = min(n, start + block_size);

        for (int i = start; i < end; i++)
            arr[i] += lazy[b];

        lazy[b] = 0;
    }

    // range add
    void range_add(int l, int r, long long val) {
        int start_block = l / block_size;
        int end_block = r / block_size;

        for (int b = start_block; b <= end_block; b++) {
            int start = b * block_size;
            int end = min(n, start + block_size) - 1;

            if (l <= start && end <= r) {
                // FULL BLOCK
                lazy[b] += val;
                block_sum[b] += val * (end - start + 1);
            }
            else {
                // PARTIAL BLOCK
                push(b);
                for (int i = max(l, start); i <= min(r, end); i++) {
                    arr[i] += val;
                    block_sum[b] += val;
                }
            }
        }
    }

    // range sum query
    long long range_sum(int l, int r) {
        long long ans = 0;

        int start_block = l / block_size;
        int end_block = r / block_size;

        for (int b = start_block; b <= end_block; b++) {
            int start = b * block_size;
            int end = min(n, start + block_size) - 1;

            if (l <= start && end <= r) {
                // FULL BLOCK
                ans += block_sum[b];
            }
            else {
                // PARTIAL BLOCK
                push(b);
                for (int i = max(l, start); i <= min(r, end); i++)
                    ans += arr[i];
            }
        }
        return ans;
    }
};


int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    SqrtDecomp ds(a);

    /*
        QUERY FORMAT:

        1 l r val   -> add val to [l,r]
        2 l r       -> print sum of [l,r]

        (0-indexed assumed)
    */

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;
            ds.range_add(l, r, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << ds.range_sum(l, r) << "\n";
        }
    }
}
