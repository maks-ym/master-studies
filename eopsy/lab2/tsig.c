//#define WITH_SIGNALS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int NUM_CHILD = 10;

int main(int argc, char *argv[]) {

#if WITH_SIGNALS == 1

pid_t cur_pid, par_pid, child_pids[NUM_CHILD];
par_pid = getpid();
cur_pid = par_pid;
int interruption_flag = 0;
int i, j, l;
int statuses[NUM_CHILD];

//handlers
void ignoring_handler(int sig) { }

void key_termination_handler(int sig) {
    if(getpid() != 0) {
	    interruption_flag = 1;
	    printf("parent[%d]: Key interrupt occured===!\n", getpid());
    }
}

void child_termination_handler(int sig) {
    printf("child[%d]: Got SIGTERM. Terminating...\n", getpid());
    exit(1);
}

if(getpid() == par_pid) {
	printf("parent[%d]: ignore signals!!\n", getpid());
    for(i = 0; i <= 31; ++i) {
        signal(i, ignoring_handler);
    }
	printf("\tset: SIGCHLD to SIG_DFL\n");
    
    signal(SIGCHLD, SIG_DFL);
	printf("\tset: SIGINT to termination handler\n");

}


for(i = 0; i < NUM_CHILD; ++i) {
    printf("INERUPTION FLAG: %d \n", interruption_flag);    
    if(interruption_flag != 1) {
        printf("parent[%d]: creating process #%d...\n", par_pid, i);
    	cur_pid = fork();
        sleep(1);
        if(cur_pid < 0) {
            printf("Error! fork() failed.\n");
            for(int j = 0; j < i; ++j) {
                kill(child_pids[j], SIGTERM);
            }
            exit(1);
        }
        else if(cur_pid == 0) {
        	//child process
        	int cur_child_pid = getpid();
        	signal(SIGINT, ignoring_handler);
            signal(SIGTERM, child_termination_handler);
            printf("child[%d]: #%d\n", cur_child_pid, i);
            printf("child[%d]: #%d - sleep\n",cur_child_pid, i);
            sleep(10);
            printf("child[%d]: #%d - awake\n",cur_child_pid, i);
            printf("child[%d]: #%d - execution is comleted\n",cur_child_pid, i);
            exit(0);
        } else {
        	signal(SIGINT, key_termination_handler);
        	
        }	
    } else {
    	printf("Interruption occured.\n");
        int j;
        for(j = 0; j < i; ++j) {
        	printf("parent[%d]: Kill process #%d!\n", getpid(), j);
            kill(child_pids[j], SIGTERM);
        }
        exit(1);
    }
}


if(getpid() == par_pid) {
    printf("parent[%d]: All child processes were created.\n", par_pid);
    //wait until children finish & get statuses
    int status, counter = 0;
    pid_t tmp_pid = 0;
    while(tmp_pid != -1) {
        tmp_pid = wait(&status);
        if(tmp_pid != -1) {
            statuses[counter] = status;
            printf("parent[%d]: terminating child[%d], return code: %d\n", par_pid, tmp_pid,status);
            ++counter;
        }
    }	

    printf("parent[%d]: All child processes exited.\n", par_pid);
    printf("parent[%d]: %d status codes recieved.\n", par_pid, counter);
    //print status codes
    for(l; l < counter; ++l) {
        printf("%d\n", statuses[l]);
    }
    //restore default handlers
    for(i = 0; i <= 31; ++i) {
        signal(i, SIG_DFL);
    }
    exit(0);
    
}

// Without signals
#else

        void termination_handler(int sig)
        {
            exit(-1);
        }

        struct sigaction sa;
        memset(&sa, 0, sizeof(struct sigaction));
        sa.sa_handler = termination_handler;
        sigaction(SIGTERM, &sa, NULL);

        //	printf("parent[%d]\n", getpid());
        pid_t parent_pid = getpid(); //got once for optimalization. Using getpid() in the same places gives the same result
        pid_t child_pids[NUM_CHILD];
        int   statuses[NUM_CHILD];
        int   i;

        for(i = 0; i < NUM_CHILD; ++i) {
            sleep(1);
            printf("parent[%d]: creating process #%d...\n", parent_pid, i);
            pid_t cur_pid = fork();
            if(cur_pid < 0) {
                printf("Error! fork() failed.\n\n");
                for(int j = 0; j < i; ++j) {
                    kill(child_pids[j], SIGTERM);
                }
                exit(-1);
            }
            if(cur_pid == 0) {
            //child process
                pid_t current_pid = getpid();
                printf("child[%d]: #%d\n", current_pid, i);
                printf("child[%d]: #%d - sleep\n",current_pid, i);
                sleep(10);
                printf("child[%d]: #%d - awake\n",current_pid, i);
                printf("child[%d]: #%d - execution is comleted\n",current_pid, i);
                exit(0);
            }
        }

        //loop ended <= everything OK
        printf("parent[%d]: All child processes were created.\n", parent_pid);
        //wait until children finish & get statuses
        int status, counter = 0;
        pid_t tmp_pid = 0;
        while(tmp_pid != -1) {
            tmp_pid = wait(&status);
            if(tmp_pid != -1) {
                statuses[counter] = status;
                printf("parent[%d]: terminating child[%d], return code: %d\n", parent_pid, tmp_pid,status);
                ++counter;
            }
        }

        printf("parent[%d]: All child processes exited.\n", parent_pid);
        printf("parent[%d]: %d status codes recieved.\n", parent_pid, counter);
        //print status codes
        int l = 0;
        for(l; l < counter; ++l) {
            printf("%d\n", statuses[l]);
        }

        exit(0);

#endif // WITH_SIGNALS
}
