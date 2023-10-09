This program acts as a scheduler for whichever jobs are scanned through the given input file. 
After typing "make" to compile the program, your input should be:
./scheduler.c SCHEDULER_POLICY INPUT_FILE TIME_SLICE (For RR only)

The three scheduler policies are:
1. FIFO, first in first out
2  SJF, shortest job first
3 RR, round robin, with the slice time being the amount of time that the scheduler will spend on each job before switching to the next

We use a struct data structure to keep track of each job, with each job having an ID, job length, binary int to keep track if it has
been sorted, and a pointer to the next job in the linked list

We used another struct for the analysis portion, with each anaylsis node having the corresponding job's id, a response time to keep track of when
the job started executing, the turnaround time to keep track of how long it took for the job to complete, and the wait time t keep track of how much time
the job waited to be executed.

While executing the inputted scheduling policy, a node is created for each job, and the corresponding anaylsis node is made as well.

WORKLOADS:

workload_1.in: 7 jobs for the RR scheduler where each job has the same response time for all jobs (6 seconds)
workload_2.in: 11 jobs where the average turnaround for FIFO is 10 times that of SJF. FIFO has an average turnaround of 1000, while SJF's is about 100.
workload_3.in: Same as workload 1. This results in the same average response, turnaround, and wait time for all 3 scheduling policies
workload_4.in: 5 jobs where RR produces an average wait time of 2 seconds, but a turnaround time of over 200 seconds
workload_5.in: 3 jobs where FIFO produces an average response time of 5 seconds and an average turnaround tme of 13 seconds, with the first job taking 3 seconds