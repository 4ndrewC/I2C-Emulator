#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t byte;

byte convert(char *str) {
    char *endptr;
    long int result = strtol(str, &endptr, 2);
    if (endptr == str || *endptr != '\0') {
        return -1; 
    }
    return (byte)result;
}

void rconvert(int num, char *binary_str) {
  int i = 0;
  if (num < 0) {
    num = (num << 1) + 1;
  }
  while (num > 0) {
    binary_str[i++] = (num & 1) ? '1' : '0';
    num >>= 1;
  }
  binary_str[i] = '\0';

  for (int j = 0; j < i / 2; j++) {
    char temp = binary_str[j];
    binary_str[j] = binary_str[i - j - 1];
    binary_str[i - j - 1] = temp;
  }
}
