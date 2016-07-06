#ifndef CSORTPOTENTIAL_H
#define CSORTPOTENTIAL_H
#include "potential.h"
#include <limits>
#include <vector>
#include <utility>
#include "input.h"
#include <algorithm>
#include <unistd.h>
#include "lennardJones.h"
#include "harmonic_angle.h"
#include "harmonic_bond.h"
#include "cgroup.h"
#include "csite.h"
#include "harmonic_dihedral.h"
#include "harmonic_improper.h"
#include "coullong.h"
#include <stdlib.h>
#include "fepatoms.h"
#include "readinput.h"
#include "readff.h"
#include "mix.h"

class cSortPotential
{
public:
    cSortPotential();
    ~cSortPotential();

    void sortData(readInput &inputData, readFF &ffData,bool op,bool ho);
    void sortPair(const vector<input*> &inp, const vector<potential*> & pot, bool ii);
    void sortFep(vector<fepAtoms*> vecFep);
    void sortBonds(const vector<input*> &inp, const vector<potential*> & pot);
    void sortAngles(const vector<input*> &inp, const vector<potential*> & pot);
    void sortDihedrals(const vector<input*> &inp, const vector<potential*> & pot);
    void sortImpropers(const vector<input*> &inp, const vector<potential*> & pot);
    void sortGroup(const vector<input*> &inp, const vector<Cgroup*> &grp);
    void sortCharges(const vector<input *> &inp, vector<cSite*> &atm);
    void sortMixing(vector<potential *> &vecPot, vector<cmixAtoms*> &vecMixAt);
    void printToFile(string s);
    double getCharge(string name);
    void goHOOMD(string s);
    vector<cSite*> & getChargePot(){return vecSite;}
    vector<potential*> & getPairPot(){return vecPa;}
    vector<potential*> & getBondPot(){return vecBn;}
    vector<potential*> & getAnglePot(){return vecAn;}
    vector<potential*> & getDihedralPot(){return vecDi;}
    vector<potential*> & getImproperPot(){return vecIm;}
    vector<Cgroup*> & getGroups(){return vecGroup;}
    vector<potential*> & getFepSites(){return vecFepOut;}
    vector<int> getVecRmAtom() {return vecRmAt;}
    vector<int> getVecRmBond() {return vecRmBn;}
    vector<int> getVecRmAngle(){return vecRmAn;}
    vector<int> getVecRmImproper(){return vecRmIm;}
    vector<pair<int,int> > getVecSwapImDi();
    void removePot();
   // void remove();

private:
    vector<Cgroup*> vecGroup;
    vector<fepAtoms*>::iterator itFep;
    vector<Cgroup*>::iterator itGroup;
    vector<input*>  inputVec;
    vector<cSite*> vecSite,vecSiteCopy;
    vector<cSite*>::iterator itSite;
    vector<input*>::iterator it,lt;
    vector<potential*> vecFepOut;
    vector<potential*> vecPotential,copyPot,vecBn,vecAn,vecDi,vecIm,vecPa;
    vector<potential*> fullPotential;
    vector<potential*>::iterator itPotential,itPot2;
    double hoomdEnergy,hoomdDist,hoomdMass;
    bool opls,hoomd;

    vector<int> vecRmAt,vecRmBn,vecRmAn,vecRmDi,vecRmIm;


};

#endif //CSORTPOTENTIAL_H
