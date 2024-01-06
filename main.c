// File: main.c
#include "seat_reservation.h"
#include "flight_info.h"
#include "passenger_info.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

//void writePassengerToFile(FLIGHT_NAME flight);

void updateFlightDataFile(NODE *root);



void handleSeatSelection(NODE *r) {
    char chosenSeat[4];

    printf("\nEnter the seat you want to choose (e.g., A1): ");
    scanf("%s", chosenSeat);
    PASSENGER_INFO passenger;
    strcpy(passenger.seat_no,chosenSeat);

    

    if(strcmp(chosenSeat, "exit") == 0) {
        printf("You have chosen seat %s.\n", chosenSeat);
        printf("Updated seat arrangement:\n");
        printSeats(&r->seatList, 30, 30);
    } 
}



int searchNode(NODE *r, char *user_fl_name) {
    if (r != NULL) {
        if (strcmp(user_fl_name, r->fl_name) == 0) {
            printf("Initial seat arrangement:\n");
            printSeats(&r->seatList,30,30);
            handleSeatSelection(r);

            return 1;
        } else if (strcmp(user_fl_name, r->fl_name) < 0) {
            return searchNode(r->left, user_fl_name);
        } else {
            return searchNode(r->right, user_fl_name);
        }
    }
    return 0;
}




int searchRecursive(TREE *pt,char *user_fl_name)
{
	return searchNode(pt->root,user_fl_name);
}

void printTreeElements(NODE *root) {
    if (root != NULL) {
        printTreeElements(root->left);

        // Print information for the current node
        printf("Flight Name: %s\n", root->fl_name);
        // Print other relevant information

        printTreeElements(root->right);
    }
}

void insertNode(NODE **root, const char flight_no[], const char src[], const char dest[], int duration, int fare, int st, int et)
{
    if (*root == NULL)
    {
        // Create a new node and assign values
        *root = (NODE *)malloc(sizeof(NODE));
        strcpy((*root)->fl_name, flight_no);
        (*root)->src = strdup(src); // Use strdup to allocate memory for strings
        (*root)->dest = strdup(dest);
        (*root)->duration = duration;
        (*root)->fare = fare;
        (*root)->st = st;
        (*root)->et = et;
         // Initialize the seatList
        createSeat(&(*root)->seatList);

        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else
    {
        // Recursively insert based on flight number or any other criteria
        if (strcmp(flight_no, (*root)->fl_name) < 0)
        {
            insertNode(&(*root)->left, flight_no, src, dest, duration, fare, st, et);
        }
        else
        {
            insertNode(&(*root)->right, flight_no, src, dest, duration, fare, st, et);
        }
    }
}

void parseAndInsertFromFile(const char *filename, TREE *root)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }


    char line[256];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        char flight_no[20], src[20], dest[20];
        int duration, fare, st, et;

        // Assuming the format is: flight_no src dest duration fare st et
        sscanf(line, "%s %s %s %d %d %d %d", flight_no, src, dest, &duration, &fare, &st, &et);

        // Insert the parsed data into the tree
        insertNode(&root->root, flight_no, src, dest, duration, fare, st, et);
    }

    fclose(file);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to update the file content
void updateFile(const char *filename, const char *search, const char *replace) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the existing content
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    fread(content, 1, file_size, file);
    content[file_size] = '\0'; // Null-terminate the content

    fclose(file);

    // Search for the string to replace
    char *position = strstr(content, search);
    if (position != NULL) {
        // Replace the string
        strncpy(position, replace, strlen(replace));
    } else {
        printf("String not found in the file.\n");
        free(content);
        return;
    }

    // Write the updated content back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        free(content);
        exit(EXIT_FAILURE);
    }

    fwrite(content, 1, file_size, file);

    fclose(file);
    free(content);
}


void printTicketHeader() {
    printf("\n\t\t******************************\n");
    printf("\t\t*         TICKET             *\n");
    printf("\t\t******************************\n");
}

