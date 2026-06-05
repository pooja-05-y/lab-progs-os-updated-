//prio non preemp
#include<stdio.h>

int main(){
    int n,i,time=0,completed=0,highest;
    printf("Enter the number of processes");
    scanf("%d",&n);
    int at[n],bt[n],ct[n],pr[n],tat[n],wt[n],rt[n];
    int sumtat=0,sumwt=0,sumrt=0;
    int visited[n];
    int order[2*n];
    int times[2*n+1];
    int k=0;
    times[k]=0;
    float avgtat,avgwt,avgrt;
    for(i=0;i<n;i++){
        printf("enter at and bt and priority for process%d",i+1);
        scanf("%d %d %d",&at[i],&bt[i],&pr[i]);
        visited[i]=0;
    }
    while(completed<n){
        highest=-1;
        for (i=0;i<n;i++){
            if (at[i]<=time && visited[i]==0 ){
                if (highest==-1 || pr[i]< pr[highest]){//
                    highest=i;
                }
                }
            }
            if (highest==-1){
                order[k]=-1;
                time++;
                k++;
                times[k]=time;
                continue;
            }
            rt[highest]=time-at[highest];// here only
            order[k]=highest;
            time+=bt[highest];
            ct[highest]=time;
            visited[highest]=1;
            completed++;
            k++;
            times[k]=time;

            tat[highest]=ct[highest]-at[highest];
            wt[highest]=tat[highest]-bt[highest];
        
            

            sumtat+=tat[highest];
            sumwt+=wt[highest];
            sumrt+=rt[highest];

        }
        avgtat=(float)sumtat/n;
        avgwt=(float)sumwt/n;
        avgrt=(float)sumrt/n;

        printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
        for (i=0;i<n;i++){
            printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i],rt[i]);
        }
        printf("\n");
        printf("AverageTAT: %0.2f",avgtat);
        printf("AverageWT: %0.2f",avgwt);
        printf("AverageRT: %0.2f",avgrt);
        printf("\n");
        printf("Gantt Chart");
        for(i=0;i<k;i++){
            if(order[i]==-1){;
                printf(" IDLE | ");
            }
            else{ printf(" P%d  |",order[i]+1);
            }
        }
        printf("\n");
        for (i=0;i<=k;i++){
            printf("%d   ",times[i]);
        }
        return 0;
    }
