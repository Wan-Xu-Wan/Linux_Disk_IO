#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <sys/time.h>
#include "basics.h"

double gettime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

int main(int argc, char *argv[]) {

    int fd; 
    double start_time, end_time, time_used;
    double file_size;
    double raw_performance;


    if (argc != 3) {
        printf("%s\n", "Usage: ./lseek <filename> <num of sys call>");
        exit(1);
    }
    
    char *filename = argv[1];

    unsigned long int lcount= strtoul(argv[2],NULL, 10);
    unsigned int count  = lcount;
    unsigned int i = 0;

    start_time = gettime();
    if ((fd = open(filename, O_RDONLY)) < 0) {
            printf("Unable to open the file.\n");
            exit(1);
        }  else {
            printf("Successfully opened the file! -------\n");
        }
    while (i <  count) {
        lseek(fd, 1, SEEK_CUR);
        i++;
    }
    close(fd);
    end_time = gettime();
    time_used = end_time - start_time;
    printf("The time used to perform the operation is %f seconds\n", time_used);
    return 0;
}
