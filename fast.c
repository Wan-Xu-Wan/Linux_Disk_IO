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
    

    if (argc != 2) {
        printf("Usage: ./fast <file_to_read>\n");
        exit(1);
    }
    
    char *filename = argv[1];

    unsigned int block_size = 1048576;
    unsigned int xor_value = 0;
    unsigned int file_size = 0;
    unsigned int read_size =0;

    if ((fd = open(filename, O_RDONLY)) < 0) {
        printf("%s\n", "Unable to open the file.");
        exit(1);
    } else {
        printf("Successfully opened the file.\n");
    }

    unsigned int *buffer = (unsigned int*)malloc((block_size / 4) * sizeof(unsigned int));
    start_time = gettime();

    while ((read_size = read(fd, buffer, block_size)) > 0 ) {
        file_size += read_size;
        if (read_size >= 4) {
            xor_value ^= xorbuf(buffer, read_size / 4);
        } else {
            xor_value ^= xorbuf(buffer, 1);
        }
    }
    close(fd);
    end_time = gettime();
    time_used = end_time - start_time;
    printf("The time used to perform the operation is %f seconds\n", time_used);
    printf("The xor value is %08x.\n", xor_value);
    printf("The block size is %u. \n", block_size);

    return 0;
}
