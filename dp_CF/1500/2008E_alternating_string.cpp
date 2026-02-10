#include <bits/stdc++.h>
using namespace std;

int ev(string &s){
    map<char,int>a,b;
    int n=s.length();
    for(int i=0;i<n;i++){
        if(i%2==1){
            b[s[i]]++;
        }else a[s[i]]++;
    }
    int ma=0,mb=0;
    for(auto [x,v]:a){
        ma=max(ma,v);
    }
    for(auto [x,v]:b){
        mb=max(mb,v);
    }
    return n-ma-mb;
}

int help(vector<int>&a,vector<int>&b,vector<int>&c,vector<int>&d){
    int n=0;
    for(int i=0;i<27;i++){
        // cout<<a[i]+b[i]<<" "<<c[i]+d[i]<<endl;
        a[i]+=b[i];
        c[i]+=d[i];
    }
    int ma=0,mb=0;
    for(int i=0;i<27;i++){
        ma=max(ma,a[i]);
        mb=max(mb,c[i]);
    }
    for(int i=0;i<27;i++){
        a[i]-=b[i];
        c[i]-=d[i];
        //n+=a[i]+c[i];
    }
    // cout<<n<<" "<<ma<<" "<<mb<<endl;
    return ma+mb;
}

int o(string &s){
    int n=s.length();
    vector<vector<int>> preo(n+5,vector<int>(27,0));
    vector<vector<int>> pree, posto, poste;
    pree = posto = poste = preo;

    for(int i=0;i<n;i++){
        if(i%2==0){
            preo[i][s[i]-'a']++;
        }else{
            pree[i][s[i]-'a']++;
        }
        for(int j=0;j<26;j++){
            if(i) pree[i][j]+=pree[i-1][j];
            if(i) preo[i][j]+=preo[i-1][j];
        }
    }

    for(int i=n-1;i>=0;i--){
        if(i%2==0){
            posto[i][s[i]-'a']++;
        }else{
            poste[i][s[i]-'a']++;
        }
        for(int j=0;j<26;j++){
            if(i) poste[i][j] += poste[i+1][j];  
            if(i) posto[i][j] += posto[i+1][j];
        }
    }

    int ans=1e8;
    for(int i=1;i<n-1;i++){
        ans=min(ans,n-1-(help(preo[i-1],poste[i+1],pree[i-1],posto[i+1])));
    }
    string t=s;
    t.pop_back();
    string u;
    for(int i=1;i<n;i++) u.push_back(s[i]);
    ans=min(ans,ev(t));
    ans=min(ans,ev(u));
    return ans;
}

int main() {
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        if(n%2==0){
            cout<<ev(s)<<endl;
        }else{
            cout<<1+o(s)<<endl;
        }
    }
}
