#include <iostream>
#include <vector>
#include "global.h"

using namespace std;

void savevtk(const vecsize& x_size, const vecsize& y_size, const vecsize& z_size, const vector<vector<vector<double> > > array)
{
    cout << "# vtk DataFile Version 2.0" << endl;
    cout << "Comment goes here" << endl;
    cout << "ASCII" << endl << endl;

    cout << "DATASET STRUCTURED_POINTS" << endl;
    cout << "DIMENSIONS    " << x_size << "    " << y_size << "    " << z_size << endl << endl;

    cout << "ORIGIN    " << "0.000" << "    " << "0.000" << "    " << "0.000" << endl;
    cout << "SPACING    " << "1.000" << "    " << "1.000" << "    " << "1.000" << endl << endl;

    cout << "POINT_DATA    " << x_size * y_size * z_size << endl;
    cout << "SCALARS scalars float" << endl;
    cout << "LOOKUP_TABLE default" << endl << endl;
 
    for (vecsize k = 0; k < z_size; ++k)
        for (vecsize i = 0; i < x_size; ++i)
        {
            for (vecsize j = 0; j < y_size; ++j)
            {
                cout << array[i][j][k] << " ";
            }
            cout << endl;
        }
}
