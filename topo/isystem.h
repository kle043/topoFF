#ifndef ISYSTEM_H
#define ISYSTEM_H
#include "catom.h"
#include "cmolecule.h"
#include "cbond.h"
#include "cangle.h"
#include "cdihederal.h"
#include "cimproper.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <iomanip>
#include <stdexcept>
#include <cfloat>
#include <math.h>
#include "FF/csortpotential.h"
class isystem
{
public:
    isystem(){;}
    int num() const {return vecAtoms.size();}
    int numMol(string resname);
    int NBonds(){return vecBonds.size();}
    int  NAngles(){return vecAngles.size();}
    int  NDihedrals(){return vecDihedral.size();}
    int  NImpropers(){return vecImproper.size();}
    int  NAtomTypes(){return vecCharge.size();}
    int  NBondTypes(){return vecBondPot.size();}
    int  NAngleTypes(){return vecAnglePot.size();}
    int  NDihedralTypes(){return vecDihedralPot.size();}
    int  NImproperTypes(){return vecImproperPot.size();}
    void readTrajectory(string filename,int b=0,int e=0,int skip=0,bool wrap=false);
    int getNframes(){return Nframes;}
    void printSummary();
    void printMolecules();
    void setPBC(double xl,double xh,double yl,double yh,double zl,double zh);
    double getPbcX(){return pbcXh-pbcXl;}
    double getPbcY(){return pbcYh-pbcYl;}
    double getPbcZ(){return pbcZh-pbcZl;}
    double getXmin(){return xmin;}
    double getYmin(){return ymin;}
    double getZmin(){return zmin;}
    double getXmax(){return xmax;}
    double getYmax(){return ymax;}
    double getZmax(){return zmax;}
    void addOPLS();
    void removeBonds(vector<int> vecInt);
    void removeAngle(vector<int> vecInt);
    void removeImproper(vector<int> vecInt);
    void setParameters(cSortPotential * inp);
    void setResId();
    void update();
    void wrapCoordinates();
    void swapImproperDihedral(vector<pair<int,int> > vecIds);
    vector<cSite*> & getChargePot(){return vecCharge;}
    vector<potential*> & getAtomPot(){return vecPairPot;}
    vector<potential*> & getBondPot(){return vecBondPot;}
    vector<potential*> & getAnglePot(){return vecAnglePot;}
    vector<potential*> & getDihedralPot(){return vecDihedralPot;}
    vector<potential*> & getImproperPot(){return vecImproperPot;}
    vector<cMolecule *> getVecMol_name(string resname);
    vector<cMolecule *> & getVecMol(){return vecMolecule;}
    cAtom * & at(int i) {return vecAtoms.at(i-1);}
    vector<cAtom*> & getAtoms(){return vecAtoms;}
    vector<cBond*> & getBonds(){return vecBonds;}
    vector<cAngle*> & getAngles(){return vecAngles;}
    vector<cImproper*> & getImpropers(){return vecImproper;}



protected:
    double  pbcXl,pbcXh,pbcYl,pbcYh,pbcZl,pbcZh;
    float xmin,xmax,ymin,ymax,zmin,zmax;
    vector<cMolecule*> vecMolecule;
    vector<cMolecule*>::iterator itMol;
    vector<cAtom*> vecAtoms;
    vector<vector<cAtom*> *> vecUniqeAtoms;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cDihederal*> vecDihedral;
    vector<cImproper*> vecImproper;
    vector<cAtom*>::iterator itAtom;
    vector<cBond*>::iterator itBond;
    vector<cAngle*>::iterator itAngle;
    vector<cDihederal*>::iterator itDihedral;
    vector<cImproper*>::iterator  itImproper;
    int Nframes,NBTypes,NATypes,NDTypes,NITypes;
    vector<cSite*> vecCharge;
    vector<cSite*>::iterator itCharge;
    vector<potential*> vecPairPot,vecBondPot,vecAnglePot,vecDihedralPot,vecImproperPot;
    vector<potential*>::iterator itPot;

private:




};

#endif // ISYSTEM_H
