#include "csystem.h"

csystem::csystem()
{
   // cout << "Default system constructor: " << this << endl;
}


csystem::~csystem()
{
   // cout << "Destructor system : " << this << endl;

    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        delete *itAtom;
    }

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {


        delete *itMol;

    }



    for (itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
    {
        delete *itBond;
    }

    for (itAngle=vecAngles.begin();itAngle!=vecAngles.end();itAngle++)
    {
        delete *itAngle;
    }

    for (itDihedral=vecDihedral.begin();itDihedral!=vecDihedral.end();itDihedral++)
    {
        delete *itDihedral;
    }

    for (itImproper=vecImproper.begin();itImproper!=vecImproper.end();itImproper++)
    {
        delete *itImproper;
    }
}

void csystem::addCoord(int idx, double x, double y, double z)
{
    Nframes=1;
    if (idx<vecAtoms.size())
    {

        vecAtoms.at(idx)->addCoord(x,y,z);
    }
}

void csystem::addAtom(int idx, int resid, string resname, string name, string type, double charge, double mass,int t)
{
    vecAtoms.push_back(new cAtom(idx,resid,resname,name,type,charge,mass,t));

}

void csystem::addBond(int t,int idx1, int idx2)
{
    cBond * ptrB=new cBond(t,idx1,idx2);
    ptrB->addAtom1(at(idx1));
    ptrB->addAtom2(at(idx2));
    vecBonds.push_back(ptrB);

}

void csystem::addAngle(int t,int idx1, int idx2, int idx3)
{
    cAngle * ptrA=new cAngle(t,idx1,idx2,idx3);
    ptrA->addAtom1(at(idx1));
    ptrA->addAtom2(at(idx2));
    ptrA->addAtom3(at(idx3));
    vecAngles.push_back(ptrA);

}

void csystem::addDihedral(int t, int idx1, int idx2, int idx3, int idx4)
{
    cDihederal * ptrDi=new cDihederal(t,idx1,idx2,idx3,idx4);
    ptrDi->addAtom1(at(idx1));
    ptrDi->addAtom2(at(idx2));
    ptrDi->addAtom3(at(idx3));
    ptrDi->addAtom4(at(idx4));
    vecDihedral.push_back(ptrDi);
}

void csystem::addImproper(int t, int idx1, int idx2, int idx3, int idx4)
{
    cImproper * ptrIm=new cImproper(t,idx1,idx2,idx3,idx4);
    ptrIm->addAtom1(at(idx1));
    ptrIm->addAtom2(at(idx2));
    ptrIm->addAtom3(at(idx3));
    ptrIm->addAtom4(at(idx4));
    vecImproper.push_back(ptrIm);
}












