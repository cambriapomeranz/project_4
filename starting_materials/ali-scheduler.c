#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct job {
    int id;
    int length;
    struct job* next;
};

struct jobAnalysis {
    int id;
    int responseTime;
    int turnaroundTime;
    int waitTime;
    struct jobAnalysis* next;
};

FILE *fp;

void fifo(struct job* orignal_head) {
    struct job* temp_head = orignal_head;
    struct jobAnalysis* analysis_head = NULL;
    struct jobAnalysis* analysis_tail = NULL;
    struct jobAnalysis* analysis_new = NULL;
    int time = 0;
    float avg_response = 0;
    float avg_turnaround = 0;
    float avg_wait = 0;
    int idCounter = 0;

    printf("Execution trace with FIFO:\n");

    while (temp_head != NULL) {
        struct job* temp_new = NULL;
        printf("Job %d ran for: %d\n", temp_head->id, temp_head->length);

        if (analysis_head == NULL && analysis_tail == NULL) {
            analysis_head = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
            analysis_head->id = temp_head->id;
            analysis_head->responseTime = time;
            analysis_head->turnaroundTime = time + temp_head->length;
            analysis_head->waitTime = time;

            analysis_tail = analysis_head;
        }
        else {
            analysis_new = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
            analysis_new->id = temp_head->id;
            analysis_new->responseTime = time;
            analysis_new->turnaroundTime = time + temp_head->length;
            analysis_new->waitTime = time;

            analysis_tail->next = analysis_new;
            analysis_tail = analysis_new;
        }

        time += temp_head->length;

        temp_new = temp_head;
        temp_head = temp_head->next;
        free(temp_new);
    }

    printf("End of execution with FIFO.\n");

    printf("Begin analyzing FIFO:\n");

    while (analysis_head != NULL) {
        struct jobAnalysis* analysis_old = NULL;

        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", analysis_head->id, analysis_head->responseTime, analysis_head->turnaroundTime, analysis_head->waitTime);

        avg_response += analysis_head->responseTime;
        avg_turnaround += analysis_head->turnaroundTime;
        avg_wait += analysis_head->waitTime;
        idCounter++;

        analysis_old = analysis_head;
        analysis_head = analysis_head->next;
        free(analysis_old);
    }

    avg_response = avg_response / idCounter;
    avg_turnaround = avg_turnaround / idCounter;
    avg_wait = avg_wait / idCounter;

    printf("Average -- Response: %0.2f  Turnaround: %0.2f  Wait: %0.2f\n", avg_response, avg_turnaround, avg_wait);
    
    printf("End analyzing FIFO.\n");
}

