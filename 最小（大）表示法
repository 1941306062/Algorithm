int get_min(string s)//最小表示法  get_max最大表示法
{
    int len=s.size();
    int i=0,j=1,k=0,t;
    while(i<len&&j<len&&k<len){
        t=s[(i+k)%len]-s[(j+k)%len];
        if(!t) k++;
        else{
                //最大-i j 互换
            if(t>0) i+=k+1;
            else j+=k+1;
            if(i==j) j++;
            k=0;
        }
    }
    return i>j?j:i;
}
