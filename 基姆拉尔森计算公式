//计算某天是星期几

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<queue>
#include<algorithm>
#include<iostream>
#include<map>
#define inf 0x3f3f3f3f
#define ll long long
using namespace std;
int v[3000][500];
int r;
void aa()
{
    int yy,mm,dd;
    r=0;
    for(int i=0; i<400; i++)
    {
        for(int j=1; j<=12; j++)
        {
            for(int k=1; k<30; k+=10)
            {
                yy=i;
                mm=j;
                dd=k;
                if(mm==1||mm==2)
                    mm+=12,yy--;
                int w=(dd+1+2*mm+3*(mm+1)/5+yy+yy/4-yy/100+yy/400)%7;
                if(w==1)
                {
                    v[r][1]=i;
                    v[r][2]=j;
                    v[r][3]=k;
                    r++;
                }
            }
        }
    }
}
int main()
{
    aa();
    int t,y,m,d,n;
    while(~scanf("%d",&t))
    {
        while(t--)
        {
            scanf("%d%d%d%d",&y,&m,&d,&n);
            n--;
            int res=y/400;
            y%=400;
            int flag;
            for(int i=0; i<r; i++)
            {
                if(v[i][1]==y&&v[i][2]==m&&v[i][3]==d)
                    flag=i;
            }
            res+=(flag+n)/2058;
            flag=(flag+n)%2058;
            res=res*400+v[flag][1];
            printf("%d %d %d\n",res,v[flag][2],v[flag][3]);
        }
    }
    return 0;
}