void sjf(struct job* original_head) {
    printf("Execution trace with SJF:\n");

    struct job* temp_head = original_head;
    struct jobAnalysis* analysis_head = NULL;
    struct jobAnalysis* analysis_tail = NULL;
    struct jobAnalysis* analysis_new = NULL;
    int time = 0;
    float avg_response = 0;
    float avg_turnaround = 0;
    float avg_wait = 0;
    int idCounter = 0;
    int shortrt;
    
    while (temp_head != NULL) {
        struct job* sjf_new = NULL;
        struct job* temp_sjf_prev = NULL;
        struct job* sjf_head = temp_head;
        struct job* temp_prev = NULL;

        shortrt = __INT_MAX__;

        while (sjf_head != NULL) {
            if (sjf_head->length < shortrt) {
                sjf_new = sjf_head;
                temp_sjf_prev = temp_prev;
                shortrt = sjf_head->length;
            }

            temp_prev = sjf_head;
            sjf_head = sjf_head->next;
        }

        printf("Job %d ran for: %d\n", sjf_new->id, sjf_new->length);

        if (analysis_head == NULL && analysis_tail == NULL) {
            analysis_head = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
            analysis_head->id = sjf_new->id;
            analysis_head->responseTime = time;
            analysis_head->turnaroundTime = time + sjf_new->length;
            analysis_head->waitTime = time;

            analysis_tail = analysis_head;
        }
        else {
            analysis_new = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
            analysis_new->id = sjf_new->id;
            analysis_new->responseTime = time;
            analysis_new->turnaroundTime = time + sjf_new->length;
            analysis_new->waitTime = time;

            analysis_tail->next = analysis_new;
            analysis_tail = analysis_new;
        }

        time += sjf_new->length;   

        if (temp_sjf_prev != NULL) {
            temp_sjf_prev->next = sjf_new->next;
            free(sjf_new);
        }
        
        else {
            temp_head = temp_head->next;
            free(sjf_new);
        }
    }

    printf("End of execution with SJF.\n");

    printf("Begin analyzing SJF:\n");

    while (analysis_head != NULL) {
        struct jobAnalysis* analysis_old = NULL;

        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", analysis_head->id, analysis_head->responseTime, analysis_head->turnaroundTime, analysis_head->waitTime);

        avg_response += analysis_head->responseTime;
        avg_turnaround += analysis_head->turnaroundTime;
        avg_wait += analysis_head->waitTime;
        idCounter++;

        analysis_old = analysis_head;
        analysis_head = analysis_head->next;
        free(analysis_old);
    }

    avg_response = avg_response / idCounter;
    avg_turnaround = avg_turnaround / idCounter;
    avg_wait = avg_wait / idCounter;

    printf("Average -- Response: %0.2f  Turnaround: %0.2f  Wait: %0.2f\n", avg_response, avg_turnaround, avg_wait);    

    printf("End analyzing SJF.\n");
}

void rr(struct job* original_head, struct job* original_tail, int timeslice, int IDCount) {
    printf("Execution trace with RR:\n");

    struct job* temp_head = original_head;
    struct job* temp_tail = original_tail;
    struct jobAnalysis* analysis_head = NULL;
    struct jobAnalysis* analysis_tail = NULL;
    struct jobAnalysis* analysis_new = NULL;
    int time = 0;
    float avg_response = 0;
    float avg_turnaround = 0;
    float avg_wait = 0;
    int idCounter = 0;
    
    while (temp_head != NULL) {
        if (temp_head->length > timeslice) {
            printf("Job %d ran for: %d\n", temp_head->id, timeslice);

            temp_head->length -= timeslice;

            if (analysis_head == NULL && analysis_tail == NULL) {
                analysis_head = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
                analysis_head->id = temp_head->id;
                analysis_head->responseTime = time;
                analysis_head->waitTime = 0 - timeslice;

                analysis_tail = analysis_head;
                if (analysis_tail->id == IDCount) {
                    IDCount = -1;
                }
            }
            else if (analysis_tail->id <= IDCount && IDCount != -1) {
                analysis_new = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
                analysis_new->id = temp_head->id;
                analysis_new->responseTime = time;
                analysis_new->waitTime = 0 - timeslice;

                analysis_tail->next = analysis_new;
                analysis_tail = analysis_new;
                if (analysis_tail->id == IDCount) {
                    IDCount = -1;
                }
            } 
            else {
                while (analysis_head->id != temp_head->id) {
                    analysis_tail->next = analysis_head;
                    analysis_tail = analysis_tail->next;
                    analysis_head = analysis_head->next;
                    analysis_tail->next = NULL;
                }
                analysis_head->waitTime -= timeslice;
            }

            time += timeslice;

            temp_tail->next = temp_head;
            temp_tail = temp_tail->next;
            temp_head = temp_head->next;
            temp_tail->next = NULL;
        }
        else {
            struct job* temp_new = NULL;
            printf("Job %d ran for: %d\n", temp_head->id, temp_head->length);

            if (analysis_head == NULL && analysis_tail == NULL) {
                analysis_head = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
                analysis_head->id = temp_head->id;
                analysis_head->responseTime = time;
                analysis_head->turnaroundTime = time + temp_head->length;
                analysis_head->waitTime = time;

                analysis_tail = analysis_head;
                if (analysis_tail->id == IDCount) {
                    IDCount = -1;
                }
            }
            else if (analysis_tail->id <= IDCount && IDCount != -1) {
                analysis_new = (struct jobAnalysis*) malloc(sizeof(struct jobAnalysis));
                analysis_new->id = temp_head->id;
                analysis_new->responseTime = time;
                analysis_new->turnaroundTime = time + temp_head->length;
                analysis_new->waitTime = time;

                analysis_tail->next = analysis_new;
                analysis_tail = analysis_new;

                if (analysis_tail->id == IDCount) {
                    IDCount = -1;
                }
            } 
            else {
                while (analysis_head->id != temp_head->id) {
                    analysis_tail->next = analysis_head;
                    analysis_tail = analysis_tail->next;
                    analysis_head = analysis_head->next;
                    analysis_tail->next = NULL;
                }
                analysis_head->turnaroundTime = time + temp_head->length;
                analysis_head->waitTime += time;
            }

            time += temp_head->length;

            temp_new = temp_head;
            temp_head = temp_head->next;
            free(temp_new);
        }

    }

    printf("End of execution with RR.\n");

    printf("Begin analyzing RR:\n");

    while (analysis_head->id != 0) {
        analysis_tail->next = analysis_head;
        analysis_tail = analysis_tail->next;
        analysis_head = analysis_head->next;
        analysis_tail->next = NULL;
    }

    while (analysis_head != NULL) {
        struct jobAnalysis* analysis_old = NULL;

        printf("Job %d -- Response time: %d  Turnaround: %d  Wait: %d\n", analysis_head->id, analysis_head->responseTime, analysis_head->turnaroundTime, analysis_head->waitTime);

        avg_response += analysis_head->responseTime;
        avg_turnaround += analysis_head->turnaroundTime;
        avg_wait += analysis_head->waitTime;
        idCounter++;

        analysis_old = analysis_head;
        analysis_head = analysis_head->next;
        free(analysis_old);
    }

    avg_response = avg_response / idCounter;
    avg_turnaround = avg_turnaround / idCounter;
    avg_wait = avg_wait / idCounter;

    printf("Average -- Response: %0.2f  Turnaround: %0.2f  Wait: %0.2f\n", avg_response, avg_turnaround, avg_wait);        

    printf("End analyzing RR.\n");
}

