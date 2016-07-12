#ifndef READINPUT_H
#define READINPUT_H
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "input.h"
#include <mix.h>
#include <stdlib.h>
#include "fepatoms.h"
using namespace std;

class readInput
{
public:
    readInput(string fn);
    const vector<input*>  getPairIds() {return vecPair;}
    const vector<input*>  getBondIds() {return vecBonds;}
    const vector<input*>  getAngleIds() {return vecAngles;}
    const vector<fepAtoms*>  getFepAtoms() {return vecFep;}
    const vector<input*>  getDihedralIds() {return vecDihedral;}
    const vector<input*>  getImproperIds() {return vecImproper;}
    bool ifii(){return printii;}
    ~readInput();
    vector<string> getFiles() {return files;}
    vector<Cmix*> & getMixing() {return vecMix;}
    vector<string> getNames(string in);


private:
    bool printii;
    string filename;
    ifstream instream;
    string path;
    string location;
    vector<input*> vecPair;
    vector<input*> vecBonds,vecDihedral,vecImproper;
    vector<input*> vecAngles;
    vector<input*>::iterator it;
    vector<Cmix*>::iterator itMix;
    vector<fepAtoms*>::iterator itFep;
    vector<string> files;
    vector<Cmix*> vecMix;
    vector<fepAtoms*> vecFep;
};

#endif // READINPUT_H
