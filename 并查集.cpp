#include"iostream"
#include"cstdio"
#include"stdlib.h"
#include"cmath"
#include"cstring"
#include"cstdlib"
#include"vector"
#include"stack"
#include"queue"
#include"set"
#include"map"
#include"algorithm"
#include <utility>
#include <iomanip>
#include <time.h>
#include<list>
using namespace std;
#define MIN(a, b) ((a)<(b)?(a):(b))
const int M=50000;
int n,k;
int f[M*3+10];//并查集的树高,high[M*3+10]
int value[M];
void inti(int n){///初始化
    for(int i=0;i<=n;i++){
        f[i]=i;
        value[i]=0;
        //rel[i]=0;
    }
}
int finds(int x){///搜索
    return f[x] == x ? x : f[x] = finds(f[x]);
    /*带权
        if(x!=f[x]){
            int tmp=f[x];
            f[x]=finds(f[x]);
            value[x]+=value[tmp];
        }
        return f[x];
        种类
        if(x!=f[x]){
            int tmp=f[x];
            f[x]=finds(f[x]);
            rel[x]=(rel[x]+rel[tmp])%3;
        }
        return f[x];
    */
}
void union_set(int x,int y){///合并
    int fx=finds(x);
    int fy=finds(y);
    if(fx!=fy)
        f[fy]=fx;
    /*带权
   // int x,int y,int w
    int fx=finds(x);
    int fy=finds(y);
    if(fx!=fy){
        f[fy]=fx;
        value[fy]=value[x]+w-value[y];
    }
    bool Check(int x,int y,int w){
    int fx = finds(x);
    int fy = finds(y);
    if(fx==fy){
        return w == value[fy] - value[x] + value[y];
    }
    return true;

    种类
    bool Union(int x,int y,int flag){
    int fx=Find(x);
    int fy=Find(y);
    if(fx!=fy){
        F[fy]=fx;
        rel[fy]=(3+flag+rel[x]-rel[y])%3;
    	return true;
    }else{
        return flag == (3+rel[y]+rel[fy]-rel[x])%3; // 当然和前文一样,此处的rel[fy]确实是为0,可以省略,但为了保持格式统一,依然保留
    }
}

}

    */
}
bool same(int x,int y){
    return finds(x)==finds(y);
}
int main()
{
    int t,x,y;

    scanf("%d%d",&n,&k);
        inti(n*3);
        int ans=0;
        for(int i=0;i<k;i++)
        {
            scanf("%d%d%d",&t,&x,&y);
            if(x<1||x>n||y<1||y>n){
                ans++;
                continue;
            }

            if(t==1){   //x和y属于同一类的信息
                if(finds(x)==finds(y+n)||finds(y)==finds(x+n)){//如果x吃y或者y吃x，说明是假话
                    ans++;
                }
                else {//合并
                    union_set(x,y);
                    union_set(x+n,y+n);
                    union_set(x+2*n,y+2*n);
                }

            }
            else {
                //x吃y的信息
                if(finds(x)==finds(y)||finds(y)==finds(x+n)){//如果x和y同组，或者y吃x,就是假话
                    ans++;
                }
                else {//存入吃的信息
                    union_set(x,y+n);
                    union_set(x+n,y+2*n);
                    union_set(x+n*2,y);
                }
            }
        }
        cout<<ans<<endl;


    return 0;
}

