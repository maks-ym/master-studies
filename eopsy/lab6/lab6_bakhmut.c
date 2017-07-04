/** 
 *  EOPSY
 *  Lab 6 - copy program
 *  Author: Maksym Bakhmut
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>      //open(). close(), read(), write()
#include <unistd.h>     //getopt()

//TODO:
// 1. help
// 2. using read() and write()
// 3. using mmap()

void show_help();

int main(int argc, char **argv) {
    //check arguments passed to the program
    if(argc == 1) {
        printf("argc = %d\n", argc); //DEBUG
        show_help();
        exit(1);
    }
    if(argc > 4) {
        printf("argc = %d\n", argc); //DEBUG
        printf("Error: too many arguments passed to the program.\n");
        printf("Use 'copy -h' for help\n");
        exit(1);
    }
    printf("argc = %d\n", argc);

    //if everything is OK, execute

    int mflag = 0;
    char *old_fname = NULL;
    char *new_fname = NULL;
    int index, i;
    int c;

    //show/hide error messages from getopt(): show  - 1, hide - 0
    opterr = 0;

    while ((c = getopt (argc, argv, "hm")) != -1) {
      switch (c) {
        case 'h':
          show_help();
          exit(0);
          break;
        case 'm':
          mflag = 1;
          //old_fname = optarg;
          break;
        //case of error
        case '?':
            printf("Error: inappropriate argument passed\n");
            printf("Use 'copy -h' for help\n");
            return 1;
        default:
          abort();
        }
    }

    //read filenames
    printf("optind before read = %d\n", optind);
    printf("argv[optind] = %s\n", argv[optind]);

    old_fname = argv[optind++];
    new_fname = argv[optind++];
    printf("optind after read = %d\n", optind);
    if( old_fname == NULL || new_fname == NULL ) {
        printf("Error: to few arguments.\n");
        exit(1);
    }

    //read
    

    //if more arguments passes
    if (optind < argc) {
        printf("Too many arguments. The rest args will be dropped out.\n");
        printf("Trying to execute...\n");
    }

    //copying file
    //open files to read and to write
    int src_file  = open( old_fname,  O_RDONLY );
    int dest_file = open( new_fname,  O_WRONLY | O_WRONLY );




    //close file streams
    close( src_file );
    close( dest_file );



    //TODO: change OR remove
    printf ("Printf of example:\nmflag = %d, old_fname = %s\n",
            mflag, old_fname);

    for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
    return 0;

}


//functions implementation

void show_help() {
  printf("copy - Program which copies one file to another\n");
  printf("\n");
  printf("Usage:\n");
  printf("copy [-m] <file_name> <new_file_name>\n");
  printf("copy [-h]\n");
  printf("\n");
  printf("Arguments:\n");
  printf("-h\thelp\n");
  printf("-m\tcopy mapping files to memory regions with mmap()\n");
  printf("\totherwise read() and write() functions will be used\n");
  printf("\n");
}

