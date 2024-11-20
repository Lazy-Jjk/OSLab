#include<stdio.h>
void findAvgTime(int n,int bt[],int at[],int q){
    int wt[n],tat[n],rem[n];
    int t=0,i,complete=0;
    int totalWT=0,totalTAT=0;
    for(i=0;i<n;i++)rem[i]=bt[i];
    for(i=0;i<n;i++)wt[i]=0;
    while(complete!=n){
        int done=0;
        for(i=0;i<n;i++){
            if(rem[i]>0){
                if(rem[i]>q){
                    rem[i]-=q;
                    t+=q;
                }else{
                    t+=rem[i];
                    wt[i]=t-bt[i]-at[i];
                    if(wt[i]<0)wt[i]=0;
                    rem[i]=0;
                    complete++;
                }
                done=1;
            }
        }
        if(!done)t++;
    }
    for(i=0;i<n;i++)tat[i]=bt[i]+wt[i];
    printf("ID BT AT WT TAT\n");
    for(i=0;i<n;i++){
        totalWT+=wt[i];
        totalTAT+=tat[i];
        printf("%d  %d  %d  %d  %d\n",i+1,bt[i],at[i],wt[i],tat[i]);
        
    }
    printf("Average Wt:%.2f\n",(float)totalWT/n);
    printf("Average TAt:%.2f\n",(float)totalTAT/n);
}
int main() {
 int bt[] = {5,5,7,7};
 int at[] = {0,1,2,3};
 int q = 4;
 int n = sizeof(bt)/sizeof(bt[0]);
 findAvgTime(n, bt, at, q);
 return 0;
}
