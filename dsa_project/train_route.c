// Train route decisions
#include <stdio.h>
#include <stdlib.h>

#define MAX_STATIONS 20
#define infinity 9999  // A large value to represent infinity

int stations, source;
int visited[10];
int m[20][20] = {{0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0}, 
                 {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
                 {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1},
                 {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
                 {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0}, 
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0},
                 {1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
                 {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1},
                 {0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1}};

// Function:        dfs
// Description:     performs dfs traversal
// Input parameter: station matrix, stations, source
// Return type:     NULL
void dfs(int m[20][20], int v, int source) 
{
    int i;
    visited[source] = 1;
    for (i = 0; i < v; i++) 
    {
        if (m[source][i] == 1 && visited[i] == 0) 
        {
            printf("Visit station:%d\n", i);
            dfs(m, v, i);
        }
    }
}

// Function:        bfs
// Description:     performs bfs traversal
// Input parameter: station matrix, stations, source
// Return type:     NULL
void bfs(int m[MAX_STATIONS][MAX_STATIONS], int v, int source) 
{
    int queue[MAX_STATIONS];
    int front = 0, rear = 0, u, i;

    int visited[MAX_STATIONS];
    for (i = 0; i < v; i++)
        visited[i] = 0;

    queue[rear] = source;
    visited[source] = 1;
    printf("The BFS Traversal is... \n");
    while (front <= rear) 
    {
        u = queue[front];
        printf("Visit station:%d\n", u);
        front = front + 1;

        for (i = 0; i < v; i++) 
        {
            if (m[u][i] == 1 && visited[i] == 0) 
            {
                visited[i] = 1;
                rear = rear + 1;
                queue[rear] = i;
            }
        }
    }
}

// Function:        warshall
// Description:     performs Warshall algorithm
// Input parameter: station matrix, stations
// Return type:     NULL
void warshall(int m[MAX_STATIONS][MAX_STATIONS], int v) 
{
    char station_names[MAX_STATIONS][MAX_STATIONS] = {"Station 1", "Station 2", "Station 3", "Station 4", "Station 5","Station 6","Station 7","Station 8","Station 9","Station 10"};
    int dist[MAX_STATIONS][MAX_STATIONS];
    int i, j, k;

    // Initialize the distance matrix
    for (i = 0; i < v; i++) 
    {
        for (j = 0; j < v; j++) 
        {
            dist[i][j] = m[i][j];
        }
    }

    // Apply the Warshall algorithm
    for (k = 0; k < v; k++) 
    {
        for (i = 0; i < v; i++) 
        {
            for (j = 0; j < v; j++) 
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest paths between stations
    printf("\nShortest Paths between Stations:\n");
    printf("If '0' -> direct route from source station to destination station\n");
    printf("If '1' or more -> indirect routes from source station to destination station\n\n");
    for (i = 0; i < v; i++) 
    {
        for (j = 0; j < v; j++) 
        {
            if (dist[i][j] == infinity)
                printf("No route from %s to %s\n", station_names[i], station_names[j]);
            else if (i != j)
                printf("Shortest route from %s to %s has distance %d\n", station_names[i], station_names[j], dist[i][j]);
        }
    }
}

int main() 
{
    int choice;

    printf("Enter the number of stations: ");
    scanf("%d", &stations);

    printf("Enter the source station: ");
    scanf("%d", &source);

    while (1) 
    {
        printf("\n1. Perform DFS Traversal\n");
        printf("2. Perform BFS Traversal\n");
        printf("3. Find Shortest Paths (Floyd-Warshall)\n");
        printf("4. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                for (int i = 0; i < stations; i++)
                    visited[i] = 0;

                printf("The DFS Traversal is... \n");
                printf("Visit station:%d\n", source);
                dfs(m, stations, source);
                break;

            case 2:
                bfs(m, stations, source);
                break;

            case 3:
                warshall(m, stations);
                break;

            case 4:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}