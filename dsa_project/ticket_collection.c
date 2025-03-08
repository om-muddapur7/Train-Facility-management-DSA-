#include <stdio.h>
#include <stdlib.h>

// Function:        update
// Description:     keeps updating sum up to the last column
// Input parameter: fenwick tree pointer, elements count, index, elements
// Return type:     NULL
void update(int *fen_tree, int n, int index, int value) 
{
    index++;
    while (index <= n) 
    {
        fen_tree[index] += value;
        index += index & -index;
    }
}

// Function:        prefix_sum
// Description:     calculates sum up to the given index
// Input parameter: pointer of fenwick tree, index
// Return type:     int
int prefix_sum(int *fen_tree, int index) 
{
    index++;
    int sum = 0;

    while (index > 0) 
    {
        sum += fen_tree[index];
        index -= index & -index;
    }

    return sum;
}

// Function:        fen_tree
// Description:     creates fenwick tree
// Input parameter: elements with their total count
// Return type:     int
int *fen_tree(int *input, int n) 
{
    int *fen_tree = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) 
    {
        fen_tree[i] = 0;
    }

    for (int i = 0; i < n; i++) 
    {
        update(fen_tree, n, i, input[i]);
    }
    
    return fen_tree;
}

// Function:        lookup_table
// Description:     creates lookup table for range minimum query
// Input parameter: input array, elements count
// Return type:     int*
int *lookup_table(int *input, int n) 
{
    int *lookup = (int *)malloc((n + 1) * (n + 1) * sizeof(int));

    for (int i = 0; i < n; i++) 
    {
        int min_val = input[i];
        lookup[i * (n + 1) + i] = min_val;

        for (int j = i + 1; j < n; j++) 
        {
            min_val = (input[j] < min_val) ? input[j] : min_val;
            lookup[i * (n + 1) + j] = min_val;
        }
    }

    return lookup;
}

// Function:        range_min_query
// Description:     returns minimum value in the given range
// Input parameter: lookup table pointer, start index, end index, elements count
// Return type:     int
int range_min_query(int *lookup, int start, int end, int n) 
{
    return lookup[start * (n + 1) + end];
}

// Function:        read
// Description:     takes elements as input 
// Input parameter: pointer of total elements and input
// Return type:     NULL
void read(int **input, int *n) 
{
    printf("Enter the number of passengers: ");
    scanf("%d", n);

    *input = (int *)malloc(*n * sizeof(int));

    printf("Enter their ticket fares:\n");
    for (int i = 0; i < *n; i++) 
    {
        scanf("%d", &(*input)[i]);
    }
}

// Function:        sum
// Description:     takes calculation index as input
// Input parameter: fenwick tree pointer
// Return type:     NULL
void sum(int *fen_tree) 
{
    int q_index;
    printf("Enter the index for ticket amount collection query: ");
    scanf("%d", &q_index);

    int sum = prefix_sum(fen_tree, q_index);
    printf("Amount collected up to index %d is: %d\n", q_index, sum);
}

// Function:        rmq
// Description:     performs Range Minimum Query (RMQ) and displays the sum
// Input parameter: lookup table pointer, elements count
// Return type:     NULL
void rmq(int *lookup, int n)
{
    int start, end;
    printf("Enter the start and end indices for range min query: ");
    scanf("%d %d", &start, &end);

    int min_val = range_min_query(lookup, start, end, n);
    printf("Minimum value in the range [%d, %d] is: %d\n", start, end, min_val);
}

int main() 
{
    int *input;
    int n, choice;

    read(&input, &n);
    int *fenwick_tree = fen_tree(input, n);
    int *lookup = lookup_table(input, n);

    do 
    {
        printf("\nMenu:\n");
        printf("1. Query Amount Collected\n");
        printf("2. Range Minimum Query\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                sum(fenwick_tree);
                break;

            case 2:
                rmq(lookup, n);
                break;

            case 3:
                printf("\nExiting...\n");
                break;

            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    free(input);
    free(fenwick_tree);
    free(lookup);

    return 0;
}