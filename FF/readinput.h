#ifndef READINPUT_H
#define READINPUT_H
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "input.h"
#include "mix.h"
#include <stdlib.h>
#include "fepatoms.h"
#include <sstream>
#include <iomanip>
using namespace std;

class readInput
{
public:
    readInput(string fn);
    void clearVec();
    void addPair(int id,string sz);
    void addBond(int id,string sz);
    void addAngle(int id,string sz);
    void addDihedral(int id,string sz);
    void addImproper(int id,string sz);
    const vector<input*>  getPairIds() {return vecPair;}
    const vector<input*>  getBondIds() {return vecBonds;}
    const vector<input*>  getAngleIds() {return vecAngles;}
    const vector<fepAtoms*>  getFepAtoms() {return vecFep;}
    const vector<input*>  getDihedralIds() {return vecDihedral;}
    const vector<input*>  getImproperIds() {return vecImproper;}
    bool ifii(){return printii;}
    ~readInput();
    vector<string> getFiles() {return files;}
    vector<cmixAtoms*> & getMixing() {return vecMix;}
    vector<string> getNames(string in);
    vector<int> getVecRmAtom() {return vecRmAt;}
    vector<int> getVecRmBond() {return vecRmBn;}
    vector<int> getVecRmAngle(){return vecRmAn;}
    vector<int> getVecRmImproper(){return vecRmIm;}


private:
    bool printii;
    string filename;
    ifstream instream;
    string path;
    string location;
    vector<int> vecRmAt,vecRmBn,vecRmAn,vecRmIm;
    vector<input*> vecPair;
    vector<input*> vecBonds,vecDihedral,vecImproper;
    vector<input*> vecAngles;
    vector<input*>::iterator it;
    vector<cmixAtoms*>::iterator itMix;
    vector<fepAtoms*>::iterator itFep;
    vector<string> files;
    vector<cmixAtoms*> vecMix;
    vector<fepAtoms*> vecFep;
};

#endif // READINPUT_H
