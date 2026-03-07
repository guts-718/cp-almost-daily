#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Point{
    int x,y,id;
};

bool cmpXY(Point &p1, Point &p2){
    if(p1.x != p2.x) return p1.x < p2.x;
    return p1.y < p2.y;
}

bool cmpYDesc(Point &p1, Point &p2){
    return p1.y > p2.y;
}

bool cmpYAsc(Point &p1, Point &p2){
    return p1.y < p2.y;
}



int32_t main(){
   
    int n;
    cin >> n;
    vector<Point> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].id = i + 1;
    }

    sort(a.begin(), a.end(), cmpXY);
    int BLOCK = sqrt(n)+1;
    vector<int> ans;

    for(int i = 0; i < n; i += BLOCK){

        int r = min(n, i + BLOCK);

        if((i / BLOCK) % 2 == 0){
            sort(a.begin() + i, a.begin() + r, cmpYAsc);
        }
        else{
            sort(a.begin() + i, a.begin() + r, cmpYDesc);
        }

        for(int j = i; j < r; j++){
            ans.push_back(a[j].id);
        }
    }

    cout << 1 << " ";

    for(int v : ans){
        if(v != 1) cout << v << " ";
    }
}