#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string.h>

#include "variables.h"
#include "load_b_lut.h"

using namespace std;

void load_b_lut(vector<vector<double> > *B_LUT, char const *file_name) {
    string s;
    ifstream f(file_name);
    size_t offset = 0;

    int i = 1, j = 0;
    int load_iter = 0;
    vector<double> *B = new vector<double>(3);

    getline(f, s); // pass the first line

    while (getline(f, s)) {
        istringstream iss(s);
        while (getline(iss, s, ',')) {
            char *cstr = new char[s.length() + 1];
            strcpy(cstr, s.c_str());
            B->push_back(atof(cstr));
            if (i == 3) {
                (*B_LUT)[j] = *B;
                B->clear();
                i = 0;
                j++;
            }
            i++;
            delete [] cstr;
        }
        load_iter++;
        if (load_iter == TOTAL_RESOL) break;
    }

    delete B;
    f.close();
}

void load_b_luts() {
    load_b_lut(B_LUT1, "./data/B_LUT1.csv");
    load_b_lut(B_LUT2, "./data/B_LUT2.csv");
    load_b_lut(B_LUT3, "./data/B_LUT3.csv");
    load_b_lut(B_LUT4, "./data/B_LUT4.csv");
    load_b_lut(B_LUT5, "./data/B_LUT5.csv");
    load_b_lut(B_LUT6, "./data/B_LUT6.csv");
    load_b_lut(B_LUT7, "./data/B_LUT7.csv");
    load_b_lut(B_LUT8, "./data/B_LUT8.csv");
    printf("B LUTs are loaded\n");
}
