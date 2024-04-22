#include <stdint.h>
#include <stdio.h>

uint32_t xmul(uint32_t a, uint32_t b);

int main()
{
    uint32_t x = 2197175160, y = 1856165212;
    uint32_t z = xmul(x, y);
    printf("multiply(%u x %u) = %u\n", x, y, z);
}
