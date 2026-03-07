#include <bits/stdc++.h>
using namespace std;

int r[]={-1,0,1,0};
int c[]={0,1,0,-1};

class DSU{
public:
    vector<int> parent;
    vector<int> size;
    int n,m;
    vector<string> vv;

    DSU(int _n,int _m,vector<string>&v){
        n=_n;
        m=_m;
        vv=v;
        parent.resize(n*m);
        size.resize(n*m);

        for(int i=0;i<n*m;i++){
            parent[i]=i;
            size[i]=1;
        }
    }

    int findUPar(int u){
        if(parent[u]==u) return u;
        return parent[u]=findUPar(parent[u]);
    }

    int join(int u,int v){
        int merge=0;
        int r1,c1,r2,c2;
        r1=u/m; c1=u%m;
        r2=v/m; c2=v%m;

        if(vv[r2][c2]=='#') return -1;

        if(vv[r2][c2]=='.' || vv[r2][c2]=='G'){
            int cnt=0;
            for(int i=0;i<4;i++){
                int nr=r2+r[i];
                int nc=c2+c[i];
                if(nr<n && nr>=0 && nc<m && nc>=0){
                    if(vv[nr][nc]=='B') cnt++;
                }
            }
            if(cnt>0) return -1;
            merge=1;
        }

        int pu=findUPar(u);
        int pv=findUPar(v);

        if(pu==pv){
            return 1;
        }

        if(size[pu] > size[pv]){
            parent[pv]=pu;
            size[pu]+=size[pv];
        }else{
            parent[pu]=pv;
            size[pv]+=size[pu];
        }

        return 1;
    }
};

int main(){
    int t;
    cin>>t;

    while(t--){
        int n,m;
        cin>>n>>m;

        vector<string> v(n);
        for(int i=0;i<n;i++) cin>>v[i];
        
        int g=0; 
        for(auto &x:v){
            for(auto y:x) g+=(y=='G');
        }
        if(v[n-1][m-1]=='B'){
            cout<<"NO"<<endl;
            continue;
        }
        if(g){
            if(n>=2 && v[n-2][m-1]=='B'){
                 cout<<"NO"<<endl;
                 continue;
            }
            
             if(m>=2 && v[n-1][m-2]=='B'){
                 cout<<"NO"<<endl;
                 continue;
            }
        }
        DSU dsu(n,m,v);

        queue<int> q;
        vector<int> vis(n*m,0);

        int start=n*m-1;
        q.push(start);
        vis[start]=1;

        while(!q.empty()){
            int node=q.front(); 
            q.pop();

            int rr=node/m;
            int cc=node%m;

            for(int i=0;i<4;i++){
                int nr=rr+r[i];
                int nc=cc+c[i];

                if(nr<n && nr>=0 && nc<m && nc>=0 && v[nr][nc]!='B'){
                    int id=nr*m+nc;

                    if(!vis[id]){
                        int x=dsu.join(node,id);
                        if(x>=1){
                            q.push(id);
                            vis[id]=1;
                        }
                    }
                }
            }
        }

        int good=0,bad=0;
        int up=dsu.findUPar(n*m-1);

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(dsu.findUPar(i*m+j)==up){
                    if(v[i][j]=='G') good++;
                    else if(v[i][j]=='B') bad++;
                }
            }
        }

        if(good==g && bad==0) cout<<"YES\n";
        else cout<<"NO\n";
    }
}