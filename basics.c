#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <sys/time.h>
#include "basics.h"

unsigned int xorbuf(unsigned int *buffer, int size) {
    unsigned int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= buffer[i];
    }
    return result;
}

unsigned int basic_read(int fd, unsigned int block_size, unsigned int block_count) {

    unsigned int *buffer;
    unsigned int read_size =0;
    unsigned int count = 0;
    unsigned int xor_value = 0;
    unsigned int file_size = 0;

    // check if block_size is a multiple of 4 bytes
    if(block_size % 4 == 0) {
        buffer = (unsigned int*)malloc((block_size / 4) * sizeof(unsigned int));
    } else {
        buffer = (unsigned int*)malloc((block_size / 4 + 1) * sizeof(unsigned int));
    }

    while ((read_size = read(fd, buffer, block_size)) > 0 && count < block_count) {
        count++;
        file_size +=  read_size;
        if (read_size >= 4) {
            
            xor_value ^= xorbuf(buffer, read_size / 4);
        } else {
            
            xor_value ^= xorbuf(buffer, 1);
        }
    }

    printf("The xor value is %08x.\n", xor_value);
    return file_size;
}

unsigned int basic_write(int fd, unsigned int block_size, unsigned int block_count) {


    unsigned int file_size = 0;
    unsigned int write_size = 0;

    //create buffer to write from
    // char is 1 byte so allocate block_size * 1 byte of memory
    char *buffer = (char *)malloc(block_size * sizeof(char));
    for (int i = 0; i < block_size; i++) {
        buffer[i] = 'x';
    }
    
    for (int i = 0; i < block_count; i++) {
        if((write_size= write(fd, buffer, (size_t) block_size)) > 0) {
            file_size += write_size;
        } else break;
    }
    return file_size;
}
