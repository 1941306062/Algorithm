#include<iostream>
#include<stdio.h>
#include<algorithm>
using namespace std;
#define ios ios::sync_with_stdio(false)
#define eb emplace_back
#define DEBUG(x) cerr << #x << '=' << x << endl
typedef long long ll;
template <typename T>
inline void read(T &f)  //快读
{
    f = 0;
    T fu = 1;
    char c = getchar();
    while (c < '0' || c > '9')
    {
        if (c == '-')
        {
            fu = -1;
        }
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        f = (f << 3) + (f << 1) + (c & 15);
        c = getchar();
    }
    f *= fu;
}

template <typename T>
inline void print(T x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t)
{
    print(x);
    putchar(t);
}
const int N=2e5+10;
/*
a 输入数组
b 去重数组
sz 去重后大小
tot 版本
s 根
ls 左
rs 右
*/
int n,m,tot,sz,num,a[N],b[N],rt[N],s[N],sum[N*300],ls[N*300],rs[N*300],rootl[50],rootr[50],cntl,cntr;
struct node{
	int l,r,k,op;
}q[N];

int hash1()
{
    sort(b+1,b+1+sz);
    return unique(b+1,b+1+sz)-b-1;
}
int get(int x){return lower_bound(b+1,b+sz+1,x)-b;}
int lowbit(int x){return x&(-x);}
struct Tree{
	void update(int &o,int pre,int l,int r,int x){
		o=++tot;
		sum[o]=sum[pre]+1;
		ls[o]=ls[pre];
		rs[o]=rs[pre];
		if(l==r) return;
		int mid=l+r>>1;
		if(x<=mid) update(ls[o],ls[pre],l,mid,x);
		else update(rs[o],rs[pre],mid+1,r,x);
	}
	void add_update(int &o,int l,int r,int x,int val){
		if(o==0) o=++tot;
		sum[o]+=val;
		if(l==r) return;
		int mid=l+r>>1;
		if(x<=mid) add_update(ls[o],l,mid,x,val);
		else add_update(rs[o],mid+1,r,x,val);
	}
	void add_update(int k,int val){
		int x=get(a[k]);int y=get(val);
		a[k]=val;
		while(k<=n){
			add_update(s[k],1,sz,x,-1);
			add_update(s[k],1,sz,y,1);
			k+=lowbit(k);
		}
	}
	int query(int last,int now,int l,int r,int x){
        if(l==r) return l;
        int cnt=sum[ls[now]]-sum[ls[last]];
        for(int i=1;i<=cntl;++i) cnt-=sum[ls[rootl[i]]];
        for(int i=1;i<=cntr;++i) cnt+=sum[ls[rootr[i]]];
        int mid=l+r>>1;
        if(cnt>=x){
            for(int i=1;i<=cntl;++i) rootl[i]=ls[rootl[i]];
            for(int i=1;i<=cntr;++i) rootr[i]=ls[rootr[i]];
            return query(ls[last],ls[now],l,mid,x);
        }else{
            for(int i=1;i<=cntl;++i) rootl[i]=rs[rootl[i]];
            for(int i=1;i<=cntr;++i) rootr[i]=rs[rootr[i]];
            return query(rs[last],rs[now],mid+1,r,x-cnt);
        }
    }
	int kth(int l,int r,int k){
		cntl=cntr=0;
		for(int i=l-1;i;i-=lowbit(i)) rootl[++cntl]=s[i];
		for(int i=r;i;i-=lowbit(i)) rootr[++cntr]=s[i];
		int ans=query(rt[l-1],rt[r],1,sz,k);
		return b[ans];
	}
}tr;

int main()
{
    int i,j,l,r,k;
    read(n);
    read(m);
    for(i=1;i<=n;i++)
        read(a[i]),b[++sz]=a[i];
    for(int i=1;i<=m;i++){
        char ch; scanf(" %c",&ch);
        if(ch=='Q'){
            q[i].op=1;
            read(q[i].l);
            read(q[i].r);
            read(q[i].k);
        }else {
        q[i].op=2;
        read(q[i].l);
        read(q[i].r);
        b[++sz]=q[i].r;
        }
    }
    sz=hash1();
    for(i=1;i<=n;i++)
        tr.update(rt[i],rt[i-1],1,sz,get(a[i]));
    for(int i=1;i<=m;i++)
    {
        if(q[i].op==1){
            print(tr.kth(q[i].l,q[i].r,q[i].k),'\n');
        }else {
            tr.add_update(q[i].l,q[i].r);
        }
    }
    return 0;
}
