#ifndef HARMONIC_ANGLE_H
#define HARMONIC_ANGLE_H
#include "harmonic_bond.h"
class harmonic_angle : public harmonic_bond
{
public:
    harmonic_angle(string n1, string n2, string n3, string uni, string f);
    harmonic_angle(int i,string n1, string n2, string n3, double k, double a, string uni, string f);
    harmonic_angle(string n1, string n2, string n3, double k, double a, string uni, string f);
    void print(ofstream &out);
    void printTerminal();
    double getAngle(){return angle;}
    void printHOOMD(ofstream &out,double e, double d);
    virtual double getDistParam(){return angle;}
private:
    double angle;
};

#endif // HARMONIC_ANGLE_H
