#include<cstdio>
#include<cmath>
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ios ios::sync_with_stdio(false);
const int M=1e5+233;
int n,m,k,u,v,w,t;
int a[M],st[M][25],Log[M];
//初始化st表
void init(){
    Log[1]=0;
    for(int i=2;i<=n+1;i++) Log[i]=Log[i/2]+1;
    for(int i=1;i<=n;i++) st[i][0]=a[i];
    for(int j=1;(1<<j)<=n;j++){//涉及到位运算加括号！
        for(int i=1;i+(1<<(j-1))<=n;i++){
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
        }
    }
}
int ask(int l,int r){
    int k = Log[r-l+1];
    int mx = max(st[l][r],st[r-(1<<k)+1][k]);
    return mx;
}
int main()
{
    ios;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    init();
    for(int i=1,l,r;i<=m;i++){
        cin>>l>>r;
        cout<<ask(l,r)<<"\n";
    }
}
