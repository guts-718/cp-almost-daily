#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

const int MAXN = 2001;

int N;
int distArr[MAXN];
vector<pii> edges;

mt19937 rng(69696969);

void query(int node) {
    cout << "? " << node << '\n';
    cout.flush();

    for (int i = 1; i <= N; i++) {
        cin >> distArr[i];
    }
}

void makeUnique(vector<pii>& v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    query(1);

    vector<int> parity[2];

    for (int i = 2; i <= N; i++) {
        parity[distArr[i] % 2].push_back(i);
    }

    if (parity[0].size() > parity[1].size()) {
        swap(parity[0], parity[1]);
    }

    for (int i = 1; i <= N; i++) {
        if (distArr[i] == 1) {
            edges.emplace_back(1, i);
        }
    }

    for (int x : parity[0]) {
        query(x);

        for (int i = 1; i <= N; i++) {
            if (distArr[i] == 1) {
                int a = x;
                int b = i;

                if (a > b) {
                    swap(a, b);
                }

                edges.emplace_back(a, b);
            }
        }
    }

    makeUnique(edges);

    shuffle(edges.begin(), edges.end(), rng);

    uniform_int_distribution<int> coin(0, 1);

    for (auto &edge : edges) {
        if (coin(rng)) {
            swap(edge.first, edge.second);
        }
    }

    cout << "!\n";

    for (auto &[u, v] : edges) {
        cout << u << " " << v << "\n";
    }

    return 0;
}