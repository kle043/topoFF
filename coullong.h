#ifndef COULLONG_H
#define COULLONG_H
#include "potential.h"
class coulLong : public potential
{
public:
    coulLong(coulLong & obj);
    coulLong(int i1, int i2, bool ii, string n1, string n2);
    virtual void print(ofstream & out);
    virtual void printTerminal();
    virtual coulLong * clone() {return new coulLong(*this);}
};

#endif // COULLONG_H
