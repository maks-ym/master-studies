//#define WITH_SIGNALS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

int NUM_CHILD = 3;
int interruption_flag;

int main(int argc, char *argv[]) {

#if WITH_SIGNALS == 1

    //handlers
    void ignoring_handler(int sig) { }

    void key_termination_handler(int sig) {
    //        if(getpid() != 0) {
            interruption_flag = 1;
            printf("parent: Key interrupt occured!\n");
    //        }
    }

    void child_termination_handler(int sig) {
            printf("child: Got SIGTERM. Terminating...");
    }

    signal(SIGINT, key_termination_handler);
    signal(SIGTERM, child_termination_handler);

    pid_t parent_pid = getpid(); //got once for optimalization. Using getpid() in the same places gives the same result
    pid_t child_pids[NUM_CHILD];
    int   statuses[NUM_CHILD];
    int   i;

    for(i = 0; i < NUM_CHILD; ++i) {
//        printf("INERUPTION FLAG: %d \n", interruption_flag);
        //check key interruption
        if (interruption_flag == 1) {
            printf("Interruption occured.\n");
            for(int j = 0; j < i; ++j) {
                kill(child_pids[j], SIGTERM);
            }
            break;
        }
        else {

            sleep(1);
            printf("parent[%d]: creating process #%d...\n", parent_pid, i);
            pid_t cur_pid = fork();
            if(cur_pid < 0) {
                printf("Error! fork() failed.");
                for(int j = 0; j < i; ++j) {
                    kill(child_pids[j], SIGTERM);
                }
                exit(-1);
            }
            if(cur_pid == 0) {
            //child process
//                signal(SIGTERM, child_termination_handler);
                pid_t current_pid = getpid();
                printf("child[%d]: #%d\n", current_pid, i);
                printf("child[%d]: #%d - sleep\n",current_pid, i);
                sleep(10);
                printf("child[%d]: #%d - awake\n",current_pid, i);
                printf("child[%d]: #%d - execution is comleted\n",current_pid, i);
                exit(0);
            }
            else {
                int sig_iter;
                for(sig_iter = 1; sig_iter <=31 ; ++sig_iter) {
                   signal(sig_iter, SIG_IGN);
                }

            }
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
    //restore default handlers
    for(i = 0; i <= 31; ++i) {
        signal(i, SIG_DFL);
    }
    exit(0);

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
                printf("Error! fork() failed.");
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
