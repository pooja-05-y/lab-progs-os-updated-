//optimal
#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f, i, j, k;
    int pageFaults = 0, found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1;

    for(i = 0; i < n; i++) {
        found = 0;

        // Check if page already exists
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if(!found) {
            int replace = -1;

            // Empty frame available
            for(j = 0; j < f; j++) {
                if(frames[j] == -1) {
                    replace = j;
                    break;
                }
            }

            // Find optimal replacement
            if(replace == -1) {
                int farthest = -1;

                for(j = 0; j < f; j++) {
                    int nextUse = n; // assume never used again

                    for(k = i + 1; k < n; k++) {
                        if(frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest) {
                        farthest = nextUse;
                        replace = j;
                    }
                }
            }

            frames[replace] = pages[i];
            pageFaults++;
        }

        printf("Page %d -> ", pages[i]);
        for(j = 0; j < f; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);

    return 0;
}
