/*
 * lab5 - Dinning Philosophers Problem.
 * Author: maks-ym
*/
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>

#define MEALS 3
#define EATING_TIME 2
#define THINKING_TIME 4

void grab_forks(int left_fork_id);
void put_away_forks(int left_fork_id);
void dinning_routine();
void eat(int mleft);
void think();

// char* philosophers_list[5] = {"Philo 1","Philo 2","Philo 3","Philo 4","Philo 5"};
int philosopher_id, sem_id, pid, status;

int main() {
	int i=0; // temp loop counter
	/*
	On the basis of the key semget(sem_key, no_of semaphores, IPC_CREAT | access_rights)
	creates or gives access permissions to a semafores' set. If different processes want
	to access the same set of semafors, they have to use the same key.
	*/ 
	//Semaphore allocation.
	// 	-> Group Owner
	sem_id = semget(IPC_PRIVATE, 5, 0644 | IPC_CREAT); 
	if(sem_id == -1) {
		perror("Error: Failed to allocate the semaphore.\n");
		exit(1);
	}
	// semaphores initialization
	while(i < 5)
		semctl(sem_id, i++, SETVAL, 1);
	//Creating philosophers. (Child Processes)
	i = 0;
	while( i < 5 ) {
		pid = fork();
		if( pid < 0 ) {
			//terminate all created the processes
			kill(-getpgrp(),SIGTERM);
			perror("Error: failed to create a processes\n");
			exit(1);
		}
		else if(pid == 0) {
			//for each philosopher
			philosopher_id = i;
			dinning_routine();
			printf ("[Philo %d] is fed up with this game and left.\n", philosopher_id);
			return 0;
		}
		++i;
	}
	//parent process
	while(1) {
		//Terminate philosophers
		pid = wait(&status);
		if(pid < 0)
			break;
	}
	i=0;
	// Deallocation of semaphores
	//  IPC_RMID marks the segment to be destroyed
	if (semctl(sem_id, 0, IPC_RMID, 1) < 0) {
		printf("Error: failed to deallocate semaphores.\n");
	} else {
		printf("Success: semaphores deallocated\n");
	}
	return 0;
}

void grab_forks(int left_fork_id) {
	// select right fork with id one less than id of the left fork
	int right_fork_id = left_fork_id-1;
	if(right_fork_id<0)
		right_fork_id=4; // In case of Plato.
	printf("[Philo %d] grabs %d(left) and %d(right) forks.\n", 
			philosopher_id,left_fork_id, right_fork_id);
	struct sembuf semaphore_as_a_fork[2] = {
		{right_fork_id,-1,0},
		{left_fork_id,-1,0}
	};
	/*
	semop(semaphore_id, semaphore_buffer, no_of_semaphores_on_which_op_is_performed)
	Performs operations over semaphores.
	*/
	//check the value of the specified fork and verify if it's up (0) or down (1)
	semop(sem_id, semaphore_as_a_fork, 2);
}

void put_away_forks(int left_fork_id) {
	int right_fork_id = left_fork_id-1;
	if(right_fork_id<0)
		right_fork_id=4; // In case of Plato.
	printf("[Philo %d] thoughs away his forks (%d left, %d right).\n", philosopher_id, left_fork_id, right_fork_id);
	struct sembuf semaphore_as_a_fork[2] = {
		{right_fork_id,1,0},
		{left_fork_id,1,0}
	};
	semop(sem_id, semaphore_as_a_fork, 2);
}

void dinning_routine() {
	printf("[Philo %d] starts his dinning routine.\n", philosopher_id);
	int meals_num = MEALS;
	int hungry = 0;
	while(meals_num) {
		if(hungry) {
			eat(--meals_num);
			hungry = 0;
		}
		else {
			think();
			hungry = 1;
		}
	}
}

void eat(int meals_left) {
	grab_forks(philosopher_id);
	printf("[Philo %d] is eating\n", philosopher_id);
	sleep(EATING_TIME);
	printf("[Philo %d] Yummy... (%d meals left)\n", philosopher_id, (MEALS - meals_left));
	put_away_forks(philosopher_id);
}

void think() {
	switch(philosopher_id) {
		case 0:
			printf("[Philo %d] (thinking): If I download a movie in Jamaica am I a pirate of the Caribbeans?\n", philosopher_id);
			break;
		case 1:
			printf("[Philo %d] (thinking): If you spill cleaning product did you make a mess?\n", philosopher_id);
			break;
		case 2:
			printf("[Philo %d] (thinking): If two mindreader read eachothers minds whould they just be reading their own mind?\n", philosopher_id);
			break;
		case 3:
			printf("[Philo %d] (thinking): Is an argument between two vegans still called a 'beef'?\n", philosopher_id);
			break;
		case 4:
			printf("[Philo %d] (thinking): At the movie theater which armrest is yours?\n", philosopher_id);
			break;
	}
	sleep(THINKING_TIME);
}
