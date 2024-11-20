#include <stdio.h>
void findWT(int n, int bt[], int at[], int wt[]) {
 wt[0] = 0;
 for (int i = 1; i < n; i++) {
 wt[i] = bt[i-1] + wt[i-1] - at[i] + at[i-1];
 if (wt[i] < 0) wt[i] = 0;
 }
}
void findTAT(int n, int bt[], int wt[], int tat[]) {
 for (int i = 0; i < n; i++) {
 tat[i] = bt[i] + wt[i];
 }
}
void findAvgTime(int n, int bt[], int at[]) {
 int wt[n], tat[n];
 int totalWT = 0, totalTAT = 0;
 findWT(n, bt, at, wt);
 findTAT(n, bt, wt, tat);
 printf("ID BT AT WT TAT\n");
 for (int i = 0; i < n; i++) {
 totalWT += wt[i];
 totalTAT += tat[i];
 printf("%d %d %d %d %d\n", i+1, bt[i], at[i], wt[i], tat[i]);
 }
 printf("Avg WT = %.2f\n", (float)totalWT / n);
 printf("Avg TAT = %.2f\n", (float)totalTAT / n);
}
int main() {
    int r;
    printf("r:",r);
    scanf("%d",&r);
    int bt[r],at[r];
    printf("Enter burst time values:\n");
    for(int i=0;i<r;i++){
        scanf("%d",&bt[i]);
    }
    printf("\nEnter arrival time values:");
    for(int i=0;i<r;i++){
        scanf("%d",&at[i]);
    }
    
 int n = sizeof(bt) / sizeof(bt[0]);
 findAvgTime(n, bt, at);
 return 0;
}
