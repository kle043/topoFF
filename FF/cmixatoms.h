#ifndef CMIXATOMS_H
#define CMIXATOMS_H
#include <string>

using namespace std;

class cmixAtoms
{
public:
    cmixAtoms(string n1, string n2, string mix);
    const string& getName1(){return name1;}
    const string& getName2(){return name2;}
    const string& getMixing(){return szmixing;}


private:
    string name1;
    string name2;
    string szmixing;
};

#endif // CMIXATOMS_H
