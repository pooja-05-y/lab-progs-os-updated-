//prio preemp
#include <stdio.h>

int main()
{
    int n, time = 0, completed = 0, highest, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], pr[n];
    int rt[n], ct[n], tat[n], wt[n], start[n];

    int sumtat = 0, sumwt = 0, sumrt = 0;

    float avgtat, avgwt, avgrt;

    int order[1000];
    int times[1001];
    int k = 0;

    times[k] = 0;

    for(i = 0; i < n; i++)
    {
        printf("Enter AT BT Priority for P%d: ", i + 1);
        scanf("%d %d %d", &at[i], &bt[i], &pr[i]);

        rt[i] = bt[i];
        start[i] = -1;
    }

    while(completed < n)
    {
        highest = -1;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(highest == -1 || pr[i] < pr[highest])
                    highest = i;
            }
        }

        if(highest == -1)
        {
            order[k] = -1;

            time++;
            k++;
            times[k] = time;

            continue;
        }

        if(start[highest] == -1)
        {
            start[highest] = time;
        }

        order[k] = highest;

        rt[highest]--;
        time++;

        k++;
        times[k] = time;

        if(rt[highest] == 0)
        {
            completed++;

            ct[highest] = time;
        }
    }

    for(i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        sumtat += tat[i];
        sumwt += wt[i];
        sumrt += start[i] - at[i];
    }

    avgtat = (float)sumtat / n;
    avgwt  = (float)sumwt / n;
    avgrt  = (float)sumrt / n;

    printf("\nP\tAT\tBT\tPRI\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1,
               at[i],
               bt[i],
               pr[i],
               ct[i],
               tat[i],
               wt[i],
               start[i] - at[i]);
    }

    printf("\nAverage TAT = %.2f", avgtat);
    printf("\nAverage WT  = %.2f", avgwt);
    printf("\nAverage RT  = %.2f\n", avgrt);

    printf("\nGantt Chart:\n\n|");

    for(i = 0; i < k; i++)
    {
        if(order[i] == -1)
            printf(" IDLE |");
        else
            printf(" P%d |", order[i] + 1);
    }

    printf("\n");

    for(i = 0; i <= k; i++)
    {
        printf("%d\t", times[i]);
    }

    printf("\n");

    return 0;
}
