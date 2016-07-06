#ifndef CSYSTEMSORTER_H
#define CSYSTEMSORTER_H
#include "isystem.h"
#include "cmeasure.h"
#include "FF/csortpotential.h"
#include "cselection.h"


class cSystemSorter
{
public:
    cSystemSorter(csystem *sys1);
    ~cSystemSorter();
    void sortOnDistance(cSortPotential *inp1);
    void findMolecules();
    void updateAngles();

private:
    void searchBonds(cselection &sel1, cselection &sel2, double bond);
    void searchAngles(cselection & sel1, cselection &sel2, cselection &sel3, double angle, double bond1, double bond2);
    csystem *sys;
    cSortPotential *inp;
    vector<potential*> vecBondPot,vecAnglePot;
    vector<potential*>::iterator itAnglePot,itBondPot;
    cmeasure measure;
    vector<cAtom*> vecAtoms,vecAtom1,vecAtom2,vecAtom3;
    vector<cMolecule*> vecMolecule;
    vector<cMolecule*>::iterator itMol;
    vector<cAtom*>::iterator itAt1,itAt2,itAt3;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cDihederal*> vecDihedral;
    vector<cImproper*> vecImproper;
    vector<cAtom*>::iterator itAtom;
    vector<cBond*>::iterator itBond,itBond2;
    vector<cAngle*>::iterator itAngle;
    vector<cDihederal*>::iterator itDihedral;
    vector<cImproper*>::iterator  itImproper;
    double pbcx,pbcy,pbcz;
    int type;




};

#endif // CSYSTEMSORTER_H
