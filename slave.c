#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "i2c.c"

// address of this device
byte addr[] = {1,1,0,0,1,1,0};

byte input_addr[bussize];
char data_length[bussize];
byte dlength = 0;
char* data_char;
byte* data;

byte correct = 0;

int idx = 0;
int phases = 5;
byte phase[5];
byte rw = 0;

byte writeloc = 0;

byte addr_feedback = 1;

void reset(){
    idx = 0;
    for(int i = 0; i<phases; i++){
        phase[i] = 0;
    }
    phase[0] = 1;
    correct = 0;
    for(int i = 0; i<bussize; i++){
        input_addr[i] = 0;
        data_length[i] = 0;
    }
    for(int i = 0; i<dlength; i++){
        data_char[i] = 0;
        data[i] = 0;
    }
    dlength = 0;
}

byte checkaddr(){
    //check if bits match
    printf("%s\n", input_addr);
    printf("%s\n", addr);
    int tidx = 0;
    for(int i = 0; i<sizeof(addr)/sizeof(addr[0]); i++){
        // printf("%u", addr[i]);
        if((byte)addr[i]!=(byte)input_addr[tidx]){
            return 0;
        }
        ++tidx;
    }
    return 1;
}

byte getrw(){
    return sda[window-1];
}

void nextphase(int idx){
    phase[idx] = 0;
    if(idx+1<bussize){
        ++idx;
        phase[idx] = 1;
    }
}

void parse(char bit){
    if(1){
        // printf("got here\n");
        if(phase[0]){
            printf("in here\n");
            input_addr[idx] = (byte)(bit-'0');
            ++idx;
            if(idx>=bussize){
                nextphase(0);
                idx = 0;
                correct = checkaddr();
                if(!correct){
                    printf("Wrong address\n");
                    addr_feedback = 0;
                    return;
                }
                printf("Address matched\n");
            }
        }
        else if(phase[1]){
            rw = getrw();
            nextphase(1);
        }
        else if(phase[2]){
            data_length[idx] = bit;
            ++idx;
            if(idx>=bussize){
                idx = 0;
                dlength = convert(data_length);
                data_char = (char*)realloc(data, dlength*sizeof(char));
                nextphase(2);
            }
        }
        else if(phase[3]){
            data_char[idx] = bit;
            ++idx;
            if(idx>=bussize){
                idx = 0;
                data = convert(data_char);
                if(rw){
                    printf("%s %d\n", "Read", mem[(byte)data]);
                }
                else{
                    mem[writeloc] = data;
                    printf("%s %d\n", "Written into", (int)writeloc);
                }
                nextphase(3);
            }
        }
        else if(phase[4]){
            if(stopcond()){
                return;
            }
            else{
                printf("Failed to stop\n");
            }
        }
    }
    
}