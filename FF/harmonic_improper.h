#ifndef HARMONIC_IMPROPER_H
#define HARMONIC_IMPROPER_H
#include "harmonic_angle.h"

class harmonic_improper : public harmonic_angle
{
public:
    harmonic_improper(string n1, string n2, string n3, string n4, double k, double n, string uni, string f);
    harmonic_improper(int i, string n1, string n2, string n3, string n4, double k, double n, string uni, string f);
    void print(ofstream &out);
    void printHOOMD(ofstream &out, double e, double d);
};

#endif // HARMONIC_IMPROPER_H
