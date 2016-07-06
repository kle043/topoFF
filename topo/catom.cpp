#include "catom.h"

cAtom::~cAtom()
{
    for (itCoord=vecCoord.begin();itCoord!=vecCoord.end();itCoord++)
    {
        delete *itCoord;
    }

}

cAtom::cAtom(int i,int rid,string resN,string N,string T,double ch,double m,int t):index(i),resid(rid),resname(resN),name(N),type(T),charge(ch),mass(m),typeId(t)
{
    visited=false;
    pbc=false;

    if(name=="Ow"||name=="Oc"||name=="O2"||name=="Oh"||name=="Ot"||name=="O2" || name=="OG" || name=="OS")
    {
        mass=15.99940;

    }else if (name=="Cc" || name =="C2"|| name =="Cm"||name=="Ct"||name=="C1"|| name=="C2" || name=="CT1"|| name=="CT2")
    {
        mass=12.01070;

    }else if (name=="Hw"|| name =="Hm"||name=="Ht"||name=="Ho"||name=="Hf"||name=="H1"|| name=="H2"|| name=="HG"||name=="HC1"||name=="HC2")
    {
        mass=1.00800;

    }else if (name=="Cac")
    {
        mass=40.077999;
    }else if (name=="N")
    {
        mass=14.0067;
    }else if (name=="Ar")
    {
        mass=39.948;
    }

}

cAtom::cAtom(int i, int rid, string resN, string N, string T, double ch, double m, int t, double x, double y, double z):index(i),resid(rid),resname(resN),name(N),type(T),charge(ch),mass(m),typeId(t)
{
    visited=false;
    pbc=false;

    addCoord(x,y,z);


}

void cAtom::addCoord(double x, double y, double z)
{

    vecCoord.push_back(new ccoordinates(x,y,z));

}

void cAtom::printTerminal()
{
    cout <<getIdx()<<" "
         <<getName()<<" "
         <<getResname()<<" "
         <<getMass()<<endl;

}

