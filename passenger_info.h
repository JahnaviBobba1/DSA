// File: passenger_info.h
#ifndef PASSENGER_INFO_H
#define PASSENGER_INFO_H

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

NOD *insertPassenger(NOD *head, PASSENGER_INFO passenger_data);
PASSENGER_INFO book_flight();
void writePassengerToFile(FLIGHT_NAME flight);



#endif // PASSENGER_INFO_H