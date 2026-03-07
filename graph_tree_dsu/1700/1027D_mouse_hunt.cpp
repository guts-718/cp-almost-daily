#include <iostream>
using namespace std;

const int N = 200005;
const int INF = 1e9 + 7;

int n;
int ans = 0;

int a[N];   
int f[N];   
int vis[N];


void DFS(int u)
{
    vis[u] = 1; 

    if (vis[f[u]] == 0)
    {
        DFS(f[u]);
    }
    else if (vis[f[u]] == 1)
    {
        int add = INF;
        int cur = u;
        do
        {
            add = min(add, a[cur]);
            cur = f[cur];
        }
        while (cur != u);

        ans += add;
    }

    vis[u] = 2; 
}


int main()
{
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= n; i++)
        cin >> f[i];

    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0)
            DFS(i);
    }

    cout << ans << endl;
}