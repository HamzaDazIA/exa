#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>

//you can comment that when compilation the server 
//a.k.a "moulinette" use the flag -D BUFFER_SIZE=xx
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif
