#ifndef CVFF_IMPROPER_H
#define CVFF_IMPROPER_H
#include "harmonic_angle.h"

class cvff_improper : public harmonic_angle
{
public:
    cvff_improper(string n1, string n2, string n3, string n4, double k, double ind, double n, string uni, string f);
    double getD(){return d;}
    void print(ofstream &out);

private:
    double d;
};

#endif // CVFF_IMPROPER_H
