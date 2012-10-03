#include <cmath>
#include "vecop.h"

using namespace std;

vec add(vec a, vec b)
{
    vec out;

    out.x = a.x + b.x;
    out.y = a.y + b.x;
    out.z = a.z + b.z;

    return out;
}

double norm(vec in)
{
    double result = sqrt(in.x * in.x + in.y * in.y + in.z * in.z);

    return result;
}

double dot(vec a, vec b)
{
    double result;

    result = a.x * b.x + a.y * b.y + a.z * b.z;

    return result;
}

vec cross(vec a, vec b)
{
    vec out;

    out.x = a.y * b.z - a.z * b.y;
    out.y = a.z * b.x - a.x * b.z;
    out.z = a.x * b.y - a.y * b.x;

    return out;
}

vec normalize(vec in)
{
    vec out;
    double norm_vec = norm(in);

    out.x = in.x / norm_vec;
    out.y = in.y / norm_vec;
    out.z = in.z / norm_vec;

    return out;
}

vec project_angular(vec in)
{
    vec out;
    
    out.x = in.x;
    out.y = in.y;
    out.z = 0;

    return out;
}

vec project_z(vec in)
{
    vec out;

    out.x = 0;
    out.y = 0;
    out.z = in.z;

    return out;
}

vec multiply(double a, vec in)
{
    vec out;

    out.x = in.x * a;
    out.y = in.y * a;
    out.z = in.z * a;

    return out;
}

vec rotate_xy(double theta, vec in)
{
    vec out;

    out.x = in.x * cos(theta) - in.y * sin(theta);
    out.y = in.x * sin(theta) + in.y * cos(theta);
    out.z = in.z;

    return out;
}
