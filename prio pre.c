#include <stdio.h>
struct Process {
    int id, bt, at, pr, rt, wt, tat;
};

int main() {
    int n, t = 0, completed = 0, min_pr, idx;
    float total_wt = 0, total_tat = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        printf("Enter AT, BT, Priority for P%d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
    }

    while (completed < n) {
        min_pr = 1e9;
        idx = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0 && p[i].pr < min_pr) {
                min_pr = p[i].pr;
                idx = i;
            }
        }
        if (idx != -1) {
            p[idx].rt--;
            t++;
            if (p[idx].rt == 0) {
                completed++;
                p[idx].tat = t - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
            }
        } else t++;
    }

    printf("Avg WT: %.2f\nAvg TAT: %.2f\n", total_wt / n, total_tat / n);
    return 0;
}
