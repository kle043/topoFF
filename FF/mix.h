#ifndef MIX_H
#define MIX_H

#include <vector>
#include "cmixatoms.h"
#include "lennardJones.h"
#include "buckingham.h"
#include <cmath>
class Cmix
{
public:
    Cmix(){;}
    void performMixing(vector<potential*> & vecPotential,vector<cmixAtoms*> & vecId);
private:
    potential *lj_mix(potential* & pot1, potential *& pot2, string mixingrule);
    potential *geometric(potential *pot1, potential *pot2);
    potential * mixedPotential;
    vector<cmixAtoms*>::iterator itCmix;
    vector<potential*>::iterator itPot;

};

#endif // MIX_H
