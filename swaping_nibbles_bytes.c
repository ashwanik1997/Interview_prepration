// Online C compiler to run C program online
#include <stdio.h>
#include <stdint.h>

uint32_t nibbleSwap(uint32_t data) 
{
    uint32_t output = 0;
    while(data > 0) {
        output = output << 4 | (data & 0xf);
        data = data >> 4;
    }
    return output;
	}
}

uint32_t byteSwap(uint32_t data)
{
    uint32_t output = 0;
    while(data > 0) {
        output = output << 8 | (data & 0xff);
        data = data >> 8;
    }
    return output;
}

int main() {
    // Write C code here
    printf("Try programiz.pro\n");
    uint32_t data = 0x12345678;
    
    printf("\nnbyteSwap = 0x%8x",byteSwap(data));
    printf("\nnibbleSwap = 0x%8x",nibbleSwap(data));
    return 0;
}
