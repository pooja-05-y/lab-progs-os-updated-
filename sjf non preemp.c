//sjf non preemp
// -- lines for gantt
#include <stdio.h>
int main(){
    int n, i , time=0, completed=0,shortest;
    printf("Enter the number of processes");
    scanf("%d", &n);
    int at[n],bt[n],ct[n],tat[n],wt[n],rt[n], sum1=0,sum2=0,sum3=0;
    float avgtat,avgwt,avgrt;
    int visited[n];
     int order[2 * n];      // stores process order and idle
    int times[2 * n + 1];  // stores time points
    int k = 0;//all 3 lines are for gantt
    times[k]=0;//for gantt
    for (int i=0;i<n;i++){
        printf("Enter the AT and BT of Process%d",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        visited[i]=0;
    }
   

    while (completed<n){
        shortest=-1;
        for (int i=0;i<n;i++){
            if (at[i]<=time && visited[i]==0){
                if(shortest==-1 || bt[i]<bt[shortest]){
                    shortest=i;
                }
            }
        }
        if (shortest==-1){
            order[k]=-1;//
            time++;
            k++;//
            times[k]=time;  //
            continue;
        }
        order[k]=shortest; //
        time+=bt[shortest];
        ct[shortest]=time;
        visited[shortest]=1;
        completed++;

        tat[shortest]=ct[shortest]-at[shortest];
        wt[shortest]=tat[shortest]-bt[shortest];
        rt[shortest]=wt[shortest];

        sum1+=tat[shortest];
        sum2+=wt[shortest];
        sum3+=rt[shortest];
        k++;//
        times[k]=time;//
    }
    avgtat= (float)sum1 /n;
    avgwt=(float)sum2/n;
    avgrt=(float)sum3/n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i],rt[i]);
    }

    printf("\nAverage TAT=%f",avgtat);
    printf("\nAverage WT=%f",avgwt);
    printf("\nAverage RT=%f",avgrt);

       printf("\nGantt Chart:\n\n|");

    for(i = 0; i < k; i++)
    {
        if(order[i] == -1)
            printf(" IDLE |  ");
        else
            printf(" P%d |   ", order[i] + 1);
    }

    printf("\n");

    for(i = 0; i <= k; i++)
    {
        printf("%d\t", times[i]);
    }

    printf("\n");

    return 0;
}
