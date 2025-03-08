#ifndef COMM_BETN_STATIONS_H_INCLUDED
#define COMM_BETN_STATIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing train details
typedef struct train
{
    char   name[20];
    char   origin[20];
    char   destination[20];
    float  arrival;
    float  departure;
    struct train* prev;
    struct train* next;
} TrainNode;

// Function:    create_train_node
// Description: creates nodes of stations where trains travel
// Input param: NULL
// Return Type: node
TrainNode* create_train_node()
{
    TrainNode* temp = (TrainNode*)malloc(sizeof(TrainNode));
    if (temp == NULL)
    {
        printf("Insufficient memory\n");
        return NULL;
    }
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

// Function:    read
// Description: input train data
// Input param: train node
// Return Type: NULL
void read(TrainNode* t)
{
    printf("Enter train name, origin, destination, arrival, and departure times:\n");
    scanf("%s%s%s%f%f", t->name, t->origin, t->destination, &t->arrival, &t->departure);
}

// Function:    insert_end
// Description: adds node of train's information to the list
// Input param: head and temp pointer
// Return Type: head
TrainNode* insert_end(TrainNode* head, TrainNode* temp)
{
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        TrainNode* cur = head;
        while (cur->next != NULL)
            cur = cur->next;

        cur->next = temp;
        temp->prev = cur;
    }

    return head;
}

// Function:    display_train
// Description: displays the list
// Input param: head pointer
// Return Type: NULL
void display_train(TrainNode* head,TrainNode* train_array[],int n)
{
    int i;
    if (head == NULL)
    {
        printf("No trains available.\n");
    }
    else
    {
        printf("\nTrains details list");
        printf("\nTrain_name\t\t\tOrigin\t\tDestination\tArrival\tDeparture\n");
        for (i = 0; i < n; i++)
        {
            printf("%s\t\t\t\t%s\t\t%s\t\t%.2f\t%.2f\n", train_array[i]->name, train_array[i]->origin, train_array[i]->destination, train_array[i]->arrival, train_array[i]->departure);
        }
    }
}

// Function:    delete_front
// Description: deletes the train(1st train) info if it is cancelled
// Input param: head pointer
// Return Type: head
TrainNode* delete_front(TrainNode* head)
{
    if (head == NULL)
    {
        printf("No trains available.\n");
        return head;
    }
    else if (head->next == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        TrainNode* temp = head;
        head = head->next;
        head->prev = NULL;
        free(temp);
    }
    return head;
}

// Function:    delete_end
// Description: deletes the next train info if it is cancelled
// Input param: head pointer
// Return Type: head
TrainNode* delete_end(TrainNode* head)
{
    if (head == NULL)
    {
        printf("No trains available.\n");
        return head;
    }
    else if (head->next == NULL)
    {
        free(head);
        head = NULL;
    }
    else
    {
        TrainNode* cur = head;
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        TrainNode* prev = cur->prev;
        if (prev != NULL)
        {
            prev->next = NULL;
            free(cur);
        }
    }
    return head;
}

// Function:    Partition
// Description: Partitions the array of trains based on train names for Quick_sort
// Input param: array of trains, array range (start and end)
// Return Type: Index of the pivot element after partitioning
int Partition(TrainNode* arr[], int l, int r)
{
    // Choose the last element as the pivot
    char pivot[20];
    strcpy(pivot, arr[r]->name);

    // Initialize the index of the smaller element
    int i = l - 1;

    // Iterate through the array
    for (int j = l; j <= r - 1; j++)
    {
        // If the current element is smaller than or equal to the pivot
        if (strcmp(arr[j]->name, pivot) <= 0)
        {
            // Swap arr[i] and arr[j]
            i++;
            TrainNode* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap arr[i + 1] and arr[r] (move the pivot element to its correct position)
    TrainNode* temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;

    // Return the index of the pivot element after partitioning
    return i + 1;
}

// Function:    Quick_sort
// Description: sorts based on trains name
// Input param: array of trains, array range(start and end)
// Return Type: NULL
void Quick_sort(TrainNode* arr[], int l, int r)
{
    if (l < r)
    {
        int pi = Partition(arr, l, r);
        Quick_sort(arr, l, pi - 1);
        Quick_sort(arr, pi + 1, r);
    }
}

// Function:    match
// Description: search for a pattern in text(Rabin-karp method)
// Input param: pattern, text, and hash parameter
// Return Type: NULL
int match(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
    int d = 256;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and the first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
        // Check the hash values of the current window of text
        // and pattern. If the hash values match, then only
        // check for characters one by one
        if (p == t)
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i + j] != pat[j])
                    break;
            }

            // If p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]
            if (j == M)
                return 1;  // Pattern found
        }

        // Calculate hash value for the next window of text:
        // Remove the leading digit, add the trailing digit
        if (i < N - M)
        {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // We might get a negative value of t, converting
            // it to a positive value
            if (t < 0)
                t = (t + q);
        }
    }

    return 0;  // Pattern not found
}

// Function:    search_train
// Description: searches train with name
// Input param: head pointer
// Return Type: NULL
void search_train(TrainNode* head)
{
    if (head == NULL)
    {
        printf("No trains available.\n");
        return;
    }

    char train_name[20];
    int q = 101;
    printf("Passenger:\nEnter train name you are boarding: ");
    scanf("%s", train_name);

    TrainNode* cur = head;
    while (cur != NULL)
    {
        if (match(train_name, cur->name, q))
        {
            printf("\nTrain\t\t\tOrigin\t\tDestination\tArrival\tDeparture\n");
            printf("%s\t\t\t%s\t\t%s\t\t%.2f\t%.2f\n", cur->name, cur->origin, cur->destination, cur->arrival, cur->departure);
            return;
        }
        cur = cur->next;
    }

    // Train not found
    printf("Train '%s' not found.\n", train_name);
}

int comm_station()
{
    TrainNode* head = NULL;
    int i, n, ch;

    printf("Train Master:\nHow many trains are scheduled today: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        TrainNode* temp = create_train_node();
        read(temp);
        head = insert_end(head, temp);
    }

    // Sort trains by name
    TrainNode* train_array[n];
    TrainNode* cur = head;
    for (i = 0; i < n; i++)
    {
        train_array[i] = cur;
        cur = cur->next;
    }

    Quick_sort(train_array, 0, n - 1);

    do
    {
        printf("\nMenu:\n");
        printf("1. Display Trains\n");
        printf("2. Search Train\n");
        printf("3. Cancel Train\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
            case '1':
                // Display sorted trains
                display_train(head, train_array, n);
                break;

            case '2':
                // Search for a train
                search_train(head);
                break;

            case '3':
                // Cancel a train
                printf("Enter the position of the train to be cancelled: ");
                int position;
                scanf("%d", &position);

                if (position == 1)
                    head = delete_front(head);
                else if (position == n)
                    head = delete_end(head);
                else
                    printf("Train can't be cancelled, find a new locopilot.\n");

                 // Display remaining trains
                printf("\nRemaining Trains details list");
                printf("\nTrain_name\t\t\tOrigin\t\tDestination\tArrival\tDeparture\n");
                cur = head;
                while (cur != NULL)
                {
                    printf("%s\t\t\t\t%s\t\t%s\t\t%.2f\t%.2f\n", cur->name, cur->origin, cur->destination, cur->arrival, cur->departure);
                    cur = cur->next;
                }
                break;

            case '4':
                // Exit the program
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (ch != '4');

    return 0;
}

#endif // COMM_BETN_STATIONS_H_INCLUDED
