//mem alloc
#include <stdio.h>
int main()
{
    int memory[50], process[50];
    int m, n;
    int i, j;
    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d memory blocks:\n", m);
    for(i = 0; i < m; i++)
    {
        scanf("%d", &memory[i]);
    }
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes:\n", n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &process[i]);
    }
    int firstFit[50];
    int tempMemory1[50];
    for(i = 0; i < m; i++)
        tempMemory1[i] = memory[i];
    for(i = 0; i < n; i++)
    {
        firstFit[i] = -1;
        for(j = 0; j < m; j++)
        {
            if(tempMemory1[j] >= process[i])
            {
                firstFit[i] = j;
                tempMemory1[j] -= process[i];
                break;
            }
        }
    }

    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(firstFit[i] != -1)
            printf("%d\n", firstFit[i] + 1);
        else
            printf("Not Allocated\n");
    }

    int bestFit[50];
    int tempMemory2[50];

    for(i = 0; i < m; i++)
        tempMemory2[i] = memory[i];

    for(i = 0; i < n; i++)
    {
        int bestIndex = -1;

        for(j = 0; j < m; j++)
        {
            if(tempMemory2[j] >= process[i])
            {
                if(bestIndex == -1 ||
                   tempMemory2[j] < tempMemory2[bestIndex])
                {
                    bestIndex = j;
                }
            }
        }

        if(bestIndex != -1)
        {
            bestFit[i] = bestIndex;
            tempMemory2[bestIndex] -= process[i];
        }
        else
        {
            bestFit[i] = -1;
        }
    }

    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(bestFit[i] != -1)
            printf("%d\n", bestFit[i] + 1);
        else
            printf("Not Allocated\n");
    }

    int worstFit[50];
    int tempMemory3[50];

    for(i = 0; i < m; i++)
        tempMemory3[i] = memory[i];

    for(i = 0; i < n; i++)
    {
        int worstIndex = -1;

        for(j = 0; j < m; j++)
        {
            if(tempMemory3[j] >= process[i])
            {
                if(worstIndex == -1 ||
                   tempMemory3[j] > tempMemory3[worstIndex])
                {
                    worstIndex = j;
                }
            }
        }

        if(worstIndex != -1)
        {
            worstFit[i] = worstIndex;
            tempMemory3[worstIndex] -= process[i];
        }
        else
        {
            worstFit[i] = -1;
        }
    }

    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t", i + 1, process[i]);

        if(worstFit[i] != -1)
            printf("%d\n", worstFit[i] + 1);
        else
            printf("Not Allocated\n");
    }

    return 0;
}
