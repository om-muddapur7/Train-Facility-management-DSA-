#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10

int sparseTable[MAX_ROWS][MAX_COLS];

// Function:        display
// Description:     displays parking allotment
// Input parameter: park array with row and columns number
// Return type:     NULL
void display(int park[MAX_ROWS][MAX_COLS], int rows, int cols) 
{
    int i, j;
    for (i = 0; i < rows; i++) 
    {
        for (j = 0; j < cols; j++) 
        {
            printf("%d ", park[i][j]);
        }
        printf("\n");
    }
}

// Function:         sparse_table
// Description:      initializes the Sparse Table
// Input parameters: park array, rows, cols
// Return type:      NULL
void sparse_table(int park[MAX_ROWS][MAX_COLS], int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            sparseTable[i][j] = park[i][j];
        }
    }
}

// Function:         sum_cars
// Description:      adds row parked elements
// Input parameters: rows, cols
// Return type:      NULL
void sum_cars(int rows, int cols) 
{
    for (int j = 0; j < cols; j++) 
    {
        for (int i = 1; i < rows; i++) 
        {
            sparseTable[i][j] += sparseTable[i - 1][j];
        }
    }
}

// Function:         rmq
// Description:      performs range minimum query in the Sparse Table
// Input parameters: start and end row, column
// Return type:      int
int rmq(int start, int end, int col) 
{
    if (start == 0) 
    {
        return sparseTable[end][col];
    } 
    else 
    {
        return sparseTable[end][col] - sparseTable[start - 1][col];
    }
}

// Function:         check_park
// Description:      finds the row with the least number of cars parked
// Input parameters: rows, cols
// Return type:      int
int check_park(int rows, int cols) 
{
    int cars = MAX_ROWS + 1;
    int check_row = -1;

    for (int i = 0; i < rows; i++) 
    {
        // start row, end row, column
        int park = rmq(i, i, cols - 1); 
        if (park < cars) 
        {
            cars = park;
            check_row = i;
        }
    }
    return check_row;
}

// Function:         input
// Description:      marks 1 for vehicle parked row-wise
// Input parameters: park array, rows, cols
// Return type:      NULL
void input(int park[MAX_ROWS][MAX_COLS], int rows, int cols) 
{
    int i, j, vehi;

    printf("Enter no. of vehicles parked: ");
    scanf("%d", &vehi);

    for (i = 0; i < rows && vehi > 0; i++) 
    {
        for (j = 0; j < cols && vehi > 0; j++) 
        {
            park[i][j] = 1;
            vehi--;
        }
    }
}

int main() 
{
    int park[MAX_ROWS][MAX_COLS] = {0};
    int rows = 10;
    int cols = 10;

    printf("Initial stage:\n");
    display(park, rows, cols);

    input(park, rows, cols);

    printf("Parking:\n");
    display(park, rows, cols);

    printf("Sparse Table (Before Summing Rows):\n");
    display(sparseTable, rows, cols);

    sparse_table(park, rows, cols);

    sum_cars(rows, cols);

    printf("Sparse Table (After Summing Rows):\n");
    display(sparseTable, rows, cols);

    // Find the row with the least number of cars parked
    int check_row = check_park(rows, cols);

    if (check_row != -1) 
    {
        printf("\nYou can park your vehicle at row %d.\n", check_row + 1);
    } 
    else 
    {
        printf("\nParking is full. Please wait...\n");
    }

    return 0;
}