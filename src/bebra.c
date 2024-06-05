#include "stdio.h"
#include "hse_decimal.h"

int main () {
    hse_decimal value_1 = {{123457u, 654u, 0xFFFFFFFF, 0}};
    hse_decimal value_2 = {{123456u, 654u, 0xFFFFFFFF, 0}};
    int return_value = hse_is_greater(value_1, value_2);
    printf("%d", return_value);

    return 0;
}