#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "slave.c"

byte tick = 1;

int it = 0;

// protocol:       SM     LRM     LM      LS
char* bitstream = "011001100000001111101011";


void sda_line(char* bitstream, byte tick){
    if(scl[window-1]){
        byte bit = *bitstream-'0';
        nextbit_sda(bit);
        // printf("got hereeee");
        ++bitstream;
    }
    else nextbit_sda(sda[window-1]);
    
}

void scl_line(){
    // printf("%s %d\n", "tick", tick);
    nextbit_scl(tick);
    // printf("%s %d\n", "input into scl", scl[window-1]);
    if(tick) tick = 0;
    else tick = 1;

}

int main(){

    byte start = startcond();
    if(1){
        phase[0] = 1;
        ++bitstream;
        scl_line();
        sda_line(bitstream, tick);
        printf("%s %d\n", "tick", scl[window-1]);
        printf("%s %d\n", "sda", sda[window-1]);
        // for now, set stop condition to *bitstream=='\0'
        while(*bitstream!='\0'){
            scl_line();
            sda_line(bitstream, tick);
            printf("%s %d\n", "tick", scl[window-1]);
            printf("%s %d\n", "sda", sda[window-1]);
            if(scl[window-1]){
                char curbit = *bitstream;
                parse(curbit);
                ++bitstream;
            }
            if(!addr_feedback){
                printf("Address mismatch\n");
                break;
            }
        }
        // show results
        printf("%d\n", rw);
        printf("%d\n", mem[writeloc]);
        // printf("%d", correct);
        // printf("got here");
    }
    return 0;   
}
