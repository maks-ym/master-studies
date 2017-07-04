#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/sem.h> 

#define N           5
#define LEFT        (i+N-1)%N
#define RIGHT       (i+1)%N
#define THINKING    0
#define HUNGRY      1
#define EATING      2

void philosopher_routine(int i);    /* the routine for each philosopher */
void grab_forks(int i);             /* get forks to be able to eat */
void through_forks(int i);          /* after finished throug forks away */
void check_neighbours(int i);       /* look at that... guys near i philosopher */

typedef int semaphore;
int state[N];
semaphore mutex;
semaphore s[N];


// /* for semget function */
// key_t key;  /* key to pass to semget() */       /* access value associated with the semaphore ID */
// int semflg; /* semflg to pass tosemget() */     /* initial values */
// int nsems;  /* nsems to pass to semget() */     /* number of elements in semaphore array */
// int semid;  /* return value from semget() */    /* id returned by semget() function */


// key = ... 
// nsems = ...
// semflg = ... ... 
// if ((semid = semget(key, nsems, semflg)) == -1) {
// 		perror("semget: semget failed"); 
// 		exit(1); } 
// else 

// /* for semop function */
// ... 
// int i; 
// int nsops;              /* number of operations to do */ 
// int semid;              /* semid of semaphore set */ 
// struct sembuf *sops;    /* ptr to operations to perform */ 

// //... 

// if ((semid = semop(semid, sops, nsops)) == -1) 
// { 
// 	perror("semop: semop failed"); 
//  exit(1);
// } 
// else 
// (void) fprintf(stderr, "semop: returned %d\n", i); 
// ...

int main() {
    printf("There were five philosofers in the room and each needed two forks to eat.\n");
    printf("-------------------------------------------------------------------------\n");
    
    
    return 0;
}

void think(int i) {
    printf("[philosopher %d]: Hmmm... If I download movie in Jamaica, am I a pirat of the Caribbean?\n", i);
    sleep(1);
}

void eat(i) {
    printf("[philosopher %d]: Yummy, yummy...\n", %d);
    sleep(1);
}

void got_hungry(int i) {
    printf("[philosopher %d]: I want to eat a wale!\n");
}

void philosopher_routine(int i) {
    while(1) {
        think(i);
        grab_forks(i);
        eat(i);
        through_forks(i);
    }
}

// left_fork_id replaced with i. Index f the philosopher. Consider that every
// of them starts grabbing from the left fork
void grab_forks( int i ) {
    sem_wait(&mutex); //down(&mutex);
    state[i] = HUNGRY;
    test(i);
    sem_post(&mutex); //up(&mutex);
    sem_wait(&s[i]); //down(&s[i]);
}

void put_away_forks( int i ) {
    down(&mutex); sem_wait(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex); //up(&mutex);
}

void test(int i) {
    if( state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        sem_post(&s[i]); //up(&s[i]);
    }
}
