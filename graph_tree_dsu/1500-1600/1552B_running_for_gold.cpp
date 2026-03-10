#include <bits/stdc++.h>
#define int long long
using namespace std;

int32_t main() {
    int t=1;
    cin>>t;

    while(t--){
        int n;
        cin>>n;

        vector<vector<int>> v(n,vector<int>(5));
        vector<int> best(5);

        for(int i=0;i<n;i++){
            int a,b,c,d,e;
            cin>>a>>b>>c>>d>>e;
            v[i]={a,b,c,d,e};
            if(i==0) best=v[i];
        }

        vector<int> id;
        for(int i=0;i<n;i++) id.push_back(i);

        while(id.size()>1){
            vector<int> temp;

            for(int i=0;i<id.size();i+=2){

                if(i+1>=id.size()){
                    temp.push_back(id[i]);
                    continue;
                }

                int cnt=0;
                for(int j=0;j<5;j++){
                    if(v[id[i]][j] < v[id[i+1]][j]) cnt++;
                }

                if(cnt<=2){
                    temp.push_back(id[i+1]);
                }else{
                    temp.push_back(id[i]);
                }
            }

            id=temp;
        }

        int cur=id[0];
        best=v[cur];

        bool b=true;

        for(int i=0;i<n;i++){
            if(i==cur) continue;

            int cnt=0;
            for(int j=0;j<5;j++){
                if(best[j] < v[i][j]) cnt++;
            }

            if(cnt<=2){
                b=false;
                break;
            }
        }

        if(b){
            cout<<cur+1<<endl;
        }else{
            cout<<-1<<endl;
        }
    }
}