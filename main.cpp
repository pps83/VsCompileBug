#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint32_t xmul(uint32_t a, uint32_t b);
const char expected[] = "multiply(2197175160 x 1856165212) = 2791835115\n";

int main()
{
    uint32_t x = 2197175160, y = 1856165212;
    uint32_t z = xmul(x, y);

    char buf[1024];
    snprintf(buf, 1000, "multiply(%u x %u) = %u\n", x, y, z);
    if (strcmp(buf, expected) != 0)
        printf("ERORR result:\n%sExpected:\n%s", buf, expected);
    else
        puts(buf);
}
