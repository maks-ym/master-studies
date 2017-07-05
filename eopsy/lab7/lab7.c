/*
 * lab7 - Dinning Philosophers Problem (pthread used)
 * Author: maks-ym
*/

/*
 * The Dining Philosophers
 * -------------------------------------------------------------------------------
 * The Dining Philosophers problem is a classic multi-process synchronization
 * problem. The problem consists of five philosophers sitting at a table who do
 * nothing but think and eat. Between each philosopher, there is a single fork
 * In order to eat, a philosopher must have both forks. A problem can arise if
 * each philosopher grabs the fork on the right, then waits for the fork on the
 * left. In this case a deadlock has occurred, and all philosophers will starve.
 * Also, the philosophers should be fair. Each philosopher should be able to eat
 * as much as the rest.
*/

#include <pthread.h>    //pthread_create(), thread_join(),
                        //pthread_mutex_init(), pthread_mutex_lock(), pthread_mutex_unlock()
#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <assert.h>     //assert()
#include <unistd.h>     //sleep()

#define NUM_THREADS     5
#define N               5
#define LEFT            (i+N-1)%N
#define RIGHT           (i+1)%N
#define THINKING        0
#define HUNGRY          1
#define EATING          2
#define THINKING_TIME   2
#define EATING_TIME     1

//used for coloring philo's statement
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void* philosopher_routine( void* i);    /* the routine for each philosopher */
void grab_forks(int i);                 /* get forks to be able to eat */
void through_forks(int i);              /* after finished throug forks away */
void test( int i );
void think( int i );
void eat( int i );

int state[N];
int meals[N] = {3,3,3,3,3};
pthread_mutex_t m;
pthread_mutex_t s[N];

int main( int argc, char** argv )
{
    pthread_t threads[ NUM_THREADS ];
    int thread_args[ NUM_THREADS ];
    int result_code;
    unsigned index;


    // printf("[DEBUG]: Mutex initialization.\n");
    pthread_mutex_init(&m, NULL);
    for( index = 0; index < N; ++index ) {
        pthread_mutex_init(&s[index], NULL);
    }

    // create all threads one by one
    for( index = 0; index < NUM_THREADS; ++index )
    {
        thread_args[ index ] = index;
        printf("[Table]: Philo %d joined.\n", index + 1 );
        result_code = pthread_create( &threads[index], NULL, philosopher_routine, &thread_args[index] );
        assert( !result_code );
    }

    // wait for each thread to complete
    for( index = 0; index < NUM_THREADS; ++index )
    {
        result_code = pthread_join( threads[ index ], NULL );
        assert( !result_code );
        printf( "[Table]: Philo %d left.\n", index + 1 );
    }

    printf( "[Table]: All philos left the table.\n" );
    exit( EXIT_SUCCESS );
}



void* philosopher_routine( void* argument ) {
  
    int passed_in_value = *( ( int* )argument );
    // printf("[DEBUG]: thread with argument %d!\n", passed_in_value );
    printf("[Philo %d]: is beginning his routine...\n", passed_in_value + 1 );
    while( meals[passed_in_value] > 0 ) {
        think(passed_in_value);
        grab_forks(passed_in_value);
        eat(passed_in_value);
        through_forks(passed_in_value);
    }
    printf("[Philo %d]: finished his routine...\n", passed_in_value + 1 );
    return NULL;
}

void grab_forks( int i ) {
    printf("[Philo %d]: is trying to survive and grabbing the forks...\n", i + 1 );
    pthread_mutex_lock(&m);
    state[i] = HUNGRY;
    test(i);
    pthread_mutex_unlock(&m);
    pthread_mutex_lock(&s[i]);
}

void through_forks( int i ) {
    printf("[Philo %d]: is fed and throughing fork out. "
           "He doesn't like his neighbours...\n", i + 1 );
    pthread_mutex_lock(&m);
    state[i] = THINKING;    
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&m);
}

void test(int i) {
    printf("[Philo %d]: is assassing the situation ...\n", i + 1 );
    if( state[i] == HUNGRY 
            && state[LEFT] != EATING 
            && state[RIGHT] != EATING) {
        state[i] = EATING;
        pthread_mutex_unlock(&s[i]);
    }
}

void think(int philosopher_id ) {
    ++philosopher_id;
    printf("[Philo %d]: thinking...\n", philosopher_id );
    switch(philosopher_id) {
		case 1:
			printf(ANSI_COLOR_YELLOW "[Philo %d]: 'If I download a movie in Jamaica am I a pirate of the Caribbeans?'"ANSI_COLOR_RESET"\n", philosopher_id);
			break;
		case 2:
			printf(ANSI_COLOR_YELLOW "[Philo %d]: 'If you spill cleaning product did you make a mess?'"ANSI_COLOR_RESET"\n", philosopher_id);
			break;
		case 3:
			printf(ANSI_COLOR_YELLOW "[Philo %d]: 'If two mindreaders read eachothers minds whould they just be reading their own mind?'"ANSI_COLOR_RESET"\n", philosopher_id);
			break;
		case 4:
			printf(ANSI_COLOR_YELLOW "[Philo %d]: 'Is an argument between two vegans still called a 'beef'?'"ANSI_COLOR_RESET"\n", philosopher_id);
			break;
		case 5:
			printf(ANSI_COLOR_YELLOW "[Philo %d]: 'At the movie theater which armrest is yours?'"ANSI_COLOR_RESET"\n", philosopher_id);
			break;
		default:
			printf(ANSI_COLOR_YELLOW "[Some Philo] (thinking)..."ANSI_COLOR_RESET"\n");
			break;
	}
    sleep(THINKING_TIME);
}

void eat( int philosopher_id ) {
    --meals[philosopher_id];
    printf("[Philo %d]: eating... (as an animal)\n", philosopher_id + 1 );
    sleep(EATING_TIME);
}


//Answers to Additional questions:
//
// 1. Would it be sufficient just to add to the old algorithm from task5
// additional mutex variable to organize critical sections in functions
// grab_forks() and put_away_forks() for making changes to values of two mutexes
// indivisably?  If not, why?
// -- No, because we need to add testing function to test available resorses
//    before trying to "grab"

// 2. Why m mutex is initialized with 1 and mutexes from the array s are
// initialized with 0's?
// -- we iniilize m with 1 to control critical region and array with 0 to make 
//    threads selfstopping when they don't need critical region.
