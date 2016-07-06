#ifndef CFFSTREAM_H
#define CFFSTREAM_H
#include "csortpotential.h"
#include <algorithm>
class cffStream
{
public:
    cffStream(cSortPotential &pot);
    void writeLammps(string file);
    void writeHoomd(string file);

private:
    bool vecHasStyle(vector<potential *> p, string s);
    ofstream outfile;
    vector<potential*> vecPotential,copyPot,vecBn,vecAn,vecDi,vecIm,vecPa,vecFepSites;
    vector<potential*>::iterator itPotential;
    vector<cSite*> vecSite;
    vector<cSite*>::iterator itSite;
    vector<Cgroup*> vecGroup;
    vector<fepAtoms*>::iterator itFep;
    vector<Cgroup*>::iterator itGroup;
    string path;
    string location;
    string filename;
    double hoomdMass,hoomdDist,hoomdEnergy;


};

#endif // CFFSTREAM_H
