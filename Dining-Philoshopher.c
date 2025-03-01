 *******Source Code*******
 #include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 4  // Number of philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define MAX_EAT_TIMES 3  // Each philosopher eats this many times

int state[N];   // Track philosopher state
int phil[N] = {0, 1, 2, 3};  // Philosopher identifiers

sem_t mutex;    // Semaphore for critical section
sem_t S[N];     // Semaphore for each philosopher

void test(int philosopher) {
    if (state[philosopher] == HUNGRY &&
        state[(philosopher + 3) % N] != EATING &&
        state[(philosopher + 1) % N] != EATING) {

        state[philosopher] = EATING;
        printf("Philosopher %d takes forks %d and %d and starts EATING\n",
               philosopher, (philosopher + 3) % N, philosopher);
        sleep(2);
        printf("Philosopher %d finishes eating\n", philosopher);
        sem_post(&S[philosopher]);  // Allow philosopher to eat
    }
}

void take_fork(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is HUNGRY\n", philosopher);
    test(philosopher);
    sem_post(&mutex);
    sem_wait(&S[philosopher]);
    sleep(1);
}

void put_fork(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = THINKING;
    printf("Philosopher %d puts forks %d and %d down and starts THINKING\n",
           philosopher, (philosopher + 3) % N, philosopher);
    test((philosopher + 3) % N);
    test((philosopher + 1) % N);
    sem_post(&mutex);
}

void *philosopher(void *num) {
    int *i = num;
    for (int eat_count = 0; eat_count < MAX_EAT_TIMES; eat_count++) {
        printf("Philosopher %d is THINKING\n", *i);
        sleep(1);
        take_fork(*i);
        sleep(1);
        put_fork(*i);
    }
    printf("Philosopher %d has finished eating and is leaving.\n", *i);
    return NULL;
}

int main() {
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is created\n", i);
    }

    for (int i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    printf("All philosophers have finished eating. Simulation ends.\n");
    return 0;
}

********Output**********
Philosopher 0 is created
Philosopher 0 is THINKING
Philosopher 1 is created
Philosopher 1 is THINKING
Philosopher 2 is created
Philosopher 2 is THINKING
Philosopher 3 is created
Philosopher 3 is THINKING
Philosopher 3 is HUNGRY
Philosopher 3 takes forks 2 and 3 and starts EATING
Philosopher 3 finishes eating
Philosopher 1 is HUNGRY
Philosopher 1 takes forks 0 and 1 and starts EATING
Philosopher 1 finishes eating
Philosopher 2 is HUNGRY
Philosopher 0 is HUNGRY
Philosopher 3 puts forks 2 and 3 down and starts THINKING
Philosopher 3 is THINKING
Philosopher 3 is HUNGRY
Philosopher 3 takes forks 2 and 3 and starts EATING
Philosopher 3 finishes eating
Philosopher 1 puts forks 0 and 1 down and starts THINKING
Philosopher 1 is THINKING
Philosopher 1 is HUNGRY
Philosopher 1 takes forks 0 and 1 and starts EATING
Philosopher 1 finishes eating
Philosopher 3 puts forks 2 and 3 down and starts THINKING
Philosopher 3 is THINKING
Philosopher 3 is HUNGRY
Philosopher 3 takes forks 2 and 3 and starts EATING
Philosopher 3 finishes eating
Philosopher 1 puts forks 0 and 1 down and starts THINKING
Philosopher 1 is THINKING
Philosopher 1 is HUNGRY
Philosopher 1 takes forks 0 and 1 and starts EATING
Philosopher 1 finishes eating
Philosopher 3 puts forks 2 and 3 down and starts THINKING
Philosopher 3 has finished eating and is leaving.
Philosopher 1 puts forks 0 and 1 down and starts THINKING
Philosopher 0 takes forks 3 and 0 and starts EATING
Philosopher 0 finishes eating
Philosopher 2 takes forks 1 and 2 and starts EATING
Philosopher 2 finishes eating
Philosopher 1 has finished eating and is leaving.
Philosopher 0 puts forks 3 and 0 down and starts THINKING
Philosopher 0 is THINKING
Philosopher 0 is HUNGRY
Philosopher 0 takes forks 3 and 0 and starts EATING
Philosopher 0 finishes eating
Philosopher 2 puts forks 1 and 2 down and starts THINKING
Philosopher 2 is THINKING
Philosopher 2 is HUNGRY
Philosopher 2 takes forks 1 and 2 and starts EATING
Philosopher 2 finishes eating
Philosopher 0 puts forks 3 and 0 down and starts THINKING
Philosopher 0 is THINKING
Philosopher 0 is HUNGRY
Philosopher 0 takes forks 3 and 0 and starts EATING
Philosopher 0 finishes eating
Philosopher 2 puts forks 1 and 2 down and starts THINKING
Philosopher 2 is THINKING
Philosopher 2 is HUNGRY
Philosopher 2 takes forks 1 and 2 and starts EATING
Philosopher 2 finishes eating
Philosopher 0 puts forks 3 and 0 down and starts THINKING
Philosopher 0 has finished eating and is leaving.
Philosopher 2 puts forks 1 and 2 down and starts THINKING
Philosopher 2 has finished eating and is leaving.
All philosophers have finished eating. Simulation ends.