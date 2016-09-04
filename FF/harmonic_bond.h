#ifndef HARMONIC_BOND_H
#define HARMONIC_BOND_H
#include "potential.h"
class harmonic_bond:public potential
{
public:
    harmonic_bond(string n1,string n2,double k,double r,string uni,string f);
    harmonic_bond(string n1,string n2,double k,double r,string uni,string f,string s);
    harmonic_bond(int i,string n1,string n2,double k,double r,string uni,string f);
    harmonic_bond(string n1,string n2,double k,string uni,string f);
    harmonic_bond(string n1,string n2,string uni,string f);
    double getK(){return K;}
    double getReq(){return req;}
    double getDistParam(){return req;}
    void print(ofstream &out);
    void printHOOMD(ofstream &out,double e, double d);
    void printTerminal();
    void printLatex(ofstream & out, double e);

protected:
    double K;
    double req;

};

#endif // HARMONIC_BOND_H
