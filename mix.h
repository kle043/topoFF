#ifndef MIX_H
#define MIX_H
#include <string>
#include <vector>
#include "lennardJones.h"
#include "buckingham.h"
#include <cmath>
class Cmix
{
public:
    Cmix(){;}
    Cmix(string n1,string n2,string mix):name1(n1),name2(n2),szmixing(mix){;}
    const string& getName1(){return name1;}
    const string& getName2(){return name2;}
    const string& getMixing(){return szmixing;}
    void performMixing(vector<potential*> & vecPotential,vector<Cmix*> & vecId);
private:
    potential *lj_mix(potential* & pot1, potential *& pot2, string mixingrule);
    potential *geometric(potential *pot1, potential *pot2);
    string name1;
    string name2;
    string szmixing;
    potential * mixedPotential;
    vector<Cmix*>::iterator itCmix;
    vector<potential*>::iterator itPot;

};

#endif // MIX_H
