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
    double file_size_min;

    if (argc != 3) {
        printf("Usage: ./run2 <filename> <block_size>\n");
        exit(1);
    }
    
    char *filename = argv[1];

    if(argv[2][0] == '-' ) {
        printf("%s\n", "Error! Block_size is negative");
        exit(1);
    }
    unsigned long int lblock_size = strtoul(argv[2],NULL, 10);
    unsigned int block_size = lblock_size;
    unsigned int block_count = 1;

    
    if (block_size == 0 )
    {
    	printf("%s\n", "Block_size can't be zero");
        exit(1);
    }

    while (1) {
        start_time = gettime();
        if ((fd = open(filename, O_RDONLY)) < 0) {
            printf("Unable to open the file.\n");
            exit(1);
        } else {
            printf("Successfully opened the file! -------\n");
            file_size= (double)basic_read(fd, block_size, block_count);
        }
        close(fd);
        end_time = gettime();
        time_used = end_time - start_time;
        file_size_min = (double) block_size * block_count;

        printf("The time used to perform the operation is %f seconds\n", time_used);
        printf("The block count is %u.\n", block_count);
        printf("The file size is %.0f bytes.\n", file_size);
        raw_performance = (file_size/1048576)/time_used;
        printf("Raw performance is %.6f MiB/s.\n", raw_performance);
   
        if (time_used > 5 && time_used >15 ) {
            //in case exceed 15 seconds
            printf("Exceed 15 seconds!\n");
            break;
        } else if (time_used > 5) break;
        else if ( file_size < file_size_min) {
            printf("The file is too small to be read between 5 and 15 seconds. Select another file!\n");
            break;
        }
        else {
            block_count *= 2;
        }
    }
    return 0;
}
