#ifndef OPLS_DIHEDRAL_H
#define OPLS_DIHEDRAL_H
#include "harmonic_dihedral.h"
class opls_dihedral : public harmonic_dihedral
{
public:
    opls_dihedral(string n1, string n2, string n3, string n4, double k1, double k2, double k3, double k4, string uni, string f);
    void print(ofstream &out);

private:
    double K1,K2,K3,K4;
};

#endif // OPLS_DIHEDRAL_H
