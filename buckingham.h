#ifndef BUCKINGHAM_H
#define BUCKINGHAM_H
#include <string>
#include <potential.h>
#include <math.h>
using namespace std;
class buckingham:public potential
{
public:
    buckingham(buckingham &obj);
    buckingham(string n1, string n2, string st, string f, double a, double r, double c);
    buckingham(string n1, string n2, string st, string uni,string disuni, string f, double a, double r, double c);
    double const & getA () {return A;}
    double const & getRho () {return rho;}
    double const & getC () {return C;}
    void print(ofstream &out);
    virtual void printTerminal();
    virtual buckingham * clone() {return new buckingham(*this);}


private:
    double A;
    double rho;
    double C;

};

#endif // BUCKINGHAM_H
