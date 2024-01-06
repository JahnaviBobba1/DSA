#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passenger_address {
    char street[100];
    char city[50];
    char state[50];
    char postalCode[20];
    char country[50];
} PASSENG_ADDR;

typedef struct CreditCard {
    char cardNumber[17];
    char cardHolderName[100];
    char expirationDate[6];
    char securityCode[4];
} CREDIT_CARD;

typedef struct passenger_info {
    char name[50];
    char gender[30];
    char seat_no[50];
    char email_id[50];
    char nationality[50];
    int ph_no;
    int emergency_cont;
    char food[50];
    PASSENG_ADDR p_a;
    CREDIT_CARD c_a;
} PASSENGER_INFO;

typedef struct flight_name {
    char fl_name[50];
    struct NOD *passenger_list;
} FLIGHT_NAME;

typedef struct NOD {
    PASSENGER_INFO passenger_data;
    struct NOD *next;
} NOD;

NOD *insertPassenger(NOD *head, PASSENGER_INFO passenger_data) {
    NOD *newNode = (NOD *)malloc(sizeof(NOD));
    if (newNode == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    newNode->passenger_data = passenger_data;
    newNode->next = head;

    return newNode;
}

PASSENGER_INFO book_flight() {
    PASSENGER_INFO passenger;
    int n;

    printf("\n\t\t****************************\n");

    printf("\n\t\tDo you want food enter 1 for food else 0: ");
    scanf("%d",&n);
    if(n==1)
    {
        printf("\n\t\tPlease enter Veg for Vegeterian and Non-Veg for Non-Vegeterian: ");
        scanf("%s",passenger.food);
    }
    else
    {
        strcpy(passenger.food, "-");
    }
    
    printf("\n\t\tEnter name: ");
    scanf("%s", passenger.name);

    printf("\n\t\tEnter your gender: ");
    scanf("%s", passenger.gender);

    printf("\n\t\tEnter your email ID: ");
    scanf("%s", passenger.email_id);

    printf("\n\t\tEnter your nationality: ");
    scanf("%s", passenger.nationality);

    printf("\n\t\tEnter your phone number: ");
    scanf("%d", &passenger.ph_no);

    printf("\n\t\tEnter your emergency contact: ");
    scanf("%d", &passenger.emergency_cont);

    printf("\n\t\tEnter your street address: ");
    scanf("%s", passenger.p_a.street);

    printf("\n\t\tEnter your city: ");
    scanf("%s", passenger.p_a.city);

    printf("\n\t\tEnter your state or region: ");
    scanf("%s", passenger.p_a.state);

    printf("\n\t\tEnter your postal code: ");
    scanf(" %[^\n]", passenger.p_a.postalCode);

    printf("\n\t\tEnter your country: ");
    scanf(" %[^\n]", passenger.p_a.country);

    printf("\n\t\tEnter your card number: ");
    scanf("%s", passenger.c_a.cardNumber);

    printf("\n\t\tEnter your card holder name: ");
    scanf("%s", passenger.c_a.cardHolderName);

    printf("\n\t\tEnter your card expiration date (MM/YY): ");
    scanf("%s", passenger.c_a.expirationDate);

    printf("\n\t\tEnter your security code: ");
    scanf("%s", passenger.c_a.securityCode);

      printf("\n\t\t****************************\n");


    return passenger;
}


void writePassengerToFile(PASSENGER_INFO passenger) {
    FILE *file = fopen("passenger_info.txt", "a");  // Open the file in append mode
    if (file == NULL) {
        perror("Error opening file");
        //exit(EXIT_FAILURE);
    }

    // Print passenger information to file
    if (fprintf(file, "Food: %s\n", passenger.food) < 0 ||
        fprintf(file, "Name: %s\n", passenger.name) < 0 ||
        fprintf(file, "Gender: %s\n", passenger.gender) < 0 ||
        fprintf(file, "Email ID: %s\n", passenger.email_id) < 0 ||
        fprintf(file, "Nationality: %s\n", passenger.nationality) < 0 ||
        fprintf(file, "Phone Number: %d\n", passenger.ph_no) < 0 ||
        fprintf(file, "Emergency Contact: %d\n", passenger.emergency_cont) < 0 ||
        fprintf(file, "Street Address: %s\n", passenger.p_a.street) < 0 ||
        fprintf(file, "City: %s\n", passenger.p_a.city) < 0 ||
        fprintf(file, "State/Region: %s\n", passenger.p_a.state) < 0 ||
        fprintf(file, "Postal Code: %s\n", passenger.p_a.postalCode) < 0 ||
        fprintf(file, "Country: %s\n", passenger.p_a.country) < 0 ||
        fprintf(file, "Card Number: %s\n", passenger.c_a.cardNumber) < 0 ||
        fprintf(file, "Card Holder Name: %s\n", passenger.c_a.cardHolderName) < 0 ||
        fprintf(file, "Expiration Date: %s\n", passenger.c_a.expirationDate) < 0 ||
        fprintf(file, "Security Code: %s\n", passenger.c_a.securityCode) < 0) {
        perror("Error writing to file");
    } else {
        fprintf(file, "\n");  // Add a newline to separate entries
        printf("Flight booked! \n");
    }

    fclose(file);
}