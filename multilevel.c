//multilevel
#include <stdio.h>

int main()
{
    int n;
     int completed = 0;
    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], wt[n], tat[n];
    int type[n], done[n];
    float totalWT = 0;
    float totalTAT = 0;

    int order[2 * n];
    int times[2 * n + 1];
    int k = 0;

    times[0] = 0;

    for(int i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);// can include three inputs in one

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Enter Type (0-System, 1-User): ");
        scanf("%d", &type[i]);

        done[i] = 0;
    }

   

    while(completed < n)
    {
        int idx = -1;

        /* Search System Queue First */
        for(int i = 0; i < n; i++)
        {
            if(done[i] == 0 &&
               at[i] <= time &&
               type[i] == 0)
            {
                if(idx == -1 || at[i] < at[idx])
                    idx = i;
            }
        }

        /* Search User Queue if no System Process */
        if(idx == -1)
        {
            for(int i = 0; i < n; i++)
            {
                if(done[i] == 0 &&
                   at[i] <= time &&
                   type[i] == 1)
                {
                    if(idx == -1 || at[i] < at[idx])
                        idx = i;
                }
            }
        }

        /* CPU Idle */
        if(idx == -1)
        {
            order[k] = -1;

            time++;

            k++;
            times[k] = time;

            continue;
        }

        order[k] = idx;

        time += bt[idx];

        k++;
        times[k] = time;

        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        done[idx] = 1;
        completed++;
    }

  

    printf("\nP\tTYPE\tAT\tBT\tCT\tWT\tTAT\n");

    for(int i = 0; i < n; i++)
    {
        printf("P%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               type[i] == 0 ? "SYS" : "USR",
               at[i],
               bt[i],
               ct[i],
               wt[i],
               tat[i]);

        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nAverage WT = %.2f", totalWT / n);
    printf("\nAverage TAT = %.2f\n", totalTAT / n);

    printf("\nGantt Chart:\n\n|");

    for(int i = 0; i < k; i++)
    {
        if(order[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", order[i] + 1);
    }

    printf("\n");

    for(int i = 0; i <= k; i++)
    {
        printf("%d\t", times[i]);
    }

    printf("\n");

    return 0;
}
