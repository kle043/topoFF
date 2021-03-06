#include "cdatawriter.h"

cdatawriter::cdatawriter()
{

}

void cdatawriter::write(isystem *sys, string filename)
{
    filename="data."+filename;
    ofstream out(filename.c_str());
    out.precision(4);
    vecPot=sys->getAtomPot();
    int ntypes=0;


    out<< std::setprecision(7)<<"Lammps data file. CGCMM style. atom_style full generated by topoFF\n";

    out<<" "<<sys->num()<<" atoms"<<endl;
    out<<" "<<sys->NBonds()<<" bonds"<<endl;
    out<<" "<<sys->NAngles()<<" angles"<<endl;
    out<<" "<<sys->NDihedrals()<<" dihedrals"<<endl;
    out<<" "<<sys->NImpropers()<<" impropers"<<endl;
    out<<" "<<sys->NAtomTypes()<<" atom types"<<endl;
    out<<" "<<sys->NBondTypes()<<" bond types"<<endl;
    out<<" "<<sys->NAngleTypes()<<" angle types"<<endl;
    out<<" "<<sys->getDihedralPot().size()<<" dihedral types"<<endl;
    out<<" "<<sys->NImproperTypes()<<" improper types"<<endl;
    out<<" "<<sys->getXmin()<<" "<<sys->getXmax()<<" xlo xhi"<<endl;
    out<<" "<<sys->getYmin()<<" "<<sys->getYmax()<<" ylo yhi"<<endl;
    out<<" "<<sys->getZmin()<<" "<<sys->getZmax()<<" zlo zhi"<<endl;

    out<<endl;


    if(!vecPot.empty())
    {
        out<<"# Pair Coeffs\n#"<<endl;
    }

    vecCharge=sys->getChargePot();

    for (itCharge=vecCharge.begin();itCharge!=vecCharge.end();itCharge++)
    {

           out<<"# "<<(*itCharge)->getIdx()<<" "<<(*itCharge)->getName()<<endl;

    }


    out<<endl;


    vecPot=sys->getBondPot();

    if(!vecPot.empty())
    {
        out<<"# Bond Coeffs\n#"<<endl;
    }

    for (itPot=vecPot.begin();itPot!=vecPot.end();itPot++)
    {
        out<<"# "<<(*itPot)->getId1()<<" "<<(*itPot)->getName1()<<"-"<<(*itPot)->getName2()<<endl;
    }

    out<<endl;


    vecPot=sys->getAnglePot();

    if(!vecPot.empty())
    {
        out<<"# Angle Coeffs\n#"<<endl;
    }

    for (itPot=vecPot.begin();itPot!=vecPot.end();itPot++)
    {
        out<<"# "<<(*itPot)->getId1()<<" "<<(*itPot)->getName1()<<"-"<<(*itPot)->getName2()<<"-"<<(*itPot)->getName3()<<endl;
    }
    out<<endl;

    vecPot=sys->getDihedralPot();

    if(!vecPot.empty())
    {
        out<<"# Dihedral Coeffs\n#"<<endl;
    }




    for (itPot=vecPot.begin();itPot!=vecPot.end();itPot++)
    {
        out<<"# "<<(*itPot)->getId1()<<" "<<(*itPot)->getName1()<<"-"<<(*itPot)->getName2()<<"-"<<(*itPot)->getName3()<<"-"<<(*itPot)->getName4()<<endl;
    }
    out<<endl;

    vecPot=sys->getImproperPot();

    if(!vecPot.empty())
    {
        out<<"# Improper Coeffs\n#"<<endl;
    }


    for (itPot=vecPot.begin();itPot!=vecPot.end();itPot++)
    {
        out<<"# "<<(*itPot)->getId1()<<" "<<(*itPot)->getName1()<<"-"<<(*itPot)->getName2()<<"-"<<(*itPot)->getName3()<<"-"<<(*itPot)->getName4()<<endl;
    }
    out<<endl;


    vecPot=sys->getAtomPot();
    vecAtoms=sys->getAtoms();

    out<<" Masses\n"<<endl;




    for (itCharge=vecCharge.begin();itCharge!=vecCharge.end();itCharge++)
    {
        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            if((*itAtom)->getName()==(*itCharge)->getName())
            {
                out<<" "<<(*itCharge)->getIdx()<<" "<<(*itAtom)->getMass()<<" # "<<(*itCharge)->getName()<<endl;
                break;
            }
        }

    }


    out<<endl;

    out<<" Atoms\n\n";

    ccoordinates *coord;
    cAtom * ptrAt;

    vecMol=sys->getVecMol();

    int i=1;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            coord=(*itAtom)->getCoordinates(0);
            ptrAt=*itAtom;

            out<<i<<" "<<ptrAt->getResId()<<" "<<ptrAt->getType()<<" "<<ptrAt->getCharge()<<" "
                <<coord->getX()<<" "<<coord->getY()<<" "<<coord->getZ()<<" # "<<ptrAt->getName()<<" "<<ptrAt->getResname()<<endl;

            ptrAt->setIdx(i);

            i++;

        }
    }

    if(!sys->getBondPot().empty())
    {

        out<<"\n Bonds\n\n";


    cBond * ptrBn;

    i=1;
    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecBonds=(*itMol)->getVecBonds();


        for (itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
        {


            ptrBn=*itBond;

            out<<i<<" "<<ptrBn->getType()<<" "<<ptrBn->getIdx1()<<" "<<ptrBn->getIdx2()
               <<" # "<<ptrBn->getAtom1()->getName()<<" "<<ptrBn->getAtom2()->getName()<<" "<<ptrBn->getAtom2()->getResname()<<endl;

            i++;

        }
    }
    }

    if(!sys->getAnglePot().empty())
    {

        out<<"\n Angles\n\n";

    cAngle * ptrAn;

    i=1;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAngles=(*itMol)->getVecAngles();


        for (itAngle=vecAngles.begin();itAngle!=vecAngles.end();itAngle++)
        {


            ptrAn=*itAngle;

            out<<i<<" "<<ptrAn->getType()<<" "<<ptrAn->getIdx1()<<" "<<ptrAn->getIdx2()<<" "<<ptrAn->getIdx3()
               <<" # "<<ptrAn->getAtom1()->getName()<<" "<<ptrAn->getAtom2()->getName()<<" "<<ptrAn->getAtom3()->getName()<<" "<<ptrAn->getAtom2()->getResname()<<endl;

            i++;

        }
    }
    }

    if(!sys->getDihedralPot().empty())
    {

        out<<"\n Dihedrals\n\n";


        cDihederal * ptrDi;

        i=1;

        for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
        {
            vecDihedrals=(*itMol)->getVecDihedrals();


            for (itDihedral=vecDihedrals.begin();itDihedral!=vecDihedrals.end();itDihedral++)
            {


                ptrDi=*itDihedral;

                out<<i<<" "<<ptrDi->getType()<<" "<<ptrDi->getIdx1()<<" "<<ptrDi->getIdx2()<<" "<<ptrDi->getIdx3()<<" "<<ptrDi->getIdx4()
                   <<" # "<<ptrDi->getAtom1()->getName()<<" "<<ptrDi->getAtom2()->getName()<<" "<<ptrDi->getAtom3()->getName()<<" "<<ptrDi->getAtom4()->getName()<<" "<<ptrDi->getAtom2()->getResname()<<endl;

                i++;

            }
        }
    }


    if(!sys->getImproperPot().empty())
    {

        out<<"\n Impropers\n\n";


        cImproper * ptrIm;

        i=1;

        for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
        {
            vecImpropers=(*itMol)->getVecImpropers();


            for (itImproper=vecImpropers.begin();itImproper!=vecImpropers.end();itImproper++)
            {


                ptrIm=*itImproper;

                out<<i<<" "<<ptrIm->getType()<<" "<<ptrIm->getIdx1()<<" "<<ptrIm->getIdx2()<<" "<<ptrIm->getIdx3()<<" "<<ptrIm->getIdx4()
                   <<" # "<<ptrIm->getAtom1()->getName()<<" "<<ptrIm->getAtom2()->getName()<<" "<<ptrIm->getAtom3()->getName()<<" "<<ptrIm->getAtom4()->getName()<<" "<<ptrIm->getAtom2()->getResname()<<endl;

                i++;

            }
        }
    }


    cout<<"Lammps data file written, see "<<filename<<endl;






    out.close();

}

