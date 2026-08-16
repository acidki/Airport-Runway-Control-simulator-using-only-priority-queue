#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FlightNode {
    char flightNumber[16];
    char airline[32];
    struct FlightNode* next;
};

struct FlightQueue {
    struct FlightNode* front;
    struct FlightNode* rear;
};

void initQueue(struct FlightQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmpty(struct FlightQueue* q) {
    return q->front == NULL;
}

void enqueue(struct FlightQueue* q, char flightNo[], char airLine[]) {
    struct FlightNode* newNode = (struct FlightNode*)malloc(sizeof(struct FlightNode));
    strcpy(newNode->flightNumber, flightNo);
    strcpy(newNode->airline, airLine);
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(struct FlightQueue* q, char flightNoOut[], char airLineOut[]) {
    if (isEmpty(q)) {
        return 0;
    }

    struct FlightNode* temp = q->front;
    strcpy(flightNoOut, temp->flightNumber);
    strcpy(airLineOut, temp->airline);

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return 1;
}

void displayQueue(struct FlightQueue* q, const char* queueName) {
    printf("\n--- %s ---\n", queueName);
    if (isEmpty(q)) {
        printf("(No flights waiting)\n");
        return;
    }

    struct FlightNode* temp = q->front;
    int position = 1;
    while (temp != NULL) {
        printf("%d. Flight %s [%s]\n", position++, temp->flightNumber, temp->airline);
        temp = temp->next;
    }
}

int main() {
    struct FlightQueue emergencyQueue;
    struct FlightQueue regularQueue;

    initQueue(&emergencyQueue);
    initQueue(&regularQueue);

    int choice;
    char flightNo[16];
    char airline[32];

    while (1) {
        printf("\n=========================================\n");
        printf("   AIRPORT RUNWAY TRAFFIC CONTROLLER     \n");
        printf("=========================================\n");
        printf("1. Request Normal Landing / Takeoff\n");
        printf("2. Request EMERGENCY Landing (Priority)\n");
        printf("3. Clear Runway for Next Flight\n");
        printf("4. View All Waiting Flights\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            break;
        }
        getchar();

        switch (choice) {
            case 1:
                printf("Enter Flight Number (e.g., BG349): ");
                fgets(flightNo, sizeof(flightNo), stdin);
                flightNo[strcspn(flightNo, "\n")] = 0;

                printf("Enter Airline Name (e.g., Biman Bangladesh): ");
                fgets(airline, sizeof(airline), stdin);
                airline[strcspn(airline, "\n")] = 0;

                enqueue(&regularQueue, flightNo, airline);
                printf("-> Flight %s added to Regular Queue.\n", flightNo);
                break;

            case 2:
                printf("Enter Emergency Flight Number (e.g., EM-911): ");
                fgets(flightNo, sizeof(flightNo), stdin);
                flightNo[strcspn(flightNo, "\n")] = 0;

                printf("Enter Airline Name: ");
                fgets(airline, sizeof(airline), stdin);
                airline[strcspn(airline, "\n")] = 0;

                enqueue(&emergencyQueue, flightNo, airline);
                printf("-> [ALERT] Flight %s routed to EMERGENCY Queue!\n", flightNo);
                break;

            case 3:
                if (dequeue(&emergencyQueue, flightNo, airline)) {
                    printf("\n===================================================\n");
                    printf(" [CLEARANCE GRANTED - EMERGENCY]\n");
                    printf(" Runway cleared for PRIORITY LANDING: %s (%s)\n", flightNo, airline);
                    printf("===================================================\n");
                } 
                else if (dequeue(&regularQueue, flightNo, airline)) {
                    printf("\n===================================================\n");
                    printf(" [CLEARANCE GRANTED - REGULAR]\n");
                    printf(" Runway cleared for standard schedule: %s (%s)\n", flightNo, airline);
                    printf("===================================================\n");
                } 
                else {
                    printf("\n-> Runway is currently idle. No planes in queue.\n");
                }
                break;

            case 4:
                displayQueue(&emergencyQueue, "EMERGENCY QUEUE (Priority 1)");
                displayQueue(&regularQueue, "REGULAR QUEUE (Priority 2)");
                break;

            case 5:
                printf("Shutting down Air Traffic Control system.\n");
                return 0;

            default:
                printf("Invalid option! Please choose between 1 and 5.\n");
        }
    }

    return 0;
}