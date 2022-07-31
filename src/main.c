#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack.h"

char* mem;
int memsize;
FILE* srcfile;

int init(){
    memsize=30000;
    mem = (char*)malloc(memsize);
    if (mem == NULL){
        return -1;
    }
    else{
        memset(mem, 0, memsize);
    }

    if (init_stack()){
        return 1;
    }

    srcfile = fopen("file.bf", "r");
    if (srcfile == NULL){
        return -1;
    }

    return 0;
}

int main(int argc, char* argv[]){
    if (init()){
        printf("ERROR %d\n", errno);
        return -1;
    }

    int ptr=0, i=0, end_loop=0;
    unsigned char c;
    while ((c=fgetc(srcfile)) != (unsigned char)EOF){
        // printf("mem[%d] = %d, c = %d\n", ptr, mem[ptr], c);
        switch (c){
            case 44: // ,
                if (!end_loop){
                    mem[ptr] = fgetc(stdin);
                }
                break;
            case 46: // .
                if (!end_loop){
                    printf("%c", mem[ptr]);
                    fflush(stdout);
                }
                break;
            case 43: // +
                if (!end_loop){
                    mem[ptr] ++;
                }
                break;
            case 45: // -
                if (!end_loop){
                    mem[ptr] --;
                }
                break;
            case 60: // <
                if (!end_loop){
                    ptr = (ptr-1)%memsize;
                }
                break;
            case 62: // >
                if (!end_loop){
                    ptr = (ptr+1)%memsize;
                }
                break;
            case 91: // [
                if (mem[ptr]){
                    push(ftell(srcfile));
                }
                else{
                    end_loop = 1;
                }
                break;
            case 93: // ]
                if (end_loop){
                    end_loop = 0;
                }
                else{
                    fseek(srcfile, pop()-1, SEEK_SET);
                }
                break;
            default:
                break;
        }
        i++;
    }
    fclose(srcfile);

    return 0;
}