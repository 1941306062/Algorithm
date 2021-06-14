/*
    功能：
        1、【标记 // Index】目标串在主串中首次匹配的索引值
        2、【标记 // Count】目标串在主串中出现的次数（可重叠）
    输入：
         str：主串（下标从0开始）
        slen：主串长度
         ttr：目标串（下标从0开始）
        tlen：目标串长度
    输出：
        1、【标记 // Index】返回首次匹配成功的索引值，否则返回 -1
        2、【标记 // Count】返回出现（匹配成功）的次数
    提示：
        next[i]：
       ----------------------------------------
            i	0	1	2	3	4	5	6	7
        模式串	A	B	C	D	A	B	D	'\0'
       next[i] -1	0	0	0	0	1	2	0
*/
int kmp(char *str,int slen,char *ttr,int tlen)
{
//    int rs = 0; // Count
    int *next=new int[tlen+1]; // +1 是因为为了计算最长模式子串时的真前后缀相同长度
    next[0] =  -1;
    for (int i=0,j=-1;i<tlen;i++) // Get_Next
    {
        while (j!=-1 && ttr[i]!=ttr[j])
            j = next[j];
        next[i+1] = ++j;
    }
 
    for (int i=0,j=0;i<slen;i++) // Index_KMP or Count_KMP
    {
        while (j!=-1 && str[i]!=ttr[j])
            j = next[j];
        if (++j==tlen)
        {
//            rs++; // Count
            return i-j+1; // Index
        }
    }
 
//    return rs; // Count
    return -1; // Index
}
