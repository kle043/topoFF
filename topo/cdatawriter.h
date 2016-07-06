#ifndef CDATAWRITER_H
#define CDATAWRITER_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include "csystem.h"
#include "FF/readinput.h"
#include <iomanip>

class cdatawriter
{
public:
    cdatawriter();
    void write(isystem * sys,string filename);

private:
    vector<potential*> vecPot;
    vector<potential*>::iterator itPot;
    vector<cAtom*> vecAtoms;
    vector<cSite*> vecCharge;
    vector<cSite*>::iterator itCharge;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cImproper*> vecImpropers;
    vector<cImproper*>::iterator itImproper;
    vector<cDihederal*> vecDihedrals;
    vector<cDihederal*>::iterator itDihedral;
    vector<cAngle*>::iterator itAngle;
    vector<cBond*>::iterator itBond;
    vector<cAtom*>::iterator itAtom;
    vector<cMolecule*> vecMol;
    vector<cMolecule*>::iterator itMol;


};

#endif // CDATAWRITER_H
