#ifndef FEPATOMS_H
#define FEPATOMS_H
#include <string>
#include <vector>
using namespace std;
class fepAtoms
{
public:
    fepAtoms(string n1,string n2,double l);
    const string& getName1(){return name1;}
    const string& getName2(){return name2;}
    double getLambda(){return lambda;}

private:
    string name1,name2;
    double lambda;


};

#endif // FEPATOMS_H
