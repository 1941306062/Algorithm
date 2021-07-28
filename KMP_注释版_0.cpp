

/*
    时间复杂度：如果文本串的长度为n，模式串的长度为m，那么匹配过程的时间复杂度为O(n)，算上计算next的O(m)时间，KMP的整体时间复杂度为O(m + n)。
    算法说明：
            1、先通过目标串（ttr）计算出对应的首尾最长前后缀长度（next[]）对应的值
            2、再通过计算出的（next[]）“智能”处理目标串在主串中的匹配过程
*/
 
#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
/*
    功能：
        获取 next 数组的值：计算目标串前后缀相同的字符个数
    输入：
         ttr：目标串（下标从0开始）
        next：目标串的最长前缀和最长后缀相同的长度，[标记:长度]=>[-1:0],[0:1],[1:2],[n:n+1]。
              如："ababaca"，长度是7，所以next[0]，next[1]，next[2]，next[3]，next[4]，next[5]，next[6]分别计算的是 a，ab，aba，abab，ababa，ababac，ababaca 的相同的最长前缀和最长后缀的长度。
              由于 a，ab，aba，abab，ababa，ababac，ababaca 的相同的最长前缀和最长后缀是""，""，"a"，"ab"，"aba"，""，"a",所以next数组的值是[-1,-1,0,1,2,-1,0]
        tlen：目标串长度
*/
void Get_Next(char *ttr,int *next,int tlen)
{
    next[0]=-1; // next[0] 初始化为 -1，-1 表示不存在相同的最大前缀和最大后缀
    for(int i=1,j=-1;i<tlen;i++)
    {
        while(j>-1 && ttr[j+1]!=ttr[i]) // 如果下一个不同，那么 j 就变成 next[j]，注意 next[j] 是小于 j 的，无论 j 取任何值
            j=next[j]; // 往前回溯
        if(ttr[j+1]==ttr[i]) // 如果相同，j++
            j++;
 
        next[i]=j; // 这是把算好的 j 值（就是相同的最大前缀和最大后缀长度）赋给 next[i]
    }
}
 
/*
    功能：
        在主串中匹配目标串；代码和 Get_Next(...) 很类似
    输入：
         str：主串（下标从0开始）
        slen：主串长度
         ttr：目标串（下标从0开始）
        tlen：目标串长度
    输出：
        若存在，返回第一个字符匹配成功的位置（下标从0开始）；否则，返回-1
*/
int Index_KMP(char *str,int slen,char *ttr,int tlen)
{
    int *next=new int[tlen];
    Get_Next(ttr,next,tlen);
 
    for(int i=0,j=-1;i<slen;i++)
    {
        while(j>-1 && ttr[j+1]!=str[i]) // ttr 和 str 不匹配，且 j>-1：表示 ttr 和 str 有部分匹配
            j=next[j]; // 往前回溯
        if(ttr[j+1]==str[i])
            j++;
 
        if(j==tlen-1) // 说明 j 移动到 ttr 的最末端，匹配完成（成功）
        {
            return i-tlen+1; // 返回相应的位置（首字符匹配的位置，下标从0开始）
        }
    }
    return -1; // 匹配失败
}
 
/*
    功能：
        目标串在主串中出现的次数（可重叠）；代码和 Get_Next(...) 很类似
    输入：
         str：主串（下标从0开始）
        slen：主串长度
         ttr：目标串（下标从0开始）
        tlen：目标串长度
    输出：
        返回出现（匹配成功）的次数
*/
int Count_KMP(char *str,int slen,char *ttr,int tlen)
{
    int cnt=0;
    int *next=new int[tlen];
    Get_Next(ttr,next,tlen);
 
    for(int i=0,j=-1;i<slen;i++)
    {
        while(j>-1 && ttr[j+1]!=str[i]) // ttr 和 str 不匹配，且 j>-1：表示 ttr 和 str 有部分匹配
            j=next[j]; // 往前回溯
        if(ttr[j+1]==str[i])
            j++;
 
        if(j==tlen-1) // 说明 j 移动到 ttr 的最末端，匹配完成（成功）
        {
            //j=-1; // 无须此代码，因为通过 next[] 可处理 j 的值
            //i=i-tlen+1; // 无须此代码（主串往前回溯），因为通过 next[] 可处理这过程
            cnt++;
        }
    }
    return cnt; // 返回匹配成功的次数
}
