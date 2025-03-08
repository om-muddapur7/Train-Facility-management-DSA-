//Information organization
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structure to contain all information related to railways
typedef struct TreeNode 
{
    int   date;
    int   tickID;
    int   platform_num;
    char  train_name[30];
    int   persons;
    float price;
    char  station[30];
    char  seat[5];
    char  class[20];
    char  from[20];
    char  to[20];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

//Function:     create_node
//Description:  creates nodes of information
//Input param:  TreeNode structure
//Return Type:  node
TreeNode* create_node(int date, int tickID, int platform_num, char train_name[30], int persons, float price, char station[30], char seat[5], char class[20], char from[20], char to[20]) 
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    newNode->date = date;
    newNode->tickID = tickID;
    newNode->platform_num = platform_num;
    newNode->persons = persons;
    newNode->price = price;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

//Function:     insert
//Description:  adds node of train's information to the tree according to Binary Search Tree
//Input param:  root pointer and TreeNode structure
//Return Type:  root
TreeNode* insert(TreeNode* root,int date, int tickID, int platform_num, char train_name[30], int persons, float price, char station[30], char seat[5], char class[20], char from[20], char to[20]) 
{
    if (root == NULL) 
    {
        return create_node(date, tickID, platform_num, train_name, persons, price, station, seat, class, from, to);
    }

    if (tickID < root->tickID) 
    {
        root->left = insert(root->left, date, tickID, platform_num, train_name, persons, price, station, seat, class, from, to);
    } 
    else if (tickID > root->tickID) 
    {
        root->right = insert(root->right, date, tickID, platform_num, train_name, persons, price, station, seat, class, from, to);
    }

    return root;
}

//Function:     search
//Description:  shows information necessary to passenger with tick-id(101,102,etc ->prototype )
//Input param:  root pointer
//Return Type:  NULL
void search(TreeNode* root,int tick) 
{
    printf("\nSearching for a node by tick-ID:\n");
    printf("Enter tick-ID: ");
    scanf("%d", &tick);

    if (root != NULL) 
    {
        if (tick == root->tickID)
        {
            printf("Date: %d, Train Name: %s, Platform Number: %d\n", root->date, root->train_name, root->platform_num);
            return; 
        }

        search(root->left,tick);
        search(root->right,tick);
    }
}

// Function:    inputs
// Description: train's unorganized information
// Input param: root pointer
// Return Type: root
TreeNode* inputs(TreeNode* root)
{
    int i, in;
    printf("Enter no. of trains: ");
    scanf("%d", &in);

    for (i = 0; i < in; i++)
    {
        int date, tickID, platform_num, persons;
        float price;
        char train_name[30], station[30], seat[5], class[20], from[20], to[20];

        printf("\nEnter new train information for Train %d:\n", i + 1);
        printf("Date: ");
        scanf("%d", &date);
        printf("Tick ID: ");
        scanf("%d", &tickID);
        printf("Platform No.: ");
        scanf("%d", &platform_num);
        printf("Train Name: ");
        scanf(" %29[^\n]", train_name);
        printf("No. of persons: ");
        scanf("%d", &persons);
        printf("Price: ");
        scanf("%f", &price);
        printf("Station: ");
        scanf("%s", station);
        printf("Seat: ");
        scanf("%s", seat);
        printf("Class: ");
        scanf("%s", class);
        printf("From: ");
        scanf("%s", from);
        printf("To: ");
        scanf("%s", to);

        root = insert(root, date, tickID, platform_num, train_name, persons, price, station, seat, class, from, to);
    }

    return root;
}

// Function:    find_min
// Description: finds minimum among 2 children
// Input param: root pointer
// Return Type: root
TreeNode* find_min(TreeNode* node) 
{
    while (node->left != NULL) 
    {
        node = node->left;
    }
    return node;
}

// Function:    delete
// Description: deletes train from tree
// Input param: root pointer and tick-ID
// Return Type: root
TreeNode* delete(TreeNode* root, int tick) 
{
    printf("\nEnter tick-ID to delete: ");
    scanf("%d", &tick);
    if (root == NULL) 
    {
        return root;
    }

    if (tick < root->tickID) 
    {
        root->left = delete(root->left, tick);
    } 
    else if (tick > root->tickID) 
    {
        root->right = delete(root->right, tick);
    } 
    else 
    {
        if (root->left == NULL) 
        {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) 
        {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = find_min(root->right);

        // Copy the in-order successor's content to this node
        root->date = temp->date;
        root->tickID = temp->tickID;
        root->platform_num = temp->platform_num;
        root->persons = temp->persons;
        root->price = temp->price;
        strcpy(root->train_name, temp->train_name);
        strcpy(root->station, temp->station);
        strcpy(root->seat, temp->seat);
        strcpy(root->class, temp->class);
        strcpy(root->from, temp->from);
        strcpy(root->to, temp->to);

        root->right = delete(root->right, temp->tickID);
    }

    return root;
}

// Function:    inorder
// Description: performs inorder traversal
// Input param: root pointer
// Return Type: NULL
void inorder(TreeNode* root) 
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("Date: %d, Train Name: %s, Platform Number: %d\n", root->date, root->train_name, root->platform_num);
        inorder(root->right);
    }
}

int main()
{
    TreeNode* root = NULL;
    int tick, tick_del;
    int opt;

    do
    {
        printf("\nMenu:\n");
        printf("1. Input train information\n");
        printf("2. Delete train (if any are canceled)\n");
        printf("3. Search for a train by tick-ID\n");
        printf("4. Display in-order traversal\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &opt);

        switch (opt)
        {
        case '1':
            root = inputs(root);
            break;

        case '2':
            printf("Are any trains cancelled? (y/n): ");
            scanf(" %c", &opt);
            if (opt == 'y')
            {
                printf("Enter tick-ID to delete: ");
                scanf("%d", &tick_del);
                root = delete(root, tick_del);
                printf("\nIn-order traversal after deletion:\n");
                inorder(root);
            }
            break;

        case '3':
            search(root,tick);
            break;

        case '4':
            printf("\nIn-order traversal:\n");
            inorder(root);
            break;

        case '5':
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    } while (opt != '5');
}                                              