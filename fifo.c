//fifo
#include <stdio.h>

int main()
{
    int n, frames;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string: ");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int frame[frames];

    for(int i = 0; i < frames; i++)
    {
        frame[i] = -1;
    }

    int fault = 0;
    int index = 0;

    for(int i = 0; i < n; i++)
    {
        int found = 0;

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if(!found)
        {
            frame[index] = pages[i];

            index = (index + 1) % frames;

            fault++;
        }

        printf("\n");

        for(int j = 0; j < frames; j++)
        {
            if(frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
    }

    printf("\n\nTotal Page Faults = %d\n", fault);

    return 0;
}
