// File: seat_reservation.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight_info.h"

#define MAX 60



//linked list of seat numbers


void printSeats(List *pl,int seatsPerRow, int m);

void createSeat(List *pl) {
    
    for (char row = 'A'; row <= 'F'; row++) {
        for (int seatNum = 30; seatNum >= 1; seatNum--) {
            Seat *temp = malloc(sizeof(Seat));
            temp->next = NULL;

            // Use sprintf to create a string combining a letter and a number
            sprintf(temp->st, "%c%d", row, seatNum);

            // Assign a unique seat number
            temp->no = (row - 'A') * 30 + seatNum;

            // Add the new Seat to the linked list
            temp->next = pl->head;
            pl->head = temp;
        }
    }
}

int isSeatTaken(List *pl, const char *chosenSeat) {
    Seat *current = pl->head;
    while (current != NULL) {
        if (strcmp(current->st, chosenSeat) == 0) {
            // Check if the seat is already taken
            if (strcmp(current->st, "X") == 0) {
                return 1; // Seat is taken
            }
            return 0; // Seat is available
        }
        current = current->next;
    }
    return 1; // Invalid seat
}



void printSeats(List* pl, int seatsPerRow, int m) {
    Seat* current = pl->head;

    while (current != NULL) {
        printf("%s ", current->st);

        // Move to the next row
        if (current->no % seatsPerRow == 0) {
            printf("\n");

            // Insert an extra line break after every m seats
            if (current->no % m == 0) {
                // Insert an extra empty line between C and D
                if (current->st[0] == 'D') {
                    printf("\n");
                }
            }
        }

        current = current->next;
    }
}
