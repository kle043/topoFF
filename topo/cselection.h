#ifndef CSELECTION_H
#define CSELECTION_H
#include "csystem.h"
#include <sstream>
#include "isystem.h"
class cselection: public isystem
{
public:
    cselection(){;}
    ~cselection();
    cselection  operator() (isystem * sys,string sel);





private:
    vector<string> vecNames;
    vector<cMolecule *> vecMol;
    vector<cAtom*> vecSys;
    vector<cBond*> vecB;
    vector<cAngle*> vecA;
    vector<string>::iterator itSz;
    void setSelNames(string names);

};

#endif // CSELECTION_H
