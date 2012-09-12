#ifndef GLOBAL_H
#define GLOBAL_H
#include "vecop.h"

typedef std::vector<std::vector<std::vector<double> > >::size_type vecsize;

void placeString(const vec&, vec&, double, double, double, double,
const vecsize&, const vecsize&, std::vector<std::vector<std::vector<double> > >&);

double brightnessTemp(double, double, double, double, double, double, double, double);

#endif
