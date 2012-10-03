#include <ios>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <boost/assign/std/vector.hpp>
#include "global.h"
#include "vecop.h"
#include "savevtk.h"

using namespace boost::assign;
using namespace std;

#define ANG_RES 600 // angular resolution in arcsec
#define FREQ_RES 7.0e-4 // 700 freq resolution
#define SKY_SIZE 10 // 10 deg sky
#define GMU 1.0e-6 // Gmu factor
#define PI 3.14159265359 // pi

int main()
{
    // Create an empty 3D vector
    vector<vector<vector<double> > > skyBox;
    const vecsize windowsize = SKY_SIZE * 3600 / ANG_RES;

    double z_1 = 10;
    double z_2 = 20;
    double delta_z = FREQ_RES / 60; // detection at 60MHz

    vecsize z_size;
    z_size = (z_2 - z_1) / delta_z / 10000; // Smooth out z by a factor of 10000

    skyBox.resize(windowsize);
    for (vecsize i = 0; i < windowsize; ++i) {
        skyBox[i].resize(windowsize);

    for (vecsize j = 0; j < windowsize; ++j) 
        skyBox[i][j].resize(z_size);
        }

    // Put zeroes in it
    for (vecsize i = 0; i < windowsize; ++i) {
        for (vecsize j = 0; j < windowsize; j++) {
            for (vecsize k = 0; k < z_size; k++)
                skyBox[i][j][k] = 0;
        }
    }

    vec pos_test;
    vec ori_test;
    pos_test.x = windowsize / 2;
    pos_test.y = windowsize / 2;
    pos_test.z = z_size / 3;
    ori_test.x = 1;
    ori_test.y = 0;
    ori_test.z = 0;

    for(int i=0; i<6; i++)
    {
    placeString(pos_test, ori_test, 1000.0, 15.0, 0.0, 0.57735, windowsize, z_size, skyBox);
    ori_test = rotate_xy(PI/6, ori_test);
    }

//    cout << skyBox.size() << "x" << skyBox[0].size() << "x" <<  skyBox[0][0].size() << endl;
/*    for (vecsize i = 0; i < windowsize; ++i)
        for (vecsize j = 0; j < windowsize; ++j)
            for (vecsize k = 0; k < z_size; ++k)
            {
                cout << i << "," << j << "," << k << "," << skyBox[i][j][k] << endl;
            }
*/

    savevtk(windowsize, windowsize, z_size, skyBox);
    
    return 0;
}


/* Confusing z in vec.z (can represent z-direction in R^3 or redshift direction) */
void placeString(const vec& position, const vec& orientation, double z_i, double z, double t_i, double vsgs,
const vecsize& windowsize, const vecsize& z_size, vector<vector<vector<double> > >& skyBox)
{
//    double length = t_i;
//    double width = t_i * vsgs;
//    double thickness = t_i * 4 * PI * GMU * vsgs;
   
   vec string_par = orientation;
/* This should be randomized in a direction perpendicular to string_par */

    vec string_perp;

/* temporary, string_perp needs to be random */
    string_perp = rotate_xy(PI/2, string_par);

    vec string_thick = cross(string_par, string_perp);

    string_par = normalize(string_par);
    string_perp = normalize(string_perp);
    string_thick = normalize(string_thick);

    double theta_par = 1 / sqrt(z_i + 1) * 90 * 3600 / ANG_RES;
    double theta_perp = 1 / sqrt(z_i + 1) * vsgs * 90 * 3600 / ANG_RES;
    double thickness_z = ceil(8 / 3 * PI *GMU * vsgs * sqrt(z_i + 1) * pow (1 + z, -1.5) * 86 / 10);

    string_par = multiply(theta_par, string_par);
    string_perp = multiply(theta_perp, string_perp);
    string_thick = multiply(thickness_z, string_thick);

    string_par = project_angular(string_par);
    string_perp = project_angular(string_perp);
    string_thick = project_z(string_thick);

    vec ihat;
    ihat.x = 1;
    ihat.y = 0;
    ihat.z = 0;

    double axis_angle = acos(dot(ihat,string_par) / norm(ihat) / norm(string_par));
    double rot_x;
    double rot_y;
    double norm_par = norm(string_par);
    double norm_perp = norm(string_perp);
    double norm_z = norm(string_thick);

    for (vecsize i = 0; i < windowsize; ++i)
        for (vecsize j = 0; j < windowsize; ++j)
            for (vecsize k = 0; k < z_size; ++k)
            {
                rot_x = i * cos(axis_angle) - j * sin(axis_angle);
                rot_y = i * sin(axis_angle) + j * cos(axis_angle);
                if ((rot_x >= position.x) && (rot_x <= position.x + norm_par) &&
                    (rot_y >= position.y) && (rot_y <= position.y + norm_perp) &&
                    (k >= position.z) && (k <= position.z + norm_z))

                    skyBox[i][j][k] += brightnessTemp(1.9e-7 * pow((1 + z), 3), 2.7e-11, 2.85e-15, 0.068, 2.7315,
                    1000.0, 15.0, 0.57735);
            }

//    cout << theta_l << "x" << theta_w << "x" << thickness_z << endl;
}

double brightnessTemp(double n_bg, double k_HH_10, double A_10, double T_star, double T_g,double z_i, double z, double
vsgs)
{
    double T_g_z = T_g * (1 + z);
    double T_K = 20 * (GMU * 1e6) * (GMU * 1e6) * vsgs * vsgs * (1 + z_i) / (1 + z);
    double n = 4 * n_bg;
    double x_c = n * k_HH_10 / A_10 * T_star / T_g_z;
    double T_b = 0.07 * x_c / (1 + x_c) * (1 - T_g_z/T_K) * sqrt(1 + z);

    return T_b;
}
