#include <stdio.h>
#include <limits.h>

void findWaitingTime(int n, int bt[], int at[], int wt[]) {
    int remaining_bt[n];
    for (int i = 0; i < n; i++) remaining_bt[i] = bt[i];

    int complete = 0, t = 0;
    int minm = INT_MAX, shortest = -1;
    int finish_time;
    int check = 0;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if (at[j] <= t && remaining_bt[j] < minm && remaining_bt[j] > 0) {
                minm = remaining_bt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        remaining_bt[shortest]--;

        minm = remaining_bt[shortest];
        if (minm == 0) minm = INT_MAX;

        if (remaining_bt[shortest] == 0) {
            complete++;
            check = 0;

            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0) wt[shortest] = 0;
        }

        t++;
    }
}

void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int n, int bt[], int at[]) {
    int wt[n], tat[n];
    int totalWT = 0, totalTAT = 0;

    findWaitingTime(n, bt, at, wt);
    findTurnAroundTime(n, bt, wt, tat);

    printf("P\tAT\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time = %.2f\n", (float)totalWT / n);
    printf("Average Turnaround Time = %.2f\n", (float)totalTAT / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];
    
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &at[i]);
    }

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    findAvgTime(n, bt, at);
    return 0;
}nv
