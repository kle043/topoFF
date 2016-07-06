#ifndef MORSE_BOND_H
#define MORSE_BOND_H
#include "harmonic_bond.h"
class morse_bond : public harmonic_bond
{
public:
    morse_bond(string n1, string n2, double k, double r, string uni, string f, double a);
    morse_bond(int i,string n1,string n2,double k,double r,string uni,string f);
    morse_bond(string n1,string n2,double k,string uni,string f);
    morse_bond();
    void print(ofstream & out);
    double getAlpha(){return alpha;}

private:
    double alpha;
};

#endif // MORSE_BOND_H
