//edf
#include <stdio.h>

int main() 
{
    int n, time_limit, time = 0, k = 0, current = -2;
    float util = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Added rel_deadline (input) and abs_deadline (ticking clock)
    int period[n], burst[n], rem[n], rel_deadline[n], abs_deadline[n];
    int order[1000], times[1001];
    times[0] = 0;

    // 1. Take Inputs and Calculate Utilization
    for(int i = 0; i < n; i++) {
        printf("Enter Period, Burst Time, and Deadline for P%d: ", i + 1);
        scanf("%d %d %d", &period[i], &burst[i], &rel_deadline[i]);
        
        rem[i] = burst[i]; 
        abs_deadline[i] = rel_deadline[i]; // First absolute deadline is just the relative deadline
        
        util += (float)burst[i] / period[i]; 
    }

    // 2. Perform Schedulability Check
    printf("\n--- System Analysis ---\n");
    printf("Utilization: %.4f | Threshold: 1.0000\n", util);
    
    // Note: If Deadlines < Periods, 100% utilization might still fail, but 1.0 is the standard bound.
    if(util <= 1.0) printf("Conclusion: Schedulable (Assuming Deadlines >= Periods)\n");
    else printf("Conclusion: NOT Schedulable (Overloaded)\n");

    printf("-----------------------\n\nEnter Simulation Time: ");
    scanf("%d", &time_limit);

    // 3. Core EDF Execution Loop
    while(time < time_limit) {
        int high = -1;
        
        for(int i = 0; i < n; i++) {
            // Replenish burst time AND set the new absolute deadline for the new period
            if(time > 0 && time % period[i] == 0) {
                rem[i] = burst[i];
                abs_deadline[i] = time + rel_deadline[i]; // Master clock + Relative limit
            }
            
            // EDF Rule: Find the ready process with the EARLIEST absolute deadline
            if(rem[i] > 0 && (high == -1 || abs_deadline[i] < abs_deadline[high])) {
                high = i;
            }
        }

        // Log Gantt chart ONLY when CPU switches processes
        if(high != current) {
            order[k] = high;
            times[k++] = time;
            current = high;
        }

        // Execute the chosen process for 1 second
        if(high != -1) rem[high]--;
        time++;
    }
    
    times[k] = time; // Cap the final timeline

    // 4. Print Gantt Chart
    printf("\nGantt Chart:\n\n|");
    for(int i = 0; i < k; i++) {
        if(order[i] == -1) printf(" IDLE |");
        else printf(" P%d |", order[i] + 1);
    }
    
    printf("\n");
    for(int i = 0; i <= k; i++) printf("%d\t", times[i]);
    printf("\n");

    return 0;
}