int main(int argc, char *argv[]){

    if (argc != 4) {
        printf("Exactly 4 arguments are required.\n");
        return 1;
    }

    char sp[5];
    memcpy(sp, argv[1], 5);

    char filename[100];
    memcpy(filename, argv[2], 100);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("file cant be found.\n");
        return 1;
    }

    int timeslice = atoi(argv[3]);

    char jobtimeScan[10];
    int jobtime;

    struct job* head = NULL;
    struct job* tail = NULL;
    struct job* new_job = NULL;

    int IDcount = 0;

    while (fscanf(fp, "%s", jobtimeScan) != EOF) {
        jobtime = atoi(jobtimeScan);
        if (head == NULL && tail == NULL) {
            head = (struct job*) malloc(sizeof(struct job));
            head->id = IDcount;
            head->length = jobtime;
            head->next = NULL;

            tail = head;
            IDcount++;
        }
        else {
            new_job = (struct job*) malloc(sizeof(struct job));
            new_job->id = IDcount;
            new_job->length = jobtime;
            new_job->next = NULL;

            tail->next = new_job;
            tail = new_job;
            IDcount++;
        }
    }

    IDcount--;

    if (strcmp(sp, "FIFO") == 0) {
        fifo(head);
    }

    else if (strcmp(sp, "SJF") == 0) {
        sjf(head);
    }

    else if (strcmp(sp, "RR") == 0) {
        rr(head, tail, timeslice, IDcount);
    }

    else {
        printf("The scheduling policy must be one of FIFO, SJF, RR.\n");
        return 1;
    }

    return 0;
}