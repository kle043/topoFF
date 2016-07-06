#include "cbond.h"

cBond::cBond(int t, int i1, int i2):type(t),idx1(i1),idx2(i2),bIdx1(false),bIdx2(false)
{
    visited=false;

}

cBond::cBond(int t, cAtom *at1, cAtom *at2): type(t),atom1(at1),atom2(at2),bIdx1(false),bIdx2(false)
{
    idx1=at1->getIdx();
    idx2=at2->getIdx();

    visited=false;


}

bool cBond::hasIdx(int idx)
{
    if(idx1==idx)
    {
        return true;

    }

    if(idx2==idx)
    {
        return true;

    }

    return false;



}
