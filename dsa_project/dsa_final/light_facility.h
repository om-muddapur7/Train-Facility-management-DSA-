#ifndef LIGHT_FACILITY_H_INCLUDED
#define LIGHT_FACILITY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct light
{
    int u;    // vertex
    int v;    // vertex
    int ilm;  // illumination
};

struct light LIGHTS[30];

// Number of lights to be placed
int lights;

// Function:        display_placement
// Description:     displays minimal spanning tree for light illumination
// Input parameter: path array
// Return type:     NULL
void display_placement(int path[20])
{
    int i, j;
    printf("\nLights Placement Path (Illumination basis):\n");

    for (i = 0; i < lights; i++)
    {
        printf("Light %d: ", i);

        for (j = 0; j < lights; j++)
        {
            if (path[j] == i)
            {
                printf("-> Light %d ", j);
            }
        }

        printf("\n");
    }
}

// Function:        read_lights
// Description:     reads the number of lights to be placed
// Input parameter: NULL
// Return type:     NULL
void read_lights()
{
    printf("Enter the number of lights: ");
    scanf("%d", &lights);
}

// Function:        prim
// Description:     computes minimal spanning tree for light illumination using Prim's Algorithm
// Input parameter: NULL
// Return type:     NULL
void prim()
{
    int src;

    printf("\nEnter the source light for Prim's Algorithm: ");
    scanf("%d", &src);

    int cost[5][5] = {
        {0, 3, 9999, 7, 9999},
        {3, 0, 4, 2, 9999},
        {9999, 4, 0, 8, 6},
        {7, 2, 8, 0, 4},
        {9999, 9999, 6, 4, 0}};

    int dist[20];
    int path[20];
    int visited[20] = {0};
    int i, j, u, k, l, m;

    for (i = 0; i < lights; i++)
    {
        dist[i] = cost[src][i];
        path[i] = src;
    }

    for (l = 0; l < lights - 1; l++)
    {
        u = 9999; // infinity
        for (j = 0; j < lights; j++)
        {
            if (visited[j] == 0 && (dist[j] < u))
                u = j;
        }
        visited[u] = 1;

        for (k = 0; k < lights; k++)
        {
            if (visited[k] == 0 && (cost[u][k] < dist[k]))
            {
                dist[k] = cost[u][k];
                path[k] = u;
            }
        }
    }

    display_placement(path);
}

// Function:        find
// Description:     checks for similarity
// Input parameter: array, vertices
// Return type:     NULL
int find(int arr[], int u, int v)
{
    if (arr[u] == arr[v])
        return 1;
    else
        return 0;
}

// Function:        union_
// Description:     performs union operation for the disjoint set data structure
// Input parameter: array, size, vertices u and v
// Return type:     NULL
void union_(int arr[], int n, int u, int v)
{
    int temp = arr[u];
    int i;
    for (i = 0; i < n; i++)
    {
        if (arr[i] == temp)
        {
            arr[i] = arr[v];
        }
    }
}

// Function:        kruskal
// Description:     computes minimal spanning tree for light illumination using Kruskal's Algorithm
// Input parameter: number of lights, number of edges
// Return type:     NULL
void kruskal(int lights, int edge)
{
    int count = 0;
    int edge_list[30];

    for (int i = 0; i < lights; i++)
    {
        edge_list[i] = i;
    }

    printf("\nKruskal's Algorithm for Lights Placement:\n");

    printf("Enter the number of edges: ");
    scanf("%d", &edge);

    for (int i = 0; i < edge; i++)
    {
        printf("Enter light (vert_1, vert_2, watt) for light %d: ", i + 1);
        scanf("%d %d %d", &LIGHTS[i].u, &LIGHTS[i].v, &LIGHTS[i].ilm);
    }

    printf("\nSelected LIGHTS for Lights Placement:\n");

    for (int k = 0; k < edge; k++)
    {
        if (find(edge_list, LIGHTS[k].u, LIGHTS[k].v))
        {
            printf("Discarded\n");
        }
        else
        {
            printf("Place light between vertex:%d to vertex:%d of Watt:%d\n", LIGHTS[k].u, LIGHTS[k].v, LIGHTS[k].ilm);
            union_(edge_list, lights, LIGHTS[k].u, LIGHTS[k].v);
            count += LIGHTS[k].ilm;
        }
    }

    printf("The total watts of light required for lights placement is %d\n", count);
}

int light_fac()
{
    int edge;
    read_lights();

    int choice;

    do
    {
        printf("\nChoose an algorithm for Lights Placement:\n");
        printf("1. For Usual Matrix\n");
        printf("2. For random Spots\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            prim();
            break;

        case 2:
            kruskal(lights, edge);
            break;

        case 3:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    return 0;
}

#endif // LIGHT_FACILITY_H_INCLUDED
