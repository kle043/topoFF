#ifndef CDIHEDERAL_H
#define CDIHEDERAL_H
#include "catom.h"

class cDihederal
{
public:
    cDihederal(int t, int i1, int i2, int i3,int i4);
    cDihederal(int t, cAtom *at1, cAtom *at2, cAtom *at3, cAtom *at4);
    int getIdx1(){return atom1->getIdx();}
    int getIdx2(){return atom2->getIdx();}
    int getIdx3(){return atom3->getIdx();}
    int getIdx4(){return atom4->getIdx();}
    void setType(int i){type=i;}
    int getType(){return type;}
    void addAtom1(cAtom * at){atom1=at;}
    void addAtom2(cAtom * at){atom2=at;}
    void addAtom3(cAtom * at){atom3=at;}
    void addAtom4(cAtom * at){atom3=at;}
    cAtom * getAtom1(){return atom1;}
    cAtom * getAtom2(){return atom2;}
    cAtom * getAtom3(){return atom3;}
    cAtom * getAtom4(){return atom4;}

private:
    int type,idx1,idx2,idx3,idx4;
     cAtom *atom1,*atom2,*atom3,*atom4;

};

#endif // CDIHEDERAL_H
