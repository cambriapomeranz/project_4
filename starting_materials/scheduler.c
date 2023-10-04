#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Job {
    int id;
    int length; // Time to complete job
    struct Job *next; //Linked list
};

typedef struct Job Job;
void FIFO() {

}

void SJF() {

}

void  RR() {

}

int main(int argc, char argv[]){
    printf("Hello, please help me schedule!\n");
    if (argc != 4){
        printf("You need 4 arguments for this program\n");
        return 0;
    }

    int time;
    int id = 0;
    struct Job* head = NULL;
    struct Job* tail = NULL;
    struct Job* new_job = NULL;

    FILE* file = fopen(argv[2], "r");
    while (fscanf(file, "%d", &time) != EOF){
        if (head == NULL && tail == NULL){
            head->id = id;
        }
    }
    
}