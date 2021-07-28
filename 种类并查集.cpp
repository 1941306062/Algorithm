#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include <iomanip>
#include<string>
using namespace std;
typedef long long ll;
const int MAX=50000+10;
int n,k,mp[MAX*3+10];
void inti(int n){
    for(int i=1; i<=n; i++) mp[i]=i;
}
int finds(int x){
    int t=x;
    while(mp[t]!=t) t=mp[t];
    return t;
}
void union_set(int x,int y){
    int fx=finds(x);int fy=finds(y);
    if(fx!=fy) mp[fx]=fy;
}
int main(){
    int t,x,y;ll ans=0;
    scanf("%d%d",&n,&k);
    inti(n*3);
    for(int i=0; i<k; i++){
        scanf("%d%d%d",&t,&x,&y);
        if(x<1||x>n||y<1||y>n){ans++;continue;}
        if(t==1){
            if(finds(x)==finds(y+n)||finds(y)==finds(x+n)) ans++;
            else{
                union_set(x,y);
                union_set(x+n,y+n);
                union_set(x+2*n,y+2*n);
            }
        }else{
            if(finds(x)==finds(y)||finds(y)==finds(x+n)) ans++;
            else{
                union_set(x,y+n);
                union_set(x+n,y+2*n);
                union_set(x+n*2,y);
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}
