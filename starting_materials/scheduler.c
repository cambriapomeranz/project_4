#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Job {
    int id;
    int length; // Time to complete job
    int sorted; // Binary int to represent if a job has been sorted or not
    struct Job *next; //Linked list
};

struct Job_Analysis {
    int id;
    int response_time;
    int turnaround_time;
    int wait_time;
    struct Job_Analysis* next;
};

void FIFO(struct Job* head) {
    //printf("Execution trace with FIFO:\n");
    struct Job* current_job = head;
    struct Job_Analysis* analysis_head = NULL;
    struct Job_Analysis* analysis_tail = NULL;

    int time = 0;
    int num_jobs = 0;
    int total_response = 0;
    int total_turn = 0;
    int total_wait = 0;
    while (current_job != NULL) {
        //printf("Job %d ran for: %d\n", current_job->id, current_job->length);
        // Update analysis
        struct Job_Analysis* analysis_new = malloc(sizeof(struct Job_Analysis));
        if (analysis_head == NULL && analysis_tail == NULL){
            analysis_head = malloc(sizeof(struct Job_Analysis));
            analysis_head->id = head->id;
            analysis_head->wait_time = time;
            analysis_head->response_time = time;
            time += current_job->length;
            analysis_head->turnaround_time = time;
            analysis_head->next = NULL;
            analysis_tail = analysis_head;
            // Update Counters
            num_jobs++;
            total_response += analysis_head->response_time;
            total_turn += analysis_head->turnaround_time;
            total_wait += analysis_head->wait_time;
        } else{
            analysis_new->id = current_job->id;
            analysis_new->wait_time = time;
            analysis_new->response_time = time;
            time += current_job->length;
            analysis_new->turnaround_time = time;
            analysis_new->next = NULL;
            // Logic for adding new job to the list, changing what tail points to and then changing tail
            analysis_tail->next = analysis_new;
            analysis_tail = analysis_new;
            // Update Counters
            num_jobs++;
            total_response += analysis_new->response_time;
            total_turn += analysis_new->turnaround_time;
            total_wait += analysis_new->wait_time;
        }
        current_job = current_job->next;
    }

    //printf("End of execution with FIFO.\n");
    // Analysis
    printf("Begin analyzing FIFO:\n");
    struct Job_Analysis* current_analysis = analysis_head;
    while (current_analysis != NULL){
        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", current_analysis->id, current_analysis->response_time, current_analysis->turnaround_time, current_analysis->wait_time);
        current_analysis = current_analysis->next;
    }
    printf("Average -- Response: %.2f  Turnaround:  %.2f  Wait: %.2f\n", total_response/(num_jobs * 1.00), total_turn/(num_jobs * 1.00), total_wait/(num_jobs * 1.00));
    printf("End analyzing FIFO.\n");
}

void SJF(struct Job* head) {
    printf("Execution trace with SJF:\n");
    struct Job* current_head = head; 
    struct Job_Analysis* analysis_head = NULL;
    struct Job_Analysis* analysis_tail = NULL;

    int time = 0;
    int total_response = 0;
    int total_turn = 0;
    int total_wait = 0;

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
            // check if new_job time is smaller the min_job time, 
            // OR if they have the same time check which has the smaller id
            if((new_job->length < min_job->length || (new_job->length == min_job->length && new_job->id < min_job->id)) && new_job->sorted != 1) {
                min_job = new_job;
            }
            new_job = new_job->next;
        }
        min_job->sorted = 1;
        jobs_sorted++;

        printf("Job %d ran for: %d\n", min_job->id, min_job->length);
        // Update analysis
        struct Job_Analysis* analysis_new = malloc(sizeof(struct Job_Analysis));
        if (analysis_head == NULL && analysis_tail == NULL){
            analysis_head = malloc(sizeof(struct Job_Analysis));
            analysis_head->id = min_job->id;
            analysis_head->wait_time = time;
            analysis_head->response_time = time;
            time += min_job->length;
            analysis_head->turnaround_time = time;
            analysis_head->next = NULL;
            analysis_tail = analysis_head;
            // Update Counters
            total_response += analysis_head->response_time;
            total_turn += analysis_head->turnaround_time;
            total_wait += analysis_head->wait_time;
        } else{
            analysis_new->id = min_job->id;
            analysis_new->wait_time = time;
            analysis_new->response_time = time;
            time += min_job->length;
            analysis_new->turnaround_time = time;
            analysis_new->next = NULL;
            // Logic for adding new job to the list, changing what tail points to and then changing tail
            analysis_tail->next = analysis_new;
            analysis_tail = analysis_new;
            // Update Counters
            total_response += analysis_new->response_time;
            total_turn += analysis_new->turnaround_time;
            total_wait += analysis_new->wait_time;
        }
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
    printf("End of execution with SJF.\n");

    // Analysis
    printf("Begin analyzing SJF:\n");
    struct Job_Analysis* current_analysis = analysis_head;
    while (current_analysis != NULL){
        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", current_analysis->id, current_analysis->response_time, current_analysis->turnaround_time, current_analysis->wait_time);
        current_analysis = current_analysis->next;
    }
    printf("Average -- Response: %.2f  Turnaround:  %.2f  Wait: %.2f\n", total_response/(num_jobs * 1.00), total_turn/(num_jobs * 1.00), total_wait/(num_jobs * 1.00));
    printf("End analyzing SJF.\n");
}

void RR(struct Job* head, int time_slice) {
    printf("Execution trace with RR:\n");
    struct Job* current_job = head;
    int jobs_left = 1;
    while(jobs_left == 1) {
        jobs_left = 0;
        current_job = head;
        while (current_job != NULL) {
            if (current_job->length > time_slice) {
                jobs_left = 1;
                printf("Job %d ran for: %d\n", current_job->id, time_slice);
                current_job->length -= time_slice;
            }
            else if (current_job->length > 0) {
                printf("Job %d ran for: %d\n", current_job->id, current_job->length);
                current_job->length = 0;
            }
            current_job = current_job->next;
        }
    }
    printf("End of execution with RR.\n");
}

int main(int argc, char *argv[]){
    if (argc != 4){
        printf("You need 4 arguments for this program\n");
        return 0;
    }

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
        if(atoi(argv[3]) == 0){
            printf("Time slice must be greater than 0\n");
        } else{
            RR(head, atoi(argv[3]));
        }
    } else{
        printf("The policy you inputted is not correct\n");
    }
}