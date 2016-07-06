#include "input.h"
input::input(int i, std::string n1, std::string n2)
{
    id=i;
    szBondAtoms[0]=n1;
    szBondAtoms[1]=n2;

}
input::input(int i, std::string n1, std::string n2, string n3)
{
    id=i;
    szAngleAtoms[0]=n1;
    szAngleAtoms[1]=n2;
    szAngleAtoms[2]=n3;

}

input::input(int i, string n1, string n2, string n3, string n4, bool improper)
{
    id=i;

    if(improper)
    {
        szImproperAtoms[0]=n1;
        szImproperAtoms[1]=n2;
        szImproperAtoms[2]=n3;
        szImproperAtoms[3]=n4;
    }else{
        szDihedralAtoms[0]=n1;
        szDihedralAtoms[1]=n2;
        szDihedralAtoms[2]=n3;
        szDihedralAtoms[3]=n4;

    }

}
