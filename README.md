# Linux_Disk_IO

## Brief description
This project is to evaluate the efficiency of Linux disk I/O, the effects of caches and the cost of system calls.
## How to run
Compile the code: bash build.sh

Disk I/O read and write: ./run <filename> [-r|-w] <block_size> <block_count>

Find "reasonable" file size to be read in 5-15 seconds: ./run2 <filename> <block_size>

Read a file as fast as possible: ./fast <file_to_read>

## Raw performance - different block sizes withc cache
![image](https://user-images.githubusercontent.com/91846138/208181658-ffe55f6e-ddeb-4795-81f7-b23ac4a44e5f.png)

From the graph above we can tell that, when the block size is relatively small, from 256 to 65,536 bytes, the performance is increasing at a rapid speed per block size increase. Then the slope becomes flatter when the block size increases from 65,536 to 134,217,728 bytes. Starting from 268,435,456 bytes, we can see the performance start to drop.

## Cache v.s. non cache
![image](https://user-images.githubusercontent.com/91846138/208181804-c95cf471-2294-423f-b8c8-b7ecc3a2bec7.png)

From the graph, we can tell that when the block size is relatively small, from 256 to 65,536 bytes, the difference between the performance with and without caching is not so obvious. When the block size becomes larger, from 131,082 bytes, we can see the gap between caching and non caching become greater and greater. When the block size reaches 134,217,728 and larger, the gap tends to stop growing or even become a little narrower.

## Cost of system calls
![image](https://user-images.githubusercontent.com/91846138/208182086-f0219016-54d4-4b01-8772-aee1a5ac7c02.png)

The graph above is the performance in Mib/sec for read system call only. We can see that after the number of system calls reached 131,072, the performance in Mib/sec started to drop.

![image](https://user-images.githubusercontent.com/91846138/208182264-c4a64b63-71e2-4df7-b8fc-ad201921250e.png)

From the graph above, we can see that read system call is much less efficient than lseek system call.
