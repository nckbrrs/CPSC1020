#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "vector.h"

int main()
{
    vec_t   v1 = {3.0, 4.0, 5.0};
    vec_t   v2 = {4.0, -1.0, 2.0};
    vec_t   v3;
    vec_t   v4;
    vec_t   v5;
    double	v;

    vec_print(stdout, "v1", &v1);
    vec_print(stdout, "v2", &v2);

    vec_diff(&v1, &v2, &v3);
    vec_print(stdout, "v2 - v1 = ", &v3);

    v = vec_dot(&v1, &v2);
    printf("v1 dot v2 is %8.3lf \n", v);

    v = vec_len(&v1);
    printf("Length of v1 is %8.3lf \n", v);

    vec_scale(1 / v, &v1, &v3);
    vec_print(stdout, "v1 scaled by its 1/ length:  ", &v3);

    vec_unit(&v1, &v4);
    vec_print(stdout, "unit vector in v1 direction: ", &v4);

    vec_sum(&v1, &v2, &v5);
    vec_print(stdout, "v1 + v2 = ", &v5);

    printf("\n===Aliased parameter test===\n");
    vec_unit(&v1, &v1);
    vec_print(stdout, "v1 is now its own unit vector:", &v1);

    return(0);
}
