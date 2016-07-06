#ifndef CCOORDINATES_H
#define CCOORDINATES_H
#include <iostream>
using namespace std;

class ccoordinates
{
public:
    ccoordinates(){;}
    ccoordinates(double & ix, double & iy, double & iz);
    void setCoordinates(double & ix, double & iy, double & iz);
    double & getX(){return x;}
    double & getY(){return y;}
    double & getZ(){return z;}
    double & getPos(string d);
    ccoordinates operator () (double  ix, double  iy, double  iz);
    ccoordinates operator+(ccoordinates &coord1);
    ccoordinates operator/(double & n);
    ccoordinates cross(ccoordinates &coord1);
    double operator*(ccoordinates &coord1);
    ccoordinates operator*(double & n);
    ccoordinates operator-(ccoordinates &coord1);
    void printCoordinates();

private:
    double x,y,z;


};

#endif // CCOORDINATES_H
