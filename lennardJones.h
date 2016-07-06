#ifndef LENNARDJONES_H
#define LENNARDJONES_H
#include "potential.h"
class lennardJones: public potential
{
public:
    lennardJones(){;}
    lennardJones(lennardJones &obj);
    lennardJones(string n1, string n2, string st, string f, double eps, double sig);
    lennardJones(string n1, string n2, string st, string uni,string disuni, string f, double eps, double sig);
    lennardJones(int i1, int i2, bool ii, string n1, string n2);
    double const & getEpsilon () {return epsilon;}
    double const & getSigma () {return sigma;}
    void print(ofstream &out);
    virtual void printTerminal();
    virtual lennardJones * clone() {return new lennardJones(*this);}

private:
    double epsilon;
    double sigma;

};

#endif // LENNARDJONES_H
