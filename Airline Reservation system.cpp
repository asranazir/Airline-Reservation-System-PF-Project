#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 5
#define MAX_ROWS 5
#define MAX_COLS 4
#define MAX_RESERVATIONS 100

int flightID[MAX_FLIGHTS];
char source[MAX_FLIGHTS][30];
char destination[MAX_FLIGHTS][30];
char departure[MAX_FLIGHTS][20];
float economyPrice[MAX_FLIGHTS];
float businessPrice[MAX_FLIGHTS];

int seats[MAX_FLIGHTS][MAX_ROWS][MAX_COLS];

int bookingID[MAX_RESERVATIONS];
int bookedFlightID[MAX_RESERVATIONS];
char passengerName[MAX_RESERVATIONS][50];
int bookedRow[MAX_RESERVATIONS];
int bookedColumn[MAX_RESERVATIONS];
char bookedClass[MAX_RESERVATIONS][20];
float ticketPrice[MAX_RESERVATIONS];
int reservationActive[MAX_RESERVATIONS];

int flightCount = 5;
int reservationCount = 0;
int nextBookingID = 1001;


void initializeFlights(void);
void displayMainMenu(void);

void displayAllFlights(void);
void searchFlights(void);
void displayFlightDetails(int index);
int findFlightByID(int id);

void displaySeats(int index);
int isSeatAvailable(int index, int row, int column);
void bookTicket(void);

int findReservationByID(int id);
void cancelReservation(void);

void checkSeatConflicts(int index);

void updateSeatAfterCancellation(int index, int row, int column);

void displayAllReservations(void);




int main(void)
{
    int choice;

    initializeFlights();

    do
    {
        displayMainMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayAllFlights();
                break;

            case 2:
                searchFlights();
                break;

            case 3:
                bookTicket();
                break;

            case 4:
                cancelReservation();
                break;

            case 5:
                displayAllReservations();
                break;

            case 6:
                printf("\nThank you for using Airline Reservation System!\n");
                printf("All data will be cleared after exit.\n");
                break;

            default:
                printf("\nInvalid choice! Enter 1 to 6.\n");
        }

    } while (choice != 6);

    return 0;
}


void initializeFlights(void)
{
    int i, j, k;

    flightID[0] = 101;
    strcpy(source[0], "Karachi");
    strcpy(destination[0], "Lahore");
    strcpy(departure[0], "09:00AM");
    economyPrice[0] = 15000;
    businessPrice[0] = 30000;

    flightID[1] = 102;
    strcpy(source[1], "Lahore");
    strcpy(destination[1], "Islamabad");
    strcpy(departure[1], "11:30AM");
    economyPrice[1] = 10000;
    businessPrice[1] = 22000;

    flightID[2] = 103;
    strcpy(source[2], "Karachi");
    strcpy(destination[2], "Islamabad");
    strcpy(departure[2], "02:00PM");
    economyPrice[2] = 18000;
    businessPrice[2] = 35000;

    flightID[3] = 104;
    strcpy(source[3], "Islamabad");
    strcpy(destination[3], "Karachi");
    strcpy(departure[3], "05:00PM");
    economyPrice[3] = 17000;
    businessPrice[3] = 32000;

    flightID[4] = 105;
    strcpy(source[4], "Lahore");
    strcpy(destination[4], "Karachi");
    strcpy(departure[4], "08:00PM");
    economyPrice[4] = 16000;
    businessPrice[4] = 31000;


    for (i = 0; i < MAX_FLIGHTS; i++)
    {
        for (j = 0; j < MAX_ROWS; j++)
        {
            for (k = 0; k < MAX_COLS; k++)
            {
                seats[i][j][k] = 0;
            }
        }
    }
}


void displayMainMenu(void)
{
    printf("\n============================================\n");
    printf("       AIRLINE RESERVATION SYSTEM\n");
    printf("============================================\n");
    printf("1. Flight Schedule Management\n");
    printf("2. Search Flights\n");
    printf("3. Book a Ticket\n");
    printf("4. Cancel a Reservation\n");
    printf("5. View All Reservations\n");
    printf("6. Exit\n");
    printf("============================================\n");
}


