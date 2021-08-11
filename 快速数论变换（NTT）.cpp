#define g 3//模数的原根
#define mod 998244353//通常情况下的模数

int pow(int x,int y)//快速幂
{
	ll z=1ll*x,ans=1ll;
	for (;y;y/=2,z=z*z%mod)if (y&1)ans=ans*z%mod;//注意精度
	return (int)ans%mod;
}
inline void ntt(int a[],int len,int inv)
{
	int bit=0;
	while ((1<<bit)<len)++bit;
	fo(i,0,len-1)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		if (i<rev[i])swap(a[i],a[rev[i]]);
	}//前面和FFT一样
	for (int mid=1;mid<len;mid*=2)
	{
		int tmp=pow(g,(mod-1)/(mid*2));//原根代替单位根
		if (inv==-1)tmp=pow(tmp,mod-2);//逆变换则乘上逆元
		for (int i=0;i<len;i+=mid*2)
		{
			int omega=1;
			for (ll j=0;j<mid;++j,omega=omega*tmp%mod)
			{
				int x=a[i+j],y=omega*a[i+j+mid]%mod;
				a[i+j]=(x+y)%mod,a[i+j+mid]=(x-y+mod)%mod;//注意取模
			}
		}//大体和FFT差不多
	}
}
