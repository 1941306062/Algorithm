#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5+7;
const int mod = 1e9+7;
/**add(l,r,x)表示区间[l,r]权值加上x
ranks(l,r,x)表示区间[l,r]查询第k大
assign(l,r,x)表示给区间[l,r]覆盖权值x
sum(l,r,x,y)表示求区间[l,r]的幂次和并模y*/

ll qpow(ll a, ll b, ll mod)
{
	ll tmp = a % mod;
    ll ans = 1;
    while(b)
    {
        if (b&1) ans = ans*tmp%mod;
        tmp = tmp*tmp%mod;
        b>>=1;
    }
    return ans;
}
struct node
{
    int l,r;
    mutable ll v;
    node(int L, int R=-1, ll V=0):l(L), r(R), v(V) {}
    bool operator<(const node& o) const
    {
        return l < o.l;
    }
};
set<node> s;

auto split(int pos)
{
	auto it = s.lower_bound(node(pos));
	if(it!=s.end() && it->l==pos) return it;
	--it;
	int l = it->l,r = it->r;
	ll v = it->v;
	s.erase(it);
	s.insert(node(l,pos-1,v));
	return s.insert(node(pos,r,v)).first;
}
void add(int l,int r,ll x = 1)
{
	auto itl = split(l),itr = split(r+1);
	for(;itl!=itr;++itl) itl->v += x;
}
void assign(int l,int r,ll v)
{
	auto itl = split(l),itr = split(r+1);
	s.erase(itl,itr);
	s.insert(node(l,r,v));
}
ll ranks(int l,int r,int k)
{
	vector<pair<ll,int> > v;
	auto itl = split(l),itr = split(r+1);
	for(;itl!=itr;++itl) v.push_back(make_pair(itl->v,itl->r-itl->l+1));
	sort(v.begin(),v.end());
	for(auto it : v)
	{
		k -= it.second;
		if(k<=0) return it.first;
	}
}
ll sum(int l,int r,ll x,ll mod)
{
	ll ans = 0;
	auto itl = split(l),itr = split(r+1);
	for(;itl!=itr;++itl) ans = (ans+1LL*(itl->r-itl->l+1)*qpow(itl->v,x,mod)%mod)%mod;
	return ans;
}
int n,m;
ll seed,vmax;
ll rnd()
{
    ll ret = seed;
    seed = (seed * 7 + 13) % mod;
    return ret;
}
ll a[maxn];
int main()
{
	scanf("%d %d %lld %lld",&n,&m,&seed,&vmax);
	for(int i=1;i<=n;i++)
	{
		a[i] = (rnd() % vmax) + 1;
		s.insert(node(i,i,a[i]));
	}
	s.insert(node(n+1,n+1,0));
	for(int i=1;i<=m;i++)
	{
		int op = ((int)rnd() % 4) + 1;
		int l = ((int)rnd() % n) + 1;
		int r = ((int)rnd() % n) + 1;
		if(l>r) swap(l,r);
		ll x,y;
		if(op==3) x = ((int)rnd() % (r-l+1)) + 1;
		else x = (rnd() % vmax) + 1;
		if(op==4) y = ((int)rnd() % vmax) + 1;
		if(op==1) add(l,r,x);
		else if(op==2) assign(l,r,x);
		else if(op==3) printf("%lld\n",ranks(l,r,x));
		else printf("%lld\n",sum(l,r,x,y));
	}
	return 0;
}
