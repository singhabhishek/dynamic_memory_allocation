# Dynamic Memory Allocation

Our algorithm using sbrk() system call to set program break or brk which defines the end of program’s data segment. We
are using sbrk() because glibc implementation of malloc uses it.

sbrk(0) - gives current address of program break
sbrk(x) - gives positive break by x bytes, thus allocating memory for x bytes
sbrk(-x) - gives negative break by x bytes, thus deallocating memory for x bytes.

The heap memory that OS provides is contiguous. We can only release memory which is at the end of heap, we can’t release
memory from middle. So to facilitate this we are using linked list to maintain the list of free memory available which
is not still released to OS, and release memory only if it is at the end of heap. This free block can be later used by
some other malloc call if size is within the limit. With each block of memory, we are also maintaining size and free/not
free status to help implement free() API and to facilitate reuse of block of memory if it can’t be given back to OS. We
are also providing locking mechanism so that no two threads allocate memory simultaneously. 

## To Build package with glibc version of dynamic memory allocation function
- $ make 

## To Build package with our custom version of dynamic memory allocation function
- $ make CFLAGS=-DCUSTOM_LIB

#### To clean package
- $ make clean

## Example Usage:
 - ./test
 

