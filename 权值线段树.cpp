int tree[n<<2];
void update_tree(int p,int v,int rt,int l,int r)//当v=1为增加，当v=-1的时为减少
{
	tree[rt]+=v;
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(p<=mid)
		update_tree(p,v,rt<<1,l,mid);
	else
		update_tree(p,v,rt<<1|1,mid+1,r);
}
int kth(int k,int rt,int l,int r)//k小值
{
	if(l==r)
		return l;
	int mid=(l+r)>>1;
	if(tree[rt<<1]>=k)
		return kth(k,rt<<1,l,mid);
	else
		return kth(k-tree[rt<<1],rt<<1|1,mid+1,r);
}
int rankl(int p,int rt,int l,int r)//排名
{
	if(r<p)
		return tree[rt];
	int m=(l+r)>>1;
	int res=0;
	res+=rankl(p,rt<<1,l,m);
	if(m<p-1)
		res+=rankl(p,rt<<1|1,m+1,r);
	return res;
}

//前驱
int findl(int rt,int l,int r)
{
    if(l==r)
        return l;
    int m=(l+r)>>1;
    if(t[rt<<1|1])
        return findl(rt<<1|1,m+1,r);
    return findl(rt<<1,l,m);
}
int pre(int p,int rt,int l,int r)//前驱
{
    if(r<p)
    {
        if(t[rt])
            return findl(rt,l,r);//查询最靠右的数
        return 0;
    }
    int m=(l+r)>>1;
    int re;
    if(m<p-1&&t[rt<<1|1]&&(re=pre(p,rt<<1|1,m+1,r)))//先考虑右子树
        return re;
    return pre(p,rt<<1,l,m);
}
int next(int p,int rt,intl,int r)//后继
{
    if(p<l)
    {
        if(t[rt])
            return findl(rt,l,r);
        return 0;
    }
    int m=(l+r)>>1;
    int re;
    if(p<m&&t[rt<<1]&&(re=next(p,rt<<1,l,m)))
        return re;
    return next(p,rt<<1|1,m+1,r);
}
void add(int l,int r,int v,int x)//添加
{
    if(l==r) f[v]++;
    else
    {
        int mid=(l+r)/2;
        if(x<=mid) add(l,mid,v*2,x); else add(mid+1,r,v*2+1,x);
        f[v]=f[v*2]+f[v*2+1];
    {
}
int find(int l,int r,int v,int x)
{
    if(l==r) return f[v];
    else
    {
        int mid=(l+r)/2;
        if(x<=mid) return find(l,mid,v*2,x); else return find(mid+1,r,v*2+1,x);
    }
}
