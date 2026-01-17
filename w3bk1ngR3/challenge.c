#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define OP_XOR  0xA1
#define OP_ROL  0xB2
#define OP_ADD  0xC3
#define OP_CMP  0xD4


uint8_t encrypted_vm[] = {
    0xF4, 0xE8, 0xF4, 0x96, 0x85
};


void anti_debug() {
    if (getenv("LD_PRELOAD")) {
        exit(1);
    }
}


void decrypt_vm(uint8_t *vm, size_t len) {
    for (size_t i = 0; i < len; i++) {
        vm[i] ^= (0x55 + i);
    }
}


int vm_execute(uint8_t *input, size_t len) {
    uint8_t acc = 0x42;
    size_t ip = 0;

    while (1) {
        uint8_t op = encrypted_vm[ip++];

        switch (op) {
            case OP_XOR:
                acc ^= input[ip % len];
                break;

            case OP_ROL:
                acc = (acc << 1) | (acc >> 7);
                break;

            case OP_ADD:
                acc += input[(ip * 3) % len];
                break;

            case OP_CMP:
                return acc == 0x7A;

            default:
                return 0;
        }
    }
}

int main() {
    anti_debug();

    uint8_t input[64];

    puts("Enter key:");
    fgets((char *)input, sizeof(input), stdin);
    input[strcspn((char *)input, "\n")] = 0;

    size_t len = strlen((char *)input);


    if (len != 29) {
        puts("Wrong!");
        return 1;
    }

    decrypt_vm(encrypted_vm, sizeof(encrypted_vm));

    if (vm_execute(input, len)) {
        puts("Correct!");
    } else {
        puts("Wrong!");
    }

    return 0;
}
