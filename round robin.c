//round robin
#include <stdio.h>

int main() {
    int n, tq, time = 0, completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Process and Queue arrays
    int at[n], bt[n], rt[n], tat[n], wt[n], start[n], in_queue[n];
    int queue[1000], front = 0, rear = 0;

    // Gantt Chart tracking arrays
    int order[1000];
    int times[1001];
    int k = 0;
    times[0] = 0;

    // Input loop
    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        
        rt[i] = bt[i];      // Remaining time
        in_queue[i] = 0;    // Queue tracker
        start[i] = -1;      // First execution tracker
    }

    // Core Round Robin Logic
    while (completed < n) {
        
        // 1. Add newly arrived processes to the queue
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && in_queue[i] == 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        // 2. Idle handling
        if (front == rear) {
            // If the last block was also idle, just extend the time
            if (k > 0 && order[k-1] == -1) {
                time++;
                times[k] = time; 
            } else {
                order[k] = -1; // -1 means IDLE
                time++;
                k++;
                times[k] = time;
            }
            continue;
        }

        // 3. Dequeue process
        int p = queue[front++];
        if (start[p] == -1) start[p] = time; // Log first start time

        // Log process in Gantt chart
        order[k] = p;

        // 4. Run the process (tick by tick to check for new arrivals)
        int run_time = (rt[p] < tq) ? rt[p] : tq;
        
        for (int t = 0; t < run_time; t++) {
            time++;
            rt[p]--;
            
            for (int i = 0; i < n; i++) {
                if (at[i] <= time && in_queue[i] == 0) {
                    queue[rear++] = i;
                    in_queue[i] = 1;
                }
            }
        }

        // Update end time for this block in the Gantt chart
        k++;
        times[k] = time;

        // 5. Check completion
        if (rt[p] == 0) {
            completed++;
            tat[p] = time - at[p];
            wt[p] = tat[p] - bt[p];
        } else {
            queue[rear++] = p; // Requeue if not finished
        }
    }

    // Print Results Table
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        int current_rt = start[i] - at[i];
        int ct = at[i] + tat[i]; // CT is Arrival Time + Turnaround Time
        
        sum_tat += tat[i];
        sum_wt += wt[i];
        sum_rt += current_rt;
        
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct, tat[i], wt[i], current_rt);
    }

    // Print Averages
    printf("\nAvg TAT: %.2f\nAvg WT: %.2f\nAvg RT: %.2f\n", sum_tat / n, sum_wt / n, sum_rt / n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n\n|");
    for (int i = 0; i < k; i++) {
        if (order[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", order[i] + 1);
    }
    
    printf("\n");
    
    for (int i = 0; i <= k; i++) {
        printf("%d\t", times[i]);
    }
    printf("\n");

    return 0;
}
