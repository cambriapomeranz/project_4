#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Job {
    int id;
    int length; // Time to complete job
    int sorted; // Binary int to represent if a job has been sorted or not
    struct Job *next; //Linked list
};

void FIFO(struct Job* head) {
    printf("Peforming the FIFO policy:\n");
    struct Job* current_job = head;

    while (current_job != NULL) {
        printf("Job %d ran for: %d\n", current_job->id, current_job->length);
        current_job = current_job->next;
    }
}

void SJF(struct Job* head) {
    printf("Peforming the SJF policy:\n");
    struct Job* current_head = head; 

    // Gets the number of jobs
    int num_jobs;
    if (head != NULL){
        num_jobs = 1;
    } else{
        num_jobs = 0;
    }
    
    while(current_head->next != NULL){
        num_jobs++;
        current_head = current_head->next;
    }

     // sort jobs in order of shortest run time first
    int jobs_sorted = 0;
    struct Job* min_job = current_head;
    while (jobs_sorted != num_jobs) {
        current_head = head;
        struct Job* new_job = current_head->next; 
        while (new_job != NULL) {
            // check if new_job time is smaller the min _job time, 
            // OR if they have the same time check which has the smaller id
            if((new_job->length < min_job->length || (new_job->length == min_job->length && new_job->id < min_job->id)) && new_job->sorted != 1) {
                min_job = new_job;
            }
            new_job = new_job->next;
        }
        min_job->sorted = 1;
        jobs_sorted++;
        printf("Job %d ran for: %d\n", min_job->id, min_job->length);
        while (current_head->next != NULL)
        {
            if(current_head->sorted == 0){
                min_job = current_head;
                break;
            } else if(current_head->next->sorted == 0){
                min_job = current_head->next;
                break;
            } else{
                current_head = current_head->next;
            }
        }
    }
}

void  RR(struct Job* head, int time_slice) {
    printf("Peforming the RR policy:\n");
    struct Job* current_job = head;

    while (current_job != NULL) {
        
        printf("Job %d ran for: %d\n", current_job->id, current_job->length);
        current_job = current_job->next;
    }
}

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("You need 4 arguments for this program\n");
        return 0;
    }
    printf("Hello, please help me schedule!\n");

    int time;
    int id = 0;
    struct Job* head = NULL;
    struct Job* tail = NULL;

    FILE* file = fopen(argv[2], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1; // Return an error code
    }

    while (fscanf(file, "%d", &time) != EOF){
        struct Job* new_job = malloc(sizeof(struct Job)); // Allocate memory for a new job
        if (new_job == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 0;
        }

        if (head == NULL && tail == NULL){
            head = malloc(sizeof(struct Job));
            head->id = id;
            head->length = time;
            head->sorted = 0;
            head->next = NULL;
            tail = head;
            id++;
        } else{
            new_job->id = id;
            new_job->length = time;
            new_job->sorted = 0;
            new_job->next = NULL;
            // Logic for adding new job to the list, changing what tail points to and then changing tail
            tail->next = new_job;
            tail = new_job;
            id++;
        }
    } 
    fclose(file);

    if (strcmp(argv[1], "FIFO") == 0){
        FIFO(head);
    } else if (strcmp(argv[1], "SJF") == 0){
        SJF(head);
    } else if (strcmp(argv[1], "RR") == 0){
        RR(head, argv[4]);
    } else{
        printf("The policy you inputted is not correct\n");
    }
}