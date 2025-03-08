#include <stdio.h>

// Function to update the Fenwick Tree
void update(int *fenwickTree, int n, int index, int value) {
    index++; // Fenwick Tree is 1-based index
    while (index <= n) {
        fenwickTree[index] += value;
        index += index & -index; // Move to the next higher position that is not covered by the current update
    }
}

// Function to get the prefix sum up to a given index
int getPrefixSum(int *fenwickTree, int index) {
    index++; // Fenwick Tree is 1-based index
    int sum = 0;
    while (index > 0) {
        sum += fenwickTree[index];
        index -= index & -index; // Move to the parent position
    }
    return sum;
}

// Function to construct the Fenwick Tree from an input array
int *constructFenwickTree(int *input, int n) {
    int *fenwickTree = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        fenwickTree[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        update(fenwickTree, n, i, input[i]);
    }
    return fenwickTree;
}

int main() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int *input = (int *)malloc(n * sizeof(int));

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &input[i]);
    }

    int *fenwickTree = constructFenwickTree(input, n);

    int queryIndex;
    printf("Enter the index for prefix sum query: ");
    scanf("%d", &queryIndex);

    int prefixSum = getPrefixSum(fenwickTree, queryIndex);
    printf("Prefix Sum up to index %d is: %d\n", queryIndex, prefixSum);

    free(input);
    free(fenwickTree);

    return 0;
}
