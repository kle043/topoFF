#include "cangle.h"

cAngle::cAngle(int t, int i1, int i2, int i3):type(t),idx1(i1),idx2(i2),idx3(i3)
{

}

cAngle::cAngle(int t, cAtom *at1, cAtom *at2, cAtom *at3):type(t),atom1(at1),atom2(at2),atom3(at3)
{
    idx1=at1->getIdx();
    idx2=at2->getIdx();
    idx3=at3->getIdx();


}

