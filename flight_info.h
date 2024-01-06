#ifndef FLIGHT_INFO_H
#define FLIGHT_INFO_H

#include "seat_reservation.h"

typedef struct flight_node {
    char fl_name[50];
    char *src;
    char *dest;
    int duration;
    int fare;
    int st;
    int et;
    List seatList;
    struct flight_node *left;
    struct flight_node *right;
}NODE;

typedef struct tree {
    struct flight_node *root;
} TREE;

void initTree(TREE *pt);
void createTree(TREE *pt);
int inorder(NODE *r, char *src, char *dest);
int inorder_call(TREE *pt, char *u_src, char *u_dest);
void storeFlightNode(NODE *node, const char *filename);
void markSeatInTree(NODE *root, const char *chosenSeat);
void updateFlightDataFile(NODE *root);


#endif // FLIGHT_INFO_H
