#include <bits/stdc++.h>
using namespace std;

/*
========================================
    SQRT DECOMPOSITION TEMPLATE
    Range Update + Range Query
========================================

CURRENT VERSION SUPPORTS:
    update(l, r, val) → add val to all elements
    query(l, r) → sum of range

TO MODIFY FOR OTHER PROBLEMS:
    See "MODIFICATION ZONES" comments below.
*/

struct SqrtDecomp {

    int n;
    int blockSize;
    int numBlocks;

    vector<long long> arr;
    vector<long long> blockSum;  // stores answer of full block
    vector<long long> lazy;      // lazy value for each block


    /*------------------------------------
        CONSTRUCTOR
    ------------------------------------*/
    SqrtDecomp(vector<long long> &input) {

        arr = input;
        n = arr.size();

        blockSize = sqrt(n) + 1;
        numBlocks = (n + blockSize - 1) / blockSize;

        blockSum.assign(numBlocks, 0);
        lazy.assign(numBlocks, 0);

        // build block sums
        for (int i = 0; i < n; i++)
            blockSum[i / blockSize] += arr[i];
    }


    /*------------------------------------
        PUSH LAZY DOWN TO ELEMENTS
        Needed only when partial block used
    ------------------------------------*/
    void push(int b) {

        if (lazy[b] == 0) return;

        int start = b * blockSize;
        int end = min(n, start + blockSize);

        for (int i = start; i < end; i++)
            arr[i] += lazy[b];

        lazy[b] = 0;
    }


    /*------------------------------------
        RANGE UPDATE
        add val to [l , r]
    ------------------------------------*/
    void update(int l, int r, long long val) {

        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {

            push(startBlock);

            for (int i = l; i <= r; i++) {
                arr[i] += val;
                blockSum[startBlock] += val;
            }
            return;
        }

        // left partial block
        push(startBlock);

        int leftEnd = (startBlock + 1) * blockSize - 1;

        for (int i = l; i <= leftEnd; i++) {
            arr[i] += val;
            blockSum[startBlock] += val;
        }


        // full blocks
        for (int b = startBlock + 1; b < endBlock; b++) {

            lazy[b] += val;

            // MODIFICATION ZONE
            // blockSum update logic depends on problem
            blockSum[b] += val * blockSize;
        }


        // right partial block
        push(endBlock);

        int rightStart = endBlock * blockSize;

        for (int i = rightStart; i <= r; i++) {
            arr[i] += val;
            blockSum[endBlock] += val;
        }
    }



    /*------------------------------------
        RANGE QUERY
        sum of [l , r]
    ------------------------------------*/
    long long query(int l, int r) {

        long long ans = 0;

        int startBlock = l / blockSize;
        int endBlock = r / blockSize;

        if (startBlock == endBlock) {

            push(startBlock);

            for (int i = l; i <= r; i++)
                ans += arr[i];

            return ans;
        }


        // left partial
        push(startBlock);

        int leftEnd = (startBlock + 1) * blockSize - 1;

        for (int i = l; i <= leftEnd; i++)
            ans += arr[i];


        // full blocks
        for (int b = startBlock + 1; b < endBlock; b++)
            ans += blockSum[b];


        // right partial
        push(endBlock);

        int rightStart = endBlock * blockSize;

        for (int i = rightStart; i <= r; i++)
            ans += arr[i];

        return ans;
    }
};



/*========================================
                MAIN
========================================*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    SqrtDecomp ds(a);

    /*
    QUERY FORMAT (example):

    type 1 l r val → range add
    type 2 l r     → range sum
    */

    while (q--) {

        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            long long v;
            cin >> l >> r >> v;

            --l; --r; // convert to 0-index

            ds.update(l, r, v);
        }
        else {
            int l, r;
            cin >> l >> r;

            --l; --r;

            cout << ds.query(l, r) << "\n";
        }
    }
}
