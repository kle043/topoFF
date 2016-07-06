#ifndef READFF_H
#define READFF_H
#include <fstream>
#include <string>
#include <iostream>
#include "FF/input.h"
#include <vector>
#include "buckingham.h"
#include "lennardJones.h"
#include "harmonic_bond.h"
#include "harmonic_angle.h"
#include "morse_bond.h"
#include "cgroup.h"
#include "csite.h"
#include "harmonic_improper.h"
#include "harmonic_dihedral.h"
#include "cvff_improper.h"
#include "opls_dihedral.h"
#include "help.h"
#include <ctype.h>
#include <sstream>
using namespace std;

class readFF
{
public:
    readFF(const vector<string> &f);
    ~readFF();
    vector<potential*> & getPotential(){return vecPotential;}
    vector<potential*> & getAngleInteractions(){return vecAngles;}
    vector<potential*> & getDihedralInteractions(){return vecDihedrals;}
    vector<potential*> & getImproperInteractions(){return vecImproper;}
    vector<potential*> & getBondsInteractions(){return vecBonds;}
    vector<cSite*> & getAtoms(){return vecSite;}
    vector<string>  getNames(string in);
    vector<Cgroup*> &getGroups(){return vecGroup;}

private:
    string filename;
    ifstream instream;
    string path;
    string location;
    vector<cSite*> vecSite;
    vector<cSite*>::iterator itSite;
    vector<string> files;
    vector<Cgroup*> vecGroup;
    vector<string> processFile;
    vector<string>::iterator itString;
    vector<string>::iterator itFiles;
    vector<input*>  inputVec;
    vector<input*>::iterator it;
    vector<potential*> vecPotential;
    vector<potential*> vecAngles,vecDihedrals,vecImproper;
    vector<potential*> vecBonds;
    vector<potential*>::iterator itPotential;
    //unit goes her


};

#endif // READFF_H
