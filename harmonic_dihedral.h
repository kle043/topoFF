#ifndef HARMONIC_DIHEDRAL_H
#define HARMONIC_DIHEDRAL_H
#include "harmonic_angle.h"
class harmonic_dihedral : public harmonic_angle
{
public:
    harmonic_dihedral(string n1, string n2, string n3, string n4, string uni, string f);
    harmonic_dihedral(int i, string n1, string n2, string n3, string n4, double k, double ind, double n, string uni, string f);
    harmonic_dihedral(string n1, string n2, string n3, string n4, double k, double ind, double n, string uni, string f);
    void print(ofstream &out);
    double getD(){return d;}

private:
    double d;

};

#endif // HARMONIC_DIHEDRAL_H
