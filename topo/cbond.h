#ifndef CBOND_H
#define CBOND_H
#include "catom.h"

class cBond
{
public:
    cBond(int t,int i1,int i2);
    cBond(int t,cAtom * at1,cAtom *at2);
    void setVisited(){visited=true;}
    void unSetVisited(){visited=false;}
    bool getVisited(){return visited;}
    int getType(){return type;}
    int getIdx1(){return atom1->getIdx();}
    int getIdx2(){return atom2->getIdx();}
    void setType(int i){type=i;}
    void addAtom1(cAtom * at){atom1=at;}
    void addAtom2(cAtom * at){atom2=at;}
    cAtom * getAtom1(){return atom1;}
    cAtom * getAtom2(){return atom2;}
    bool hasIdx(int idx);
    bool bIdx1,bIdx2;


private:
    bool visited;
    int type,idx1,idx2;
    cAtom *atom1,*atom2;
};

#endif // CBOND_H
