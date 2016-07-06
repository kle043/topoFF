#ifndef CANGLE_H
#define CANGLE_H
#include "catom.h"

class cAngle
{
public:
    cAngle(int t,int i1,int i2,int i3);
    cAngle(int t,cAtom *at1,cAtom *at2,cAtom *at3);
    int getIdx1(){return atom1->getIdx();}
    int getIdx2(){return atom2->getIdx();}
    int getIdx3(){return atom3->getIdx();}
    int getType(){return type;}
    void setType(int i){type=i;}
    void addAtom1(cAtom * at){atom1=at;}
    void addAtom2(cAtom * at){atom2=at;}
    void addAtom3(cAtom * at){atom3=at;}
    cAtom * getAtom1(){return atom1;}
    cAtom * getAtom2(){return atom2;}
    cAtom * getAtom3(){return atom3;}

private:
    int type,idx1,idx2,idx3;
     cAtom *atom1,*atom2,*atom3;

};

#endif // CANGLE_H
