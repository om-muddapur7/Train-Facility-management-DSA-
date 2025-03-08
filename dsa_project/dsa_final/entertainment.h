#ifndef ENTERTAINMENT_H_INCLUDED
#define ENTERTAINMENT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store pincode, and entertainment plays
typedef struct entertainment
{
    int  pincode;
    char channels[10];
    char music[10];
} ENT;

// Function:        load_from_file_entertain
// Description:     reads file
// Input parameter: NULL
// Return type:     NULL
void load_from_file_entertain(ENT *fun, int size)
{
    FILE *fp;

    fp = fopen("entertainment_list.txt", "r");

    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    int i = 0;
    while (!feof(fp) && i < size)
    {
        fscanf(fp, "%d %s %s", &fun[i].pincode, fun[i].channels, fun[i].music);
        i++;
    }
    fclose(fp);
}

// Function:        merge
// Description:     sorts the array according to pincode
// Input parameter: fun pointer,start,middle,end index
// Return type:     NULL
void merge(ENT *fun, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    ENT L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = fun[l + i];
    for (j = 0; j < n2; j++)
        R[j] = fun[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].pincode <= R[j].pincode)
        {
            fun[k] = L[i];
            i++;
        }
        else
        {
            fun[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        fun[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        fun[k] = R[j];
        j++;
        k++;
    }
}

// Function:        merge_sort
// Description:     divides the array into halves
// Input parameter: fun pointer,start,end index
// Return type:     NULL
void merge_sort(ENT *fun, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        merge_sort(fun, l, m);
        merge_sort(fun, m + 1, r);

        merge(fun, l, m, r);
    }
}

// Function:        display_play
// Description:     prints sorted values
// Input parameter: fun pointer
// Return type:     NULL
void display_play(ENT *fun)
{
    printf("Sorted Entertainment Plays:\n");
    for (int i = 5; i < 105; i++)
    {
        printf("Pincode: %d, Channels: %s, Music: %s\n", fun[i].pincode, fun[i].channels, fun[i].music);
    }
}

// Function:        bm_search
// Description:     Boyer-Moore string search
// Input parameter: text, pattern
// Return type:     index or -1
int bm_search(char *txt, char *pat)
{
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[256];

    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < m; i++)
        badchar[(int)pat[i]] = i;

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
            return s;

        s += (j - badchar[(int)txt[s + j]]);
    }

    return -1;
}

// Function:    TV
// Description: allows passenger to choose play based on city pincode
// Input param: fun pointer
// Return Type: NULL
void TV(ENT *fun)
{
    int pin, i;
    char input[20];

    printf("\nChoose city pincode: ");
    scanf("%d", &pin);

    for (i = 0; i < 120; i++)
    {
        if (pin == fun[i].pincode)
        {
            printf("Choose 'channel' or 'music' to see or listen: ", fun[i].channels, fun[i].music);
            scanf("%s", input);

            int index = bm_search(input, "channel");
            if (index != -1)
            {
                printf("Enjoy %s.\n", fun[i].channels);
                return;
            }

            index = bm_search(input, "music");
            if (index != -1)
            {
                printf("Enjoy %s.\n", fun[i].music);
                return;
            }

            printf("Invalid option.\n");
            return;
        }
    }

    printf("City yet to be uploaded.\n");
}


int entertain_fac()
{
    ENT fun[120];

    load_from_file_entertain(fun, 120);

    merge_sort(fun, 0, 119);

    display_play(fun);

    TV(fun);

    return 0;
}

#endif // ENTERTAINMENT_H_INCLUDED
