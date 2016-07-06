#include "cimproper.h"

cImproper::cImproper(int t, int i1, int i2, int i3, int i4):type(t),idx1(i1),idx2(i2),idx3(i3),idx4(i4)
{
    isDi=false;
}

cImproper::cImproper(int t, cAtom *at1, cAtom *at2, cAtom *at3, cAtom *at4):type(t),atom1(at1),atom2(at2),atom3(at3),atom4(at4)
{
    isDi=false;
    idx1=at1->getIdx();
    idx2=at2->getIdx();
    idx3=at3->getIdx();
    idx4=at4->getIdx();


}

