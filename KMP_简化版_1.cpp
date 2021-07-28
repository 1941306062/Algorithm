int kmp(char *str,int slen,char *ttr,int tlen)
{
//    int rs = 0; // Count
    int *next=new int[tlen+1];
    next[0] =  -1;
    for (int i=0,j=-1;i<tlen;i++)
    {
        while (j!=-1 && ttr[i]!=ttr[j])
            j = next[j];
        next[i+1] = ++j;
    }
 
    for (int i=0,j=0;i<slen;i++)
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
