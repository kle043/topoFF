#ifndef CMEASURE_H
#define CMEASURE_H
#include "catom.h"
#include <iomanip>
#include <cmath>

#define pi 3.14159265
class cmeasure
{
public:
    cmeasure();
    void setPBC(double x,double y,double z);
    double getBond(cAtom *atom1, cAtom *atom2, int frame);
    double getBondPBC(cAtom *atom1, cAtom *atom2, int frame,double x,double y,double z);
    double getAngle(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame);
    double getDihedral(cAtom *atom1, cAtom *atom2, cAtom *atom3,cAtom *atom4, int frame);
    double getAnglePBC(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame,double x,double y,double z);
    double getBiSector(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame);
    double getNBiSector(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame);
    double safeAcos (double x);



protected:


private:
    double pbcx,pbcy,pbcz;
    double getBond(ccoordinates &coord1, ccoordinates &coord2);
    double getAngle(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3);
    double getBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3);
    double getNBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3);
    ccoordinates vecBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3);
    double vecLength(ccoordinates &vec1);
    double vecAngle(ccoordinates &vec1, ccoordinates &vec2);



};

#endif // CMEASURE_H
