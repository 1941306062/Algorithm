
#include<bits/stdc++.h>
#define ios ios::sync_with_stdio(false)

using namespace std;
/*int lowbit(int x){
    return (x&-x);
}*/

#define fi first
#define se second
#define lowbit(x) x&-x
typedef pair <int, int> pii;
typedef long long ll;
const int M=1e6 +10;
const int mod=998244353;
int n,k;
int c[M][12];
int a[M];
int b[M];
//int c[M];
void update(int x,ll val){
   for (;x <= n;x += (x & -x))c[x] = max(c[x],val);
}
int ask(int  x){
    ll s=0;
     for (;x;x -= (x & -x)) s=max(s,c[x]);
    return s;
}
/*
void inti()
{
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        {

            cin>>num;
            cnt[i][j]=num;
            update(i,j,num);
        }
}*/

int main()
{
    //ios;
    cin>>n;
    for(int i=1;i<=n;i++) {cin>>cnt[i].a>>cnt[i].b;cnt[i].id=i;}
    sort(cnt+1,cnt+1+n,cmp2);
    for(int i=1;i<=n;i++) cnt[i].b=i;
    sort(cnt+1,cnt+1+n,cmp1);
    for(int i=1;i<=n;i++)
    {
        ans[cnt[i].id]=ask(cnt[i].b)+1;
        update(cnt[i].b,ans[cnt[i].id]);
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;
    return 0;
}
