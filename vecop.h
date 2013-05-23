#ifndef VECTORS_H
#define VECTORS_H

#include <iostream>

typedef struct vec {
    double x,y,z;
} vec;

vec add(vec, vec);
double norm(vec);
double dot(vec, vec);
vec cross(vec, vec);
vec normalize (vec);
vec project_angular (vec);
vec project_z (vec);
vec multiply (double, vec);
vec rotate_xy (double, vec, vec);

#endif
