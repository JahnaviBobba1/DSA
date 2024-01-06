#include <stdio.h>
#include <stdlib.h>
#include "seat_reservation.h"
#include <string.h> // Include string.h for string operations
#define MAX 60

typedef struct tree
{
    struct flight_node *root; // Change 'node' to 'flight_node'
} TREE;



typedef struct flight_node
{
    char fl_name[50];
    char *src;
    char *dest;
    int duration;
    int fare;
    int st;
    int et;
    List seatList;
    struct flight_node *left; // Change 'node' to 'flight_node'
    struct flight_node *right; // Change 'node' to 'flight_node'
} NODE;






void initTree(TREE *pt);
void createTree(TREE *pt);
int inorder(NODE *r,char *src,char *dest); // Correct the function declaration
int inorder_call(TREE *pt,char *u_src,char *u_dest);





void initTree(TREE *pt)
{
    pt->root = NULL;
}

void storeSeatsToFile(List *seat, FILE *file) {
    Seat *current = seat->head;
    while (current != NULL) {
        // Store seat information line by line
        fprintf(file, "%s\n", current->st);
        current = current->next;
    }
}


void storeFlightNode(NODE *node, const char *filename) {
    // Open the file in append mode
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    // Write the flight_node information to the file as a new line
    fprintf(file, "%s %s %s %d %d %d %d %d ",
            node->fl_name, node->src, node->dest,
            node->duration, node->fare, node->st, node->et);
    //storeSeatsToFile(node->seatList.head, file);
    Seat *current = node->seatList.head;
    while (current != NULL) {
        fprintf(file, "%s ", current->st);
        current = current->next;
    }
    fprintf(file, "\n");
    // Close the file
    fclose(file);
}









void createTree(TREE *pt)
{
    int choice;

    NODE *temp = malloc(sizeof(NODE));
    temp->left = temp->right = NULL;
    printf("enter the flight name\n");
    scanf("%s", temp->fl_name);
    // For 'src' and 'dest', allocate memory and use strcpy
    temp->src = malloc(50);
    temp->dest = malloc(50);
    printf("enter the source\n");
    scanf("%s", temp->src);
    printf("enter the destination\n");
    scanf("%s", temp->dest);
    printf("enter the duration\n");
    scanf("%d", &temp->duration);
    printf("enter the flight fare\n");
    scanf("%d", &temp->fare);
    // For 'st' and 'et', use char arrays and scanf strings
    printf("enter the start time\n");
    scanf("%d", &temp->st);
    printf("enter the end time\n");
    scanf("%d", &temp->et);

    createSeat(&temp->seatList);

    printf("yess done!!!");
    pt->root = temp;

    printf("Do you want to add one more node\n");
    scanf("%d", &choice);

    while (choice)
    {
        temp = malloc(sizeof(NODE));
        temp->left = temp->right = NULL;
        printf("enter the flight name\n");
        scanf("%s", temp->fl_name);
        // For 'src' and 'dest', allocate memory and use strcpy
        temp->src = malloc(50);
        temp->dest = malloc(50);
        printf("enter the source\n");
        scanf("%s", temp->src);
        printf("enter the destination\n");
        scanf("%s", temp->dest);
        printf("enter the duration\n");
        scanf("%d", &temp->duration);
        printf("enter the flight fare\n");
        scanf("%d", &temp->fare);
        // For 'st' and 'et', use char arrays and scanf strings
        printf("enter the start time\n");
        scanf("%d", &temp->st);
        printf("enter the end time\n");
        scanf("%d", &temp->et);
        //NODE *treeArray = malloc(sizeof(NODE) * 100); //linked list 
        temp->seatList.head = NULL;
        createSeat(&temp->seatList);
        


        NODE *p = pt->root;
        NODE *q = NULL;
        while (p != NULL)
        {
            if (temp->fare <= p->fare)
            {
                q = p;
                p = p->left;
            }
            else
            {
                q = p;
                p = p->right;
            }
        }

        if (temp->fare <= q->fare)
            q->left = temp;
        else
            q->right = temp;

        
        printf("Do you want to add one more flight node\n");
        scanf("%d", &choice);
    }
}

int inorder(NODE *r, char *u_src, char *u_dest) {
    int count = 0;
    if (r != NULL) {
        count += inorder(r->left, u_src, u_dest);
        if (strcmp(r->src, u_src) == 0 && strcmp(r->dest, u_dest) == 0) {
            printf("Flight Name: %s, Source: %s, Destination: %s, Duration: %d, Fare: %d, Start Time: %d, End Time: %d\n",
                   r->fl_name, r->src, r->dest, r->duration, r->fare, r->st, r->et);
            count = 1;  // Set count to 1 when a match is found
        }
        count += inorder(r->right, u_src, u_dest);
    }
    return count;
}


int inorder_call(TREE *pt, char *u_src, char *u_dest) {
    
    
    int res=inorder(pt->root, u_src, u_dest);
     return res;
}


void markSeatInTree(NODE *root, const char *chosenSeat) {
    if (root != NULL) {
        markSeatInTree(root->left, chosenSeat);

        // Check if the current node's seat matches the chosen seat
        if (strcmp(root->seatList.head->st, chosenSeat) == 0) {
            // Mark the chosen seat with 'X' in the binary tree
            strcpy(root->seatList.head->st, "X");
        }

        markSeatInTree(root->right, chosenSeat);
    }
}


void updateFlightDataFile(NODE *root) {
    // Open the original file in read mode
    FILE *file = fopen("flight_data.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read each line and update the seat information if the flight matches
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract flight information
        char *token = strtok(line, " ");
        if (token != NULL) {
            // Compare flight name with the root node's flight name
            if (strcmp(token, root->fl_name) == 0) {
                // Update the seat information
                fseek(file, -strlen(line), SEEK_CUR); // Move back to the beginning of the line
                Seat *current = root->seatList.head;
                while (current != NULL) {
                    // Find the seat in the line and update it to 'X'
                    char *seatToken = strtok(NULL, " ");
                    if (strcmp(seatToken, current->st) == 0) {
                        // Update the seat to 'X'
                        fprintf(file, "X "); // Update the seat to 'X'
                    } else {
                        fprintf(file, "%s ", seatToken); // Keep other seat information unchanged
                    }
                    current = current->next;
                }
                fseek(file, 0, SEEK_CUR); // Move back to the end of the line
            }
        }
    }

    // Close the file
    fclose(file);
}
