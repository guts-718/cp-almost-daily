#include <bits/stdc++.h>
using namespace std;
#define int long long

int N;
int INF = 4e18;


vector<vector<int>> mul(const vector<vector<int>>& A,
                        const vector<vector<int>>& B){
    vector<vector<int>> C(N, vector<int>(N, INF));

    for(int i=0;i<N;i++)
        for(int k=0;k<N;k++){
            if(A[i][k]>=INF) continue;
            for(int j=0;j<N;j++){
                C[i][j]=min(A[i][k]+B[k][j], C[i][j]);
            }
        }
    return C;
}

vector<vector<int>> mpow(vector<vector<int>> base,int exp){
    vector<vector<int>> res(N, vector<int>(N, INF));

    for(int i=0;i<N;i++) res[i][i]=0;

    while(exp){
        if(exp&1) res=mul(res,base);
        base=mul(base,base);
        exp/=2;
    }
    return res;
}

int32_t main(){
    int K;
    cin>>N>>K;

    vector<vector<int>> A(N, vector<int>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cin>>A[i][j];
        }
    }
    
    auto res=mpow(A,K);

    for(int i=0;i<N;i++){
        cout<<res[i][i]<<endl;
    }
}
