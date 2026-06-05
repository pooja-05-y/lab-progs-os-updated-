//rms
#include <stdio.h>
#include <math.h>

int main() 
{
    int n, time_limit, time = 0, k = 0, current = -2;
    float util = 0.0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int period[n], burst[n], rem[n], order[1000], times[1001];
    times[0] = 0;

    // 1. Take Inputs and Calculate Utilization simultaneously
    for(int i = 0; i < n; i++) {
        printf("Enter Period and Burst for P%d: ", i + 1);
        scanf("%d %d", &period[i], &burst[i]);
        
        rem[i] = burst[i]; 
        util += (float)burst[i] / period[i]; 
    }

    // 2. Perform Schedulability Check
    float bound = n * (pow(2.0, 1.0 / n) - 1.0);
    printf("\n--- System Analysis ---\n");
    printf("Utilization: %.4f | Threshold: %.4f\n", util, bound);
    
    if(util <= bound) printf("Conclusion: DEFINITELY Schedulable\n");
    else if(util <= 1.0) printf("Conclusion: MIGHT be Schedulable\n");
    else printf("Conclusion: NOT Schedulable (Overloaded)\n");

    printf("-----------------------\n\nEnter Simulation Time: ");
    scanf("%d", &time_limit);

    // 3. Core RMS Execution Loop
    while(time < time_limit) {
        int high = -1;
        
        for(int i = 0; i < n; i++) {
            // Replenish burst time if a new period just started
            if(time > 0 && time % period[i] == 0) rem[i] = burst[i];
            
            // Find the ready process with the shortest period
            if(rem[i] > 0 && (high == -1 || period[i] < period[high])) {
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
