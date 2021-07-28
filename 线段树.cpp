#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define lson l,mid,p<<1
#define rson mid+1,r,p<<1|1
#define ios ios::sync_with_stdio(false)
typedef long long ll;
const int MAXN= 2e5+10;
int n,m;
int d[MAXN];
struct Tree
{
    int l,r;
    ll w;
    int sum;
}tree[MAXN<<2];
ll add[MAXN<<2];
inline void push_up(int x){
    tree[x].sum = tree[x<<1].sum+tree[x<<1|1].sum;
}
inline void push_down(int x,int m){//lazy
    if(add[x]){
        add[x<<1]+=add[x];
        add[x<<1|1]+=add[x];
        tree[x<<1].sum+=(m-(m>>1))*add[x];
        tree[x<<1|1].sum+=(m>>1)*add[x];
        add[x]=0;
    }
}

void build(int p,int l,int r)
{
    add[p]=0;
    tree[p].l=l;
    tree[p].r=r;
    if(l==r) {
            tree[p].gcd=tree[p].maximum=abs(d[l]);
            tree[p].sum=d[l];return;
    }
    int mid=(l+r)>>1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    push_up(p);
}
void update(int id,int p,int x)//单点更新
{
    if(tree[id].l==p&&tree[id].r==p)
    {
        tree[id].sum+=x;
        tree[id].maximum=abs(tree[id].sum);
        tree[id].gcd=abs(tree[id].sum);
        return;
    }
    int mid=(tree[id].l+tree[id].r)>>1;
    if(p<=mid) update(id<<1,p,x);
    else update(id<<1|1,p,x);
    push_up(id);
}
void change(int p,int l,int r,int num)//区间修改，lazy
{

    if(l<=tree[p].l&&tree[p].r<=r) {
        tree[p].sum+=((long long)(tree[p].r-tree[p].l+1))*num;
        add[p]+=num;
        return;
    }
    push_down(p,r-l+1);
    int mid=(tree[p].l+r)>>1;
    if(l<=mid) change(p*2,l,r,num);
    if(r>mid) change(p*2+1,l,r,num);
    push_up(p);
}
ll query(int p,int l,int r)//区间求和 lazy
{
    if(l<=tree[p].l&&r>=tree[p].r) return tree[p].sum;
    push_down(p,tree[p].r-tree[p].l+1);
    int mid=(l+r)>>1;
    ll sum=0;
    if(l<=mid) sum+=query(p*2,l,mid);
    if(r>mid) sum+=query(p*2+1,mid+1,r);
    return sum;
}

int query_gcd(int p,int l,int r)//求区间里数的公约数，用到了差分数组
{
    if(l<=tree[p].l&&tree[p].r<=r) return tree[p].gcd;
    int mid=(tree[p].l+tree[p].r)>>1;
    int sum=0;
    if(l<=mid) sum=query_gcd(sum,query_gcd(p<<1,l,r));
    if(r>=mid+1) sum=query_gcd(sum,query_gcd(p<<1|1,l,r));
    return sum;
}

int query_sum(int p,int l,int r)//区间求和，无lazy
{
    if(l<=tree[p].l&&tree[p].r<=r) return tree[p].sum;
    int mid=(tree[p].l+tree[p].r)>>1;
    int sum=0;
    if(l<=mid) sum+=query_sum(p<<1,l,r);
    if(r>=mid+1) sum+=query_sum(p<<1|1,l,r);
    return sum;
}

int query_sub(int p,int l,int r)//区间里数之间差值绝对值最大
{
    if(l<=tree[p].l&&tree[p].r<=r) return tree[p].maximum;
    int mid=(tree[p].l+tree[p].r)>>1;
    int sum=0;
    if(l<=mid) sum=max(sum,query_sub(p<<1,l,r));
    if(r>=mid+1) sum=max(sum,query_sub(p<<1|1,l,r));
    return sum;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) scanf("%d",col+i);
    for(int i=1;i<=n;i++) d[i]=col[i]-col[i-1];//差分数组
    build(1,1,n);
    while(m--){
        int opt;
        int l,r;
        int c;
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1){
            scanf("%d",&c);
            update(1,l,c);
            if(r<n) update(1,r+1,-c);
        }else if(opt==2){

            if(l==r) puts("0");
            else cout<<sub(1,l+1,r)<<endl;
        }else {

            cout<<__gcd(fin(1,1,l),gc(1,l+1,r))<<endl;
        }
    }
}


