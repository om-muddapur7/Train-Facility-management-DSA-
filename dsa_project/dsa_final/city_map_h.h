#ifndef CITY_MAP_H_H_INCLUDED
#define CITY_MAP_H_H_INCLUDED

//City Maps
#include <stdio.h>
#include <stdlib.h>

struct citycode
{
    char city[30];
    int  code;
};

typedef struct citycode CC;
CC city_list[20];

int city_count = 0;
int places;

//Function:        load_from_file
//Description:     reads file
//Input parameter: NULL
//Return type:     NULL
void load_from_file()
{
    FILE *fp;

    // Open the file in read mode
    fp = fopen("city_code.txt", "r");

    // Check if the file was successfully opened
    if (fp == NULL)
    {
        printf("File Not found\n");
        return;
    }

    printf("***City Codes***\n");
    printf("Code\tCity\n");

    // Until the end of the file, read all the file data
    while(!feof(fp))
    {
        fscanf(fp,"%s %d", city_list[city_count].city, &city_list[city_count].code);
        printf("%d\t%s\n",city_list[city_count].code,city_list[city_count].city);
        city_count++;
    }
    fclose(fp);
}

//Function:        read_city
//Description:     reads no. of places to be visited from source
//Input parameter: NULL
//Return type:     NULL
void read_city()
{
    printf("\nEnter no. of places to be visited from city index 1: ");
    scanf("%d", &places);
}

//Function:        heapify
//Description:     sorts places based upon codes
//Input parameter: city code array,size of heap, current element index
//Return type:     NULL
void heapify(CC arr[], int n, int i)
{
    // This function is used to maintain the max heap property.
    int largest = i; // Assume the current index is the largest
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // Check if the left child is larger than the current largest
    if (left < n && arr[left].code > arr[largest].code)
        largest = left;

    // Check if the right child is larger than the current largest
    if (right < n && arr[right].code > arr[largest].code)
        largest = right;

    // If the largest element is not the current element at index i,
    // swap them and recursively heapify the affected subtree.
    if (largest != i)
    {
        CC temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

//Function:        heap_sort
//Description:     calls heapify for sorting elements
//Input parameter: city code array,city count
//Return type:     NULL
void heap_sort(CC arr[], int n)
{
    int i;
    // Build a max heap by repeatedly calling heapify
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements one by one from the heap
    for (i = n - 1; i > 0; i--)
    {
        // Swap the root (maximum element) with the last element
        CC temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

//Function:        display_city
//Description:     displays array
//Input parameter: city code array,city count
//Return type:     NULL
void display_city(CC arr[], int n)
{
    int i;
    printf("\n***City Codes after Heap Sort***\n");
    printf("Code\tCity\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%s\n", city_list[i].code, city_list[i].city);
    }
}


//Function:         Dijkstra
//Description:      computes shortest path from source
//Input parameter:  source
//Return type:      NULL
void Dijkstra(int src)
{
    //Cost matrix shows the distance between places
    //9999->infinity(NO direct road)
    int cost[5][5] = {
        {0,       3, 9999, 7, 9999},
        {3,       0,    4, 2, 9999},
        {9999,    4,    0, 8,    6},
        {7,       2,    8, 0,    4},
        {9999, 9999,    6, 4,    0}};

    int dist[20];
    int path[20];
    int visited[20] = {0};
    int i, j, u, k, l, m;

    for (i = 0; i < places; i++)
    {
        dist[i] = cost[src][i];
        path[i] = src;
    }

    for (l = 0; l < places - 1; l++)
    {
        u = 9999;  // Infinity
        for (j = 0; j < places; j++)
        {
            if (visited[j] == 0 && (dist[j] < u))
                u = j;
        }
        visited[u] = 1;

        for (k = 0; k < places; k++)
        {
            if (visited[k] == 0 && (dist[u] + cost[u][k] < dist[k]))
            {
                dist[k] = dist[u] + cost[u][k];
                path[k] = u;
            }
        }
    }

    // Print the shortest paths
    for (m = 0; m < places; m++)
    {
        printf("Distance to %d: %d, Path: ", m, dist[m]);
        int way = m;
        while (way != src)
        {
            printf("%d <- ", way);
            way = path[way];
        }
        printf("%d\n", src);
    }
}

int city_map()
{
    load_from_file();

    heap_sort(city_list, city_count);
    display_city(city_list,city_count);

    read_city();

    // Call Dijkstra's algorithm with source=0 (Railway station)
    int src=0;
    Dijkstra(src);

    return 0;
}

#endif // CITY_MAP_H_H_INCLUDED
