#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure storing train's information.
typedef struct announcement
{
    char train_name[50];
    float arrival;
    float departure;
} TRAIN;

TRAIN train_list[20];

int train_count = 0;

// Function:    bfss
// Description: brute force string search 
// Input param: text and pattern
// Return Type: index or -1
int bfss(char *txt, char *pat)
{
    int m = strlen(pat);
    int n = strlen(txt);

    for (int i = 0; i <= n - m; i++)
    {
        int j;
        for (j = 0; j < m; j++)
        {
            if (pat[j] != txt[i + j])
                break;
        }

        if (j == m)
            return i;
    }

    return -1;
}

// Function:    search_train
// Description: searches train and returns index if found
// Input param: train name, trains pointer, and size
// Return Type: index or -1
int search_train(char *train, TRAIN *trains, int size)
{
    int i;

    for (i = 0; i < size; i++)
    {
        int index = bfss(trains[i].train_name, train);
        if (index != -1)
        {
            return i;
        }
    }

    return -1;
}

// Function:    announce
// Description: Takes input and displays train's result
// Input param: trains pointer and size
// Return Type: NULL
void announce(TRAIN *trains, int size)
{
    char train[20];
    printf("Enter your train name (First letter capital): ");
    scanf("%s", train);

    int index = search_train(train, trains, size);

    if (index != -1)
    {
        printf("Train found! Train %s arrival time is %.2f and departure time is %.2f at platform number %d\n",trains[index].train_name, trains[index].arrival, trains[index].departure, index + 1);
    }
    else
    {
        printf("Train not found\n");
    }
}

// Function:        load_from_file
// Description:     reads file
// Input parameter: NULL
// Return type:     NULL
void load_from_file(TRAIN *trains, int size)
{
    FILE *fp;

    fp = fopen("train_list.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    int i = 0;
    while (!feof(fp) && i < size)
    {
        fscanf(fp, "%s %f %f", trains[i].train_name, &trains[i].arrival, &trains[i].departure);
        i++;
    }
    fclose(fp);
}

// Function:        bubble_sort
// Description:     sorts array
// Input parameter: trains pointer and size
// Return type:     NULL
void bubble_sort(TRAIN *trains, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (strcmp(trains[j].train_name, trains[j + 1].train_name) > 0)
            {
                // Swap the trains if they are in the wrong order
                TRAIN temp = trains[j];
                trains[j] = trains[j + 1];
                trains[j + 1] = temp;
            }
        }
    }
    // Display the sorted array
    printf("***Trains***\n");
    printf("Train_name with train arrival and departure timings:\n");

    for (int i = 3; i < 21; i++)
    {
        printf("%s\n%.2f\t%.2f\n\n", trains[i].train_name, trains[i].arrival, trains[i].departure);
    }

}

int main()
{
    TRAIN trains[24];

    load_from_file(trains, 24);

    bubble_sort(trains, 24);

    announce(trains, 24);

    return 0;
}