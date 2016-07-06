#ifndef CFULLPOTENTIAL_H
#define CFULLPOTENTIAL_H
#include "potential.h"
#include <vector>
#include <input.h>
#include <algorithm>
#include <unistd.h>
#include "lennardJones.h"
#include "harmonic_angle.h"
#include "harmonic_bond.h"
#include "cgroup.h"
#include "atom.h"
#include "harmonic_dihedral.h"
#include "harmonic_improper.h"
#include "coullong.h"
#include <stdlib.h>
#include "fepatoms.h"
class CfullPotential
{
public:
    CfullPotential();
    ~CfullPotential();

    void sortPair(const vector<input*> &inp, const vector<potential*> & pot, bool ii);
    void sortFep(vector<fepAtoms*> vecFep);
    void sortBonds(const vector<input*> &inp, const vector<potential*> & pot);
    void sortAngles(const vector<input*> &inp, const vector<potential*> & pot);
    void sortDihedrals(const vector<input*> &inp, const vector<potential*> & pot);
    void sortImpropers(const vector<input*> &inp, const vector<potential*> & pot);
    void sortGroup(const vector<input*> &inp, const vector<Cgroup*> &grp);
    void sortCharges(const vector<input *> &inp, const vector<atom*> &atm);
    void printToFile(string s);

private:
    vector<Cgroup*> vecGroup;
    vector<fepAtoms*>::iterator itFep;
    vector<Cgroup*>::iterator itGroup;
    vector<input*>  inputVec;
    vector<atom*> vecAtom,vecAtomCopy;
    vector<atom*>::iterator itAtom;
    vector<input*>::iterator it,lt;
    vector<potential*> vecFepOut;
    vector<potential*> vecPotential,copyPot;
    vector<potential*> fullPotential;
    vector<potential*>::iterator itPotential,itPot2;
    string path;
    string location;
    string filename;
    ofstream outfile;


};

#endif //CFULLPOTENTIAL_H
