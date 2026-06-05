//sjf preemp
#include <stdio.h>
int main(){
    int n, i , time=0, completed=0,shortest;
    printf("Enter the number of processes");
    scanf("%d", &n);
    int at[n],bt[n],ct[n],tat[n],wt[n],rt[n],start[n], sum1=0,sum2=0,sum3=0;
    float avgtat,avgwt,avgrt;
     int order[1000];      // stores process order and idle
    int times[1001];  // stores time points
    int k = 0;
    //times[0]=0;//all 4 lines are for gantt//no need for this line
    times[k]=0;//for gantt
    for (int i=0;i<n;i++){
        printf("Enter the AT and BT of Process%d",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        rt[i]=bt[i];
        start[i]=-1;
    }
    

    while (completed<n){
        shortest=-1;
        for (int i=0;i<n;i++){
            if (at[i]<=time && rt[i]>0){
                if(shortest==-1 || rt[i]<rt[shortest]){
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
        if(start[shortest]==-1){
        
            start[shortest]=time;  
        }
             order[k]=shortest;//
        rt[shortest]--;
        time++;
        k++;//
        times[k] = time;//
       
        if(rt[shortest]==0){
            completed++;
            ct[shortest]=time;
        }
    }
        for (int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
        //  int rt_time[i]=start[i]-at[i];//no need

        sum1+=tat[i];
        sum2+=wt[i];
        sum3+=start[i]-at[i];
    }
    avgtat= (float)sum1 /n;
    avgwt=(float)sum2/n;
    avgrt=(float)sum3/n;

    printf("\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i],start[i]-at[i ]);
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








        
    
