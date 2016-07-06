#include "cselection.h"



cselection::~cselection()
{
   // cout << "Destructor: sel  " << this << endl;

}

cselection  cselection::operator()(isystem *sys, string sel)
{

    Nframes=sys->getNframes();
    pbcXh=sys->getPbcX();
    pbcXl=0;
    pbcYh=sys->getPbcY();
    pbcYl=0;
    pbcZh=sys->getPbcZ();
    pbcZl=0;
    xmin=sys->getXmin();
    ymin=sys->getYmin();
    zmin=sys->getZmin();
    xmax=sys->getXmax();
    ymax=sys->getYmax();
    zmax=sys->getZmax();
    bool foundSel=false;
    bool bBond1,bBond2,bBond3;
    //vecBonds=sys->vecBonds; Have to add
    //vecAngles=sys->vecAngles;



    //new empty vector vecAtoms can contain elements when selection is given
    std::size_t foundRes = sel.find("resname");
    std::size_t foundName = sel.find("name");
    std::size_t foundAll = sel.find("all");


    setSelNames(sel);
    vecSys=sys->getAtoms();
    vecB=sys->getBonds();
    vecA=sys->getAngles();

    if(foundAll!=std::string::npos)
    {
        foundSel=true;
        vecAtoms=sys->getAtoms();
        vecMolecule=sys->getVecMol();
        vecBonds=sys->getBonds();
        vecAngles=sys->getAngles();

    }





    if(foundName!=std::string::npos)
    {

        for (itAtom=vecSys.begin();itAtom!=vecSys.end();itAtom++)
        {

            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itAtom)->getName()==*itSz)
                {
                    foundSel=true;

                    vecAtoms.push_back(*itAtom);
                }
            }
        }

        for (itBond=vecB.begin();itBond!=vecB.end();itBond++)
        {
            bBond1=false;
            bBond2=false;
            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itBond)->getAtom1()->getName()==*itSz)
                {
                    bBond1=true;

                }
                if ((*itBond)->getAtom2()->getName()==*itSz)
                {
                    bBond2=true;

                }
            }

            if(bBond1 && bBond2)
            {
                vecBonds.push_back(*itBond);
            }

        }

        for (itAngle=vecA.begin();itAngle!=vecA.end();itAngle++)
        {
            bBond1=false;
            bBond2=false;
            bBond3=false;
            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itAngle)->getAtom1()->getName()==*itSz)
                {
                    bBond1=true;

                }
                if ((*itAngle)->getAtom2()->getName()==*itSz)
                {
                    bBond2=true;

                }
                if ((*itAngle)->getAtom3()->getName()==*itSz)
                {
                    bBond3=true;

                }
            }

            if(bBond1 && bBond2 && bBond3)
            {
                vecAngles.push_back(*itAngle);
            }

        }




    }

    if(foundRes!=std::string::npos)
    {
        for (itAtom=vecSys.begin();itAtom!=vecSys.end();itAtom++)
        {

            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itAtom)->getResname()==*itSz)
                {
                    foundSel=true;

                    vecAtoms.push_back(*itAtom);
                }
            }
        }

        vecMolecule=sys->getVecMol_name(*itSz);

        for (itBond=vecB.begin();itBond!=vecB.end();itBond++)
        {
            bBond1=false;
            bBond2=false;

            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itBond)->getAtom1()->getResname()==*itSz)
                {
                    bBond1=true;

                }
                if ((*itBond)->getAtom2()->getResname()==*itSz)
                {
                    bBond2=true;

                }

            }

            if(bBond1 && bBond2 )
            {
                vecBonds.push_back(*itBond);
            }

        }

        for (itAngle=vecA.begin();itAngle!=vecA.end();itAngle++)
        {
            bBond1=false;
            bBond2=false;
            bBond3=false;
            for (itSz=vecNames.begin();itSz!=vecNames.end();itSz++)
            {
                if ((*itAngle)->getAtom1()->getResname()==*itSz)
                {
                    bBond1=true;

                }
                if ((*itAngle)->getAtom2()->getResname()==*itSz)
                {
                    bBond2=true;

                }
                if ((*itAngle)->getAtom3()->getResname()==*itSz)
                {
                    bBond3=true;

                }
            }

            if(bBond1 && bBond2 && bBond3)
            {
                vecAngles.push_back(*itAngle);
            }

        }

    }

    if(!foundSel)
    {
        throw invalid_argument( "Did not find selection "+sel );

    }

    return *this;




}



void cselection::setSelNames(string names)
{
    string dummy;
    istringstream ss(names);

    ss>>dummy;

    //cout<<"Sel is "<<dummy<<endl;

    while (ss>> names)
    {
        vecNames.push_back(names);

    }

}

