#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int token;
char *src, *old_src;
int poolsize;
int line;

int *text, *old_text, *stack;
char *data;

char *data;

int *pc, *bp, *sp, ax, cycle;

enum { LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
    OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, MOD,
    OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT};

void next() {
    token = *src++;
    return;
}

void expression() {
    //do nothing
}

void program() {
    next();
    while (token > 0){
        printf("token is: %c\n", token);
        next();
    }
}

int eval() {
    int op, *tmp;

    while(1) {
        if (op == IMM)  {ax = *pc++;}
        else if (op == LC) {ax = *(char *)ax;}
        else if (op == LI) {ax = *(int *)ax;}
        else if (op == SC) {ax = *(char *)*sp++ = ax;}
        else if (op == SI) {*(int *)*sp++ = ax;}
    }

    return 0;
}


int main(int argc, char **argv) {
    int i, fd;

    argc--;
    argv++;


    poolsize = 256 * 1024;
    line = 1;

    if ((fd = open(*argv, 0)) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }


    if (!(src = old_src = malloc(poolsize))) {
        printf("read() return %d\n", i);
        return -1;
    }

    if ((i = read(fd, src, poolsize-1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    
    // allocate memory for virtual machine
    if (!(text = old_text = malloc(poolsize))) {
        printf("read() return %d\n", i);
        return -1;
    }

    if (!(data = malloc(poolsize))) {
        printf("read() return %d\n", i);
        return -1;
    }

    if (!(stack = malloc(poolsize))) {
        printf("read() return %d\n", i);
        return -1;
    }

    memset(text, 0, poolsize);
    memset(data, 0, poolsize);
    memset(stack, 0, poolsize);

    bp = sp = (int *)((int)stack + poolsize);
    ax = 0;

    src[i] = 0;
    close(fd);

    program();
    return eval();
}
