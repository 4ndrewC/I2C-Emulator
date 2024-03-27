#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"
#include "extraneous.c"

typedef uint8_t byte;

byte mtflag = 0;

byte mem[memsize];

byte sda[window];
byte scl[window];

byte readflag = 0;

void nextbit_sda(byte next){
    for(int i = 1; i<window; i++){
        sda[i-1] = sda[i];
    }
    sda[window-1] = next;
}

void nextbit_scl(byte next){
    for(int i = 1; i<window; i++){
        scl[i-1] = scl[i];
    }
    scl[window-1] = next;
}

byte startcond(){
    // check most recent bit
    byte dline = sda[window-1];
    byte cline = scl[window-1];

    if(!dline && cline) return 1;
    return 0;
}

byte stopcond(){
    byte dline_end = sda[window-2];
    byte dline_end1 = sda[window-1];
    byte cline = scl[window-1];

    if(dline_end1-dline_end && cline) return 1;
    return 0;
}

void sendack(){
    // default to always acknowledge
    nextbit_sda(0);
}

void writemem(int datasize, char* data, char* addr_string){
    int addr = atoi(addr_string);
    byte inputval = convert(data);
    mem[addr] = inputval;
    printf("%s %s %s %d", "Written ", data, " into address ", addr);
}

char* readmem(int datasize, char* addr_string){
    int addr = atoi(addr_string);
    //convert binary to string
    char* ret = rconvert(mem[addr]);
    return ret;
}
