#ifndef ISYSTEM_H
#define ISYSTEM_H
#include "catom.h"
#include "cmolecule.h"
#include "cbond.h"
#include "cangle.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "dcd_r.hpp"
#include <iomanip>
#include <stdexcept>
#include <cfloat>
#include <math.h>
class isystem
{
public:
    isystem(){;}
    int num() const {return vecAtoms.size();}
    int numMol(string resname);
    int numMol_at(int i);
    vector<cMolecule*> & getVecMol_name(string resname);
    vector<cMolecule*> & getVecMol_at(int i);
    cAtom * & at(int i) {return vecAtoms.at(i-1);}
    vector<cAtom*> & getAtoms(){return vecAtoms;}
    vector<cBond*> & getBonds(){return vecBonds;}
    vector<cAngle*> & getAngles(){return vecAngles;}
    vector< vector<cMolecule*> *> & getVecMol(){return vecVecMolecule;}
    void readTrajectory(string filename,int b=0,int e=0,int skip=0,bool wrap=false);
    int getNframes(){return Nframes;}
    void printSummary();
    void printMolecules();
    double getPbcX(){return pbcXh;}
    double getPbcY(){return pbcYh;}
    double getPbcZ(){return pbcZh;}
    double getXmin(){return xmin;}
    double getYmin(){return ymin;}
    double getZmin(){return zmin;}
    double getXmax(){return xmax;}
    double getYmax(){return ymax;}
    double getZmax(){return zmax;}


protected:
    double  pbcXl,pbcXh,pbcYl,pbcYh,pbcZl,pbcZh;
    float xmin,xmax,ymin,ymax,zmin,zmax;
    vector<cMolecule*> vecMolecule;
    vector< vector<cMolecule*> *> vecVecMolecule;
    vector< vector<cMolecule*> *>::iterator itVecMol;
    vector<cMolecule*>::iterator itMol;
    vector<cAtom*> vecAtoms;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cAtom*>::iterator itAtom;
    vector<cBond*>::iterator itBond;
    vector<cAngle*>::iterator itAngle;
    vector<cMolecule*> * ptrVecVecMol;
    int Nframes;

private:




};

#endif // ISYSTEM_H
