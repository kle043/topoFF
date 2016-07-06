#ifndef CXMLWRITER_H
#define CXMLWRITER_H
#include "csystem.h"
#include "cconstants.h"
#include <limits>
using namespace constants;
class cxmlwriter
{
public:
    cxmlwriter();
    void write(isystem * sys1, string filename, bool isbody);


private:
    void getImage(ccoordinates *coord);
    void balanceCharge();
    double getHoomdCharge(cMolecule *ptrMol, string name);
    void setResHoomdCharge(cMolecule *ptrMol, string name, double hoomdCharge, int natoms);
    double SetPrecision(double value, double precision);
    isystem *sys;
    vector<potential*> vecPot;
    vector<potential*>::iterator itPot;
    vector<cAtom*> vecAtoms;
    vector<cSite*> vecCharge;
    vector<cSite*>::iterator itCharge;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cImproper*> vecImpropers;
    vector<cDihederal*> vecDihedrals;
    vector<cDihederal*>::iterator itDihedral;
    vector<cAngle*>::iterator itAngle;
    vector<cBond*>::iterator itBond;
    vector<cAtom*>::iterator itAtom;
    vector<cImproper*>::iterator itImproper;
    vector<cMolecule*> vecMol;
    vector<cMolecule*>::iterator itMol;
    int image[3];
    double pbcx,pbcy,pbcz;
    double factorCharge;


};

#endif // CXMLWRITER_H
