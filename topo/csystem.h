#ifndef CSYSTEM_H
#define CSYSTEM_H
#include "topo/isystem.h"
#include <stack>
using namespace std;
class csystem : public isystem
{
public:
    csystem();
    ~csystem();
    void addCoord(int idx,double x,double y,double z);
    void addAtom(int idx, int resid, string resname, string name, string type, double charge, double mass, int t);
    void addBond(int t, int idx1, int idx2);
    void addAngle(int t, int idx1, int idx2, int idx3);
    void addDihedral(int t, int idx1, int idx2, int idx3, int idx4);
    void addImproper(int t, int idx1, int idx2, int idx3, int idx4);
    void addMolecule(cMolecule * mol){vecMolecule.push_back(mol);}
    void addBond(cBond * bn){vecBonds.push_back(bn);}
    void addAngle(cAngle * an){vecAngles.push_back(an);}
    void addDihedral(cDihederal * di){vecDihedral.push_back(di);}
    void addImproper(cImproper * im){vecImproper.push_back(im);}
    int num() const {return vecAtoms.size();}    






private:
    vector<cBond>::iterator itBond2;


};

#endif // CSYSTEM_H