void displayAllFlights(void)
{
    int i;

    printf("\n================ FLIGHT SCHEDULE MANAGEMENT ================\n");

    printf("%-10s %-15s %-15s %-12s %-14s %-14s\n", "Flight ID", "From", "To", "Departure", "Economy(Rs)", "Business(Rs)");

    for (i = 0; i < flightCount; i++)
    {
        printf("%-10d %-15s %-15s %-12s %-14.2f %-14.2f\n", flightID[i], source[i], destination[i], departure[i], economyPrice[i], businessPrice[i]);
    }
}

void searchFlights(void)
{
    char searchSource[30], searchDestination[30];
    int i, found = 0;

    printf("\n================ SEARCH FLIGHTS =================\n");

    printf("Enter source city: ");
    scanf("%29s", searchSource);

    printf("Enter destination city: ");
    scanf("%29s", searchDestination);

    for (i = 0; i < flightCount; i++)
    {
        if (strcmp(source[i], searchSource) == 0 && strcmp(destination[i], searchDestination) == 0)
        {
            displayFlightDetails(i);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo flight found for this route.\n");
    }
}

void displayFlightDetails(int index)
{
    printf("\nFlight ID: %d\n", flightID[index]);
    printf("Route: %s to %s\n", source[index], destination[index]);
    printf("Departure: %s\n", departure[index]);
    printf("Economy Price: Rs. %.2f\n", economyPrice[index]);
    printf("Business Price: Rs. %.2f\n", businessPrice[index]);
}
int findFlightByID(int id)
{
    for (int i = 0; i < flightCount; i++)
    {
        if (flightID[i] == id)
        {
            return i;
        }
    }
    return -1;
}


void displaySeats(int index)
{
    int i, j;

    printf("\n================ SEAT MAP =================\n");
    printf("A = Available, X = Reserved\n");
    printf("               ECONOMY       BUSINESS\n");

    for (i = 0; i < MAX_ROWS; i++)
    {
        printf("Row %d:          ", i + 1);

        for (j = 0; j < MAX_COLS; j++)
        {
            if (seats[index][i][j] == 0)
            {
                printf("A ");
            }
            else
            {
                printf("X ");
            }

            if (j == 1)
            {
                printf("      ");
            }
        }

        printf("\n");
    }

    printf("Columns 1-2: Economy\n");
    printf("Columns 3-4: Business\n");
}

int isSeatAvailable(int index, int row, int column)
{
    if (row < 0 || row >= MAX_ROWS ||
        column < 0 || column >= MAX_COLS)
    {
        return 0;
    }
 if (seats[index][row][column] == 0)
    {
        return 1;
    }

    return 0;
}

void bookTicket(void)
{
    int id, index;
    int row, column, classChoice;
    float price;
    char name[50];

    printf("\n================ TICKET RESERVATION =================\n");

    displayAllFlights();

    printf("\nEnter Flight ID: ");
    scanf("%d", &id);

    index = findFlightByID(id);

    if (index == -1)
    {
        printf("\nInvalid Flight ID!\n");
        return;
    }

    printf("Enter passenger name (one word): ");
    scanf("%49s", name);

    printf("\n1. Economy Class\n");
    printf("2. Business Class\n");
    printf("Enter class choice: ");
    scanf("%d", &classChoice);

    if (classChoice != 1 && classChoice != 2)
    {
        printf("\nInvalid class choice!\n");
        return;
    }

    displaySeats(index);

    printf("\nEnter seat row (1-%d): ", MAX_ROWS);
    scanf("%d", &row );

    printf("Enter seat column (1-%d): ", MAX_COLS);
    scanf("%d", &column );

    row--;
    column--;

    if (classChoice == 1 && (column < 0 || column > 1))
    {
        printf("\nSelect Economy seat from columns 1 or 2.\n");
        return;
    }

    if (classChoice == 2 && (column < 2 || column > 3))
    {
        printf("\nSelect Business seat from columns 3 or 4.\n");
        return;
    }
    
   

    if (isSeatAvailable(index, row, column) == 0)
    {
        printf("\nSeat Conflict: Seat is already reserved \n");
        checkSeatConflicts(index);
        return;
    }

    if (reservationCount >= MAX_RESERVATIONS)
    {
        printf("\nReservation storage is full!\n");
        return;
    }

    if (classChoice == 1)
    {
        price = economyPrice[index];
    }
    else
    {
        price = businessPrice[index];
    }

    bookingID [reservationCount] = nextBookingID;
    bookedFlightID [reservationCount] = id;
    strcpy(passengerName [reservationCount], name);
    bookedRow [reservationCount] = row + 1;
    bookedColumn [reservationCount] = column + 1;

    if (classChoice == 1)
    {
        strcpy(bookedClass[reservationCount], "Economy");
    }
    else
    {
        strcpy(bookedClass[reservationCount], "Business");
    }

    ticketPrice[reservationCount] = price;
    reservationActive[reservationCount] = 1;


    seats[index][row][column] = 1;

    printf("\nTicket booked successfully!\n");
    printf("----------------------------------\n");
    printf("Booking ID: %d\n", nextBookingID);
    printf("Passenger: %s\n", name);
    printf("Flight ID: %d\n", id);
    printf("Seat: Row %d, Column %d\n", row + 1, column + 1);
    printf("Class: %s\n", bookedClass[reservationCount]);
    printf("Ticket Price: Rs. %.2f\n", price);
    printf("----------------------------------\n");

    reservationCount++;
    nextBookingID++;
}



int findReservationByID(int id)
{
    int i;

    for (i = 0; i < reservationCount; i++)
    {
        if (bookingID[i] == id && reservationActive[i] == 1)
        {
            return i;
        }
    }

    return -1;
}

void cancelReservation(void)
{
    int id, reservationIndex, flightIndex;
    int row, column;

    printf("\n================ RESERVATION CANCELLATION =================\n");

    printf("Enter Booking ID: ");
    scanf("%d", &id);

    reservationIndex = findReservationByID(id);

    if (reservationIndex == -1)
    {
        printf("\nBooking not found or already cancelled!\n");
        return;
    }

    flightIndex = findFlightByID(bookedFlightID[reservationIndex]);

    if (flightIndex == -1)
    {
        printf("\nFlight information not found!\n");
        return;
    }

    row = bookedRow[reservationIndex] - 1;
    column = bookedColumn[reservationIndex] - 1;

 reservationActive[reservationIndex] = 0;

    updateSeatAfterCancellation(flightIndex, row, column);

    printf("\nReservation cancelled successfully!\n");
    printf("Booking ID: %d\n", id);
    printf("The seat is now available again.\n");
}

void updateSeatAfterCancellation(int index, int row, int column)
{
    if (row >= 0 && row < MAX_ROWS && column >= 0 && column < MAX_COLS)
    {
        seats[index][row][column] = 0;
    }
}


void checkSeatConflicts(int index)
{
    int i, j;

    printf("\n================ SEAT CONFLICT MANAGEMENT =================\n");

    printf("Available seats for Flight ID %d:\n", flightID [index]);

    for (i = 0; i < MAX_ROWS; i++)
    {
        printf("Row %d: ", i + 1);

        for (j = 0; j < MAX_COLS; j++)
        {
            if (seats[index][i][j] == 0)
            {
                printf("[Column %d: Available] ", j + 1);
            }
            else
            {
                printf("[Column %d: Reserved] ", j + 1);
            }
        }

        printf("\n"); 
    }
}

void displayAllReservations(void)
{
    int i, found = 0;

    printf("\n================ ALL RESERVATIONS =================\n");

    printf("%-12s %-12s %-20s %-8s %-8s %-12s %-12s\n", "Booking ID", "Flight ID", "Passenger", "Row", "Column", "Class", "Price");

    for (i = 0; i < reservationCount; i++)
    {
        if (reservationActive[i] == 1)
        {
            printf("%-12d %-12d %-20s %-8d %-8d %-12s Rs.%-10.2f\n", bookingID[i], bookedFlightID[i], passengerName[i], bookedRow[i], bookedColumn[i], bookedClass[i], ticketPrice[i]);

            found = 1;
        }
    }

    if (found == 0)
    {
        printf("\nNo active reservations found.\n");
    }
}

