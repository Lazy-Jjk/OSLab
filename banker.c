include <stdio.h>
#define MAX_PROC 10
#define MAX_RES 10
void findSafeSeq(int n, int m, int alloc[MAX_PROC][MAX_RES], int max[MAX_PROC][MAX_RES], int 
avail[MAX_RES]);
int main() {
 int n, m; 
 int alloc[MAX_PROC][MAX_RES];
 int max[MAX_PROC][MAX_RES]; 
 int avail[MAX_RES]; 
 printf("Enter number of processes: ");
 scanf("%d", &n);
 printf("Enter number of resources: ");
 scanf("%d", &m);
 printf("Enter allocation matrix:\n");
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 scanf("%d", &alloc[i][j]);
 }
 }
 printf("Enter maximum matrix:\n");
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 scanf("%d", &max[i][j]);
 }
 }
 printf("Enter available resources:\n");
 for (int i = 0; i < m; i++) {
 scanf("%d", &avail[i]);
 }
 findSafeSeq(n, m, alloc, max, avail);
 return 0;
}
void findSafeSeq(int n, int m, int alloc[MAX_PROC][MAX_RES], int max[MAX_PROC][MAX_RES], int 
avail[MAX_RES]) {
 int need[MAX_PROC][MAX_RES];
 int finish[MAX_PROC], safeSeq[MAX_PROC];
 int work[MAX_RES];
 int count = 0;
 for (int i = 0; i < n; i++) finish[i] = 0;
 for (int i = 0; i < m; i++) work[i] = avail[i];
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < m; j++) {
 need[i][j] = max[i][j] - alloc[i][j];
 }
 }
 printf("Safe sequence is: ");
 while (count < n) {
 int found = 0;
 for (int i = 0; i < n; i++) {
 if (!finish[i]) {
 int j;
 for (j = 0; j < m; j++) {
 if (need[i][j] > work[j]) break;
 }
 if (j == m) {
 for (int k = 0; k < m; k++) {
 work[k] += alloc[i][k];
 }
 safeSeq[count++] = i;
 finish[i] = 1;
 found = 1;
 break;
 }
 }
 }
 if (!found) {
 printf("System is in an unsafe state.\n");
 return;
 }
 }
 for (int i = 0; i < n; i++) {
 printf("P%d ", safeSeq[i]);
 }
 printf("\n");
}
