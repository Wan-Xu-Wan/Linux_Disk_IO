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


    if (argc != 5) {
        printf("%s\n", "Usage: ./run <filename> [-r|-w] <block_size> <block_count>");
        exit(1);
    }
    
    char *filename = argv[1];

    if(argv[3][0] == '-' || argv[4][0] == '-') {
        printf("%s\n", "Error! Block_size or block_count is negative");
        exit(1);
    }
    unsigned long int lblock_size = strtoul(argv[3],NULL, 10);
    unsigned long int lblock_count = strtoul(argv[4],NULL, 10);
    unsigned int block_size = lblock_size;
    unsigned int block_count = lblock_count;
    
    if (block_size == 0 || block_count == 0)
    {
    	printf("%s\n", "Block_size or block_count can't be zero");
        exit(1);
    }

    
    start_time = gettime();
    
    if ((strcmp(argv[2], "-r") == 0)) {
        
        if ((fd = open(filename, O_RDONLY)) < 0) {
            printf("%s\n", "Unable to open the file.");
            exit(1);
        } else {
            printf("Successfully opened the file.\n");
            file_size= (double)basic_read(fd, block_size, block_count);
        }
        
    } else if ((strcmp(argv[2], "-w") == 0)) {

        if ((fd = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXU)) < 0) {
            printf("%s\n", "Unable to open the file.");
            exit(1);
        } else {
            printf("Successfully opened the file.\n");
            file_size = (double) basic_write(fd, block_size, block_count);
        }
       
    } else {
        printf("%s\n", "Usage: ./run <filename> [-r|-w] <block_size> <block_count>");
        exit(1);
    }
    close(fd);

    end_time = gettime();
    time_used = end_time - start_time;

    printf("The time used to perform the operation is %f seconds\n", time_used);


    raw_performance = (file_size/1048576)/time_used;
    printf("The file size is %.0f bytes.\n", file_size);
    printf("Raw performance is %.6f MiB/s.\n", raw_performance);

    return 0;
}
