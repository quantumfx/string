#include <stdlib.h>
#include <stdio.h>
#include "vecop.h"

int main ()
{
   vec rotate;
   rotate.x = 9;
   rotate.y = 2;
   rotate.z = 0;

    printf("x: %f, y: %f\n", rotate.x, rotate.y);

   vec origin;
   origin.x = 4; origin.y = 2; origin.z = 0;
   rotate=rotate_xy(3.14159265358979/6, rotate, origin);

    printf("x: %f, y: %f\n", rotate.x, rotate.y);

    vec cross_a;
    cross_a.x = 1;
    cross_a.y = 3;
    cross_a.z = 2;

    vec cross_b;
    cross_b.x = 4;
    cross_b.y = 1;
    cross_b.z = 5;


    printf("a_x: %f, a_y: %f, a_z: %f\nb_x: %f, b_y: %f, b_z: %f\n", cross_a.x, cross_a.y, cross_a.z, cross_b.x, cross_b.y, cross_b.z);

   vec prod = cross(cross_a,cross_b);

    printf("x: %f, y: %f, z: %f\n", prod.x, prod.y, prod.z);

    return 0;
}
