#ifndef INPUT_H
#define INPUT_H
#include <string>
#include <fstream>
#include <vector>
using namespace std;
class input
{
public:
    input(int i,string n):id(i),nameAtom(n){;}
    void setNameAtom(string n){nameAtom=n;}
    input(int i,string n1,string n2);
    input(int i,string n1,string n2,string n3);
    input(int i, string n1, string n2, string n3, string n4,bool improper);
    const int &  getId(){return id;}
    const string &  getSiteName(){return nameAtom;}
    string* getBondAtoms(){return szBondAtoms;}
    string* getAngleAtoms(){return szAngleAtoms;}
    string* getDihedralAtoms(){return szDihedralAtoms;}
    string* getImproperAtoms(){return szImproperAtoms;}



private:
    int id;
    string nameAtom;
    string szBondAtoms[2];
    string szAngleAtoms[3];
    string szDihedralAtoms[4];
    string szImproperAtoms[4];


};

#endif // INPUT_H