/*
//乘法线段树,只有乘法
//加法-plz  *法-mlz
inline void pushdown(long long i){//注意这种级别的数据一定要开long long
    long long k1=tree[i].mlz,k2=tree[i].plz;
    tree[i<<1].sum=(tree[i<<1].sum*k1+k2*(tree[i<<1].r-tree[i<<1].l+1))%p;//
    tree[i<<1|1].sum=(tree[i<<1|1].sum*k1+k2*(tree[i<<1|1].r-tree[i<<1|1].l+1))%p;
    tree[i<<1].mlz=(tree[i<<1].mlz*k1)%p;
    tree[i<<1|1].mlz=(tree[i<<1|1].mlz*k1)%p;
    tree[i<<1].plz=(tree[i<<1].plz*k1+k2)%p;
    tree[i<<1|1].plz=(tree[i<<1|1].plz*k1+k2)%p;
    tree[i].plz=0;
    tree[i].mlz=1;
    return ;
}
//根号线段树
inline void Sqrt(int i,int l,int r){
    if(tree[i].l>=l && tree[i].r<=r && (tree[i].minn-(long long)sqrt(tree[i].minn))==(tree[i].maxx-(long long)sqrt(tree[i].maxx))){//如果这个区间的最大值最小值一样
        long long u=tree[i].minn-(long long)sqrt(tree[i].minn);//计算区间中每个元素需要减去的
        tree[i].lz+=u;
        tree[i].sum-=(tree[i].r-tree[i].l+1)*u;
        tree[i].minn-=u;
        tree[i].maxx-=u;
            //cout<<"i"<<i<<" "<<tree[i].sum<<endl;
        return ;
    }
    if(tree[i].r<l || tree[i].l>r)  return ;
    push_down(i);
    if(tree[i*2].r>=l)  Sqrt(i*2,l,r);
    if(tree[i*2+1].l<=r)  Sqrt(i*2+1,l,r);
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;
    tree[i].minn=min(tree[i*2].minn,tree[i*2+1].minn);//维护最大值和最小值
    tree[i].maxx=max(tree[i*2].maxx,tree[i*2+1].maxx);
    //cout<<"i"<<i<<" "<<tree[i].sum<<endl;
    return ;
}

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
#define ios ios::sync_with_stdio(false)
typedef long long ll;
const int MAXN=100000 + 5;
const int M=10007;

int n,q;

int s[MAXN<<2],e[MAXN<<2];
ll sum[MAXN<<2][3],add[MAXN<<2][3];//0 1 2  1 2 3

void build(int p,int l,int r)
{
    s[p]=l;
    e[p]=r;
    sum[p][0]=sum[p][1]=sum[p][2]=0;
    add[p][0]=add[p][2]=0;
    add[p][1]=1;

    if(l!=r)
    {
        int mid=(l+r)>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        //build(rson);
    }
}

void push_down(int p, int len)
{
    int lc = p << 1, rc = p << 1 | 1;
    if(add[p][2])
    {
        add[lc][2] = add[rc][2] = add[p][2];
        add[lc][1] = add[rc][1] = 1;
        add[lc][0] = add[rc][0] = 0;

        ll tmp = (add[p][2] * add[p][2] % M) * add[p][2] % M;
        sum[lc][2] = tmp * (len - (len >> 1)) % M;
        sum[rc][2] = tmp * (len >> 1) % M;

        sum[lc][1] = (((add[p][2] * add[p][2]) % M) * (len - (len >> 1)) % M) % M;
        sum[rc][1] = ((add[p][2] * add[p][2] % M) * (len >> 1) % M) % M;

        sum[lc][0] = add[p][2] * (len - (len >> 1)) % M;
        sum[rc][0] = add[p][2] * (len >> 1) % M;

        add[p][2] = 0;
    }

    if(add[p][1] != 1)
    {
        add[lc][1] = add[lc][1] * add[p][1] % M;
        add[rc][1] = add[rc][1] * add[p][1] % M;
        if(add[lc][0])	add[lc][0] = add[lc][0] * add[p][1] % M;
        if(add[rc][0])	add[rc][0] = add[rc][0] * add[p][1] % M;

        sum[lc][2] = sum[lc][2] * ((add[p][1] * add[p][1] % M) * add[p][1] % M) % M;
        sum[rc][2] = sum[rc][2] * ((add[p][1] * add[p][1] % M) * add[p][1] % M) % M;

        sum[lc][1] = sum[lc][1] * (add[p][1] * add[p][1] % M) % M;
        sum[rc][1] = sum[rc][1] * (add[p][1] * add[p][1] % M) % M;

        sum[lc][0] = sum[lc][0] * add[p][1] % M;
        sum[rc][0] = sum[rc][0] * add[p][1] % M;

        add[p][1] = 1;
    }

    if(add[p][0])
    {
        add[lc][0] += add[p][0];
        add[rc][0] += add[p][0];

        ll tmp = (add[p][0] * add[p][0] % M) * add[p][0] % M;
        sum[lc][2] = (sum[lc][2] + (add[p][0] * (sum[lc][1] + add[p][0] * sum[lc][0] % M) % M * 3) % M
                      + (len - (len >> 1)) * tmp % M) % M;
        sum[rc][2] = (sum[rc][2] + (add[p][0] * (sum[rc][1] + add[p][0] * sum[rc][0] % M) % M * 3) % M
                      + (len >> 1) * tmp % M) % M;

        tmp = add[p][0] * add[p][0] % M;
        sum[lc][1] = (sum[lc][1] + 2 * (add[p][0] * sum[lc][0] % M) % M +
                      (len - (len >> 1)) * tmp % M) % M;
        sum[rc][1] = (sum[rc][1] + 2 * (add[p][0] * sum[rc][0] % M) % M + (len >> 1) * tmp % M) % M;

        sum[lc][0] = (sum[lc][0] + (add[p][0] * (len - (len >> 1)) % M)) % M;
        sum[rc][0] = (sum[rc][0] + (add[p][0] * (len >> 1) % M)) % M;

        add[p][0] = 0;
    }
}



void push_up(int p)
{
    int lc = p << 1, rc = p << 1 | 1;
    sum[p][0] = (sum[lc][0] + sum[rc][0]) % M;
    sum[p][1] = (sum[lc][1] + sum[rc][1]) % M;
    sum[p][2] = (sum[lc][2] + sum[rc][2]) % M;
}


void update(int t,int c,int st,int ed,int p)
{
    int len=ed-st+1;
    if(s[p]==st&&e[p]==ed)
    {

        if(t == 2)
        {
            add[p][2] = c;
            add[p][1] = 1;
            add[p][0] = 0;
            sum[p][0] = (c*(ed-st+1))%M;
            sum[p][1] = ((c * c % M) * (ed - st + 1)) % M;
            sum[p][2] = (((c * c) % M) * c % M) * (ed - st + 1) % M;
        }

        else if(t == 1)
        {
            add[p][1] = add[p][1] * c % M;
            if(add[p][0])	add[p][0] = add[p][0] * c % M;
            sum[p][0] = sum[p][0] * c % M;
            sum[p][1] = (c * c % M) * sum[p][1] % M;
            sum[p][2] = ((c * c % M) * c % M) * sum[p][2] % M;
        }

        else if(t == 0)
        {
            add[p][0] = (add[p][0] + c) % M;
            sum[p][2]=(sum[p][2] + (sum[p][1] + c * sum[p][0] % M) * 3 * c % M +
                       ((((len * c) % M) * c % M) * c % M)) % M;


            sum[p][1] = (sum[p][1] + (sum[p][0] * c % M) * 2 % M + (len * c % M) * c % M) % M;
            sum[p][0]=(c*len%M+(sum[p][0]))%M;
        }
        return ;
    }
    if(s[p]==e[p]) return;

    push_down(p,e[p]-s[p]+1);

    int m = (s[p]+e[p])>>1;
    if(ed<=m) update(t,c,st,ed,p<<1);
    else if(st>m) update(t,c,st,ed,p<<1|1);
    else
    {
        update(t,c,st,m,p<<1);
        update(t,c,m+1,ed,p<<1|1);
    }
    push_up(p);
}
ll query(int op,int l,int r,int p)
{
    if(s[p]==l&&e[p]==r)
    {
        return sum[p][op]%M;
    }

    push_down(p,e[p]-s[p]+1);

    int m=(s[p]+e[p])>>1;

    ll res=0;
    if(r<=m) res+=query(op,l,r,p<<1)%M;
    else if(l>m) res+=query(op,l,r,p<<1|1)%M;
    else
    {
        res += query(op,l,m,p<<1)%M;
        res += query(op,m+1,r,p<<1|1)%M;
    }
    return res%M;
}
int main()
{
    //freopen("in.txt","r",stdin);
    while(cin>>n>>q)
    {
        if(n==0&&q==0) break;

        build(1,1,n);

        while(q--)
        {
            int op,a,b,c;
            scanf("%d%d%d%d",&op,&a,&b,&c);

            if(op==4)
            {
                printf("%lld\n",query(c-1,a,b,1)%M);
            }
            else
            {
                update(op-1,c,a,b,1);
            }

        }
    }

}

*/
