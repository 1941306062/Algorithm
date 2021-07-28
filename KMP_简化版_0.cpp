#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
void Get_Next(char *ttr,int *next,int tlen)
{
    next[0]=-1;
    for(int i=1,j=-1;i<tlen;i++)
    {
        while(j>-1 && ttr[j+1]!=ttr[i])
            j=next[j];
        if(ttr[j+1]==ttr[i])
            j++;
 
        next[i]=j;
    }
}
 
int Index_KMP(char *str,int slen,char *ttr,int tlen)
{
    int *next=new int[tlen];
    Get_Next(ttr,next,tlen);
 
    for(int i=0,j=-1;i<slen;i++)
    {
        while(j>-1 && ttr[j+1]!=str[i])
            j=next[j];
        if(ttr[j+1]==str[i])
            j++;
 
        if(j==tlen-1)
            return i-tlen+1;
    }
 
    return -1;
}
 
int Count_KMP(char *str,int slen,char *ttr,int tlen)
{
    int cnt=0;
    int *next=new int[tlen];
    Get_Next(ttr,next,tlen);
 
    for(int i=0,j=-1;i<slen;i++)
    {
        while(j>-1 && ttr[j+1]!=str[i])
            j=next[j];
        if(ttr[j+1]==str[i])
            j++;
 
        if(j==tlen-1)
            cnt++;
    }
 
    return cnt;
}
