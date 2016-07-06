#ifndef CMOLECULE_H
#define CMOLECULE_H
#include "catom.h"
#include "cbond.h"
#include "cangle.h"
#include "cimproper.h"
#include "cdihederal.h"
#include "cmeasure.h"
#include <math.h>
#include <map>

class cMolecule
{
public:
    cMolecule(cAtom *at);
    cMolecule(cBond *bn);
    const double & getMolMass() const {return mass;}
    const double & getNetCharge(){return charge;}
    void setNetCharge();
    int numMol(){return vecAtoms.size();}
    void setResId(int i);
    vector<cAtom*> & getAtoms(){return vecAtoms;}
    const string & getResname() const {return resname;}
    vector<cBond*> getVecBonds() {return vecBonds;}
    vector<cAngle*> getVecAngles() {return vecAngles;}
    vector<cDihederal*> getVecDihedrals() {return vecDihedrals;}
    vector<cImproper*> getVecImpropers() {return vecImpropers;}
    bool has(int idx);
    int getNAtoms(string name);
    pair<string,int> getNAtomsMax();
    cBond * getBond(int i);
    cAngle * getAngle(int i);
    cAtom * getAtom(int idx);
    void addAtom(cAtom * at);
    void addBond(cBond * bn);
    void addImproper(cImproper * im);
    void addDihederal(cDihederal * im);
    void removeBond(int i);
    void removeAngle(int i);
    void removeDihedral(int i);
    void removeImproper(int i);
    void findAngles();
    void find_1_4();
    void addAngle(cAngle * an){vecAngles.push_back(an);}
    void setVisited(){visited=true;}
    void unSetVisited(){visited=false;}
    bool getVisited(){return visited;}
    void swapImDi(pair<int, int> ids);


private:

    bool visited;
    string resname;
    double mass,charge;
    vector<cAtom*> vecAtoms;
    vector<string> vecNames;
    vector<string>::iterator itNames;
    vector<cAtom*>::iterator itAtom;
    vector<cBond*> vecBonds;
    vector<cAngle*> vecAngles;
    vector<cDihederal*> vecDihedrals;
    vector<cDihederal*>::iterator itDihedral;
    vector<cImproper*> vecImpropers;
    vector<cBond*>::iterator itBond,itBond2,itBond3;
    vector<cAngle*>::iterator itAngle,itAngle2;
    vector<cImproper*>::iterator itImproper;


};

#endif // CMOLECULE_H