void printTicketFooter() {
    printf("\t\t******************************\n\n");
}

void printTicketInfo(const char *label, const char *value) {
    printf("\t\t* %-15s: %-9s *\n", label, value);
}



int main() {
    char u_src[50];
    char u_dest[50];
    int choice;

    printf("\n\t\t****************************\n");
    printf("\n\t\tAdmin please enter 1\n");
    printf("\n\t\tCustomer please enter 0\n");
    scanf("%d", &choice);
    printf("\n\t\t****************************\n");

    while (choice == 1) {
         NODE *temp = malloc(sizeof(NODE));
        temp->left = temp->right = NULL;
        printf("\n\t\tenter the flight name\n");
        scanf("%s", temp->fl_name);
        // For 'src' and 'dest', allocate memory and use strcpy
        temp->src = malloc(50);
        temp->dest = malloc(50);
        printf("\n\t\tenter the source\n");
        scanf("%s", temp->src);
        printf("\n\t\tenter the destination\n");
        scanf("%s", temp->dest);
        printf("\n\t\tenter the duration\n");
        scanf("%d", &temp->duration);
        printf("\n\t\tenter the flight fare\n");
        scanf("%d", &temp->fare);
        // For 'st' and 'et', use char arrays and scanf strings
        printf("\n\t\tenter the start time\n");
        scanf("%d", &temp->st);
        printf("\n\t\tenter the end time\n");
        scanf("%d", &temp->et);
        printf("\n\t\t****************************\n");
        //NODE *treeArray = malloc(sizeof(NODE) * 100); //linked list 
        temp->seatList.head = NULL;
        createSeat(&temp->seatList);
        storeFlightNode(temp, "flight_data.txt");
        printf("\n\t\tDo you want to enter another flight?\n");
        scanf("%d",&choice);

    }

    printf("\n\t\tFor booking flight enter 1\n");
    printf("\n\t\t Press any key to exit\n");
    int n;
    scanf("%d", &n);

    if (n == 1) {
        TREE tobj;
        initTree(&tobj);
        parseAndInsertFromFile("flight_data.txt", &tobj);

        int opt = 1;

        do {
            printf("\n\t\t****************************\n");
            printf("\n\t\tEnter source\n");
            scanf("%s", u_src);
            printf("\n\t\tEnter destination\n");
            scanf("%s", u_dest);
            printf("\n\n\t\tHere are your available flights:\n");

            int res = inorder_call(&tobj, u_src, u_dest);

            if (res == 0) {
                printf("Sorry! No available flights for your route\n");
                printf("Do you want to enter another flight? (0/1): ");
                scanf("%d", &opt);
            } else {
                printf("\n\t\tPlease type in the flight you want to go in!\n");
                char user_fl_name[50];
                scanf("%s", user_fl_name);

                res = searchRecursive(&tobj, user_fl_name);

                if (res == 0) {
                    printf("\n\t\tFlight not found. Please try again.\n");
                    opt = 1; // Allow the user to enter another flight
                } else {
                    FLIGHT_NAME flight;
                    PASSENGER_INFO passenger = book_flight();
                    strcpy(flight.fl_name, user_fl_name);
                    flight.passenger_list = insertPassenger(flight.passenger_list, passenger);

                    // Write passenger information to file
                    writePassengerToFile(flight);
                    //printf("Seat chosen: %s\n", passenger.seat_no);

                    printTicketHeader();    
                    printTicketInfo("NAME", passenger.name);
                    //printTicketInfo("SEAT", passenger.seat_no);
                    printTicketInfo("FLIGHT", user_fl_name);
                    printTicketInfo("SOURCE", u_src);
                    printTicketInfo("DESTINATION", u_dest);
                    printTicketFooter();

                    opt = 0; // Exit the loop after successful booking
                }
            }
        } while (opt == 1);
    }

    return 0;
}
