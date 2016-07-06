#include "isystem.h"

void isystem::readTrajectory(string filename, int b, int e, int skip, bool wrap)
{


}

int isystem::numMol(string resname)
{
    int i=0;
    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        if((*itMol)->getResname()==resname)
        {
            i++;

        }
    }


    return i;
}



vector<cMolecule *> isystem::getVecMol_name(string resname)
{
    vector<cMolecule*> vecmol;
    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        if((*itMol)->getResname()==resname)
        {
            vecmol.push_back(*itMol);

        }
    }

    return vecmol;

}

void isystem::setResId()
{
    int i=1;

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        vector<cAngle*> vecAng=(*itMol)->getVecAngles();

        (*itMol)->setResId(i);

        i++;
    }

}

void isystem::update()
{
    vecBonds.clear();
    vecAngles.clear();
    vecDihedral.clear();
    vecImproper.clear();



    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        vector<cBond*> vecBn=(*itMol)->getVecBonds();

        for (itBond=vecBn.begin();itBond!=vecBn.end();itBond++)
        {
            vecBonds.push_back(*itBond);
        }


        vector<cAngle*> vecAng=(*itMol)->getVecAngles();

        for (itAngle=vecAng.begin();itAngle!=vecAng.end();itAngle++)
        {
            vecAngles.push_back(*itAngle);
        }

        vector<cDihederal*> vecDi=(*itMol)->getVecDihedrals();

        for (itDihedral=vecDi.begin();itDihedral!=vecDi.end();itDihedral++)
        {
            vecDihedral.push_back(*itDihedral);
        }


        vector<cImproper*> vecIm=(*itMol)->getVecImpropers();

        for (itImproper=vecIm.begin();itImproper!=vecIm.end();itImproper++)
        {
            vecImproper.push_back(*itImproper);
        }
    }

}



void isystem::printSummary()
{


    string frame="=";
    string side="=";
    string title=" SYSTEM ";
    string delimiter=": ";

    int shift=1;

    string lineA=side+" NATOMS   "+delimiter+to_string(num());
    string lineB=side+" NBONDS   "+delimiter+to_string(vecBonds.size());
    string lineANG=side+" NANGLES  "+delimiter+to_string(vecAngles.size());
    string lineDi=side+" NDihedrals  "+delimiter+to_string(vecDihedral.size());
    string lineImp=side+" NImpropers  "+delimiter+to_string(vecImproper.size());
    string lineNMol=side+" NMols  "+delimiter+to_string(vecMolecule.size());
    string linePBC=side+" PBC      "+delimiter+"[ "+to_string(getPbcX())+" "+to_string(getPbcY())+" "+to_string(getPbcZ())+" ]";
    string lineLimitX=side+" LIMITS_X "+delimiter+"[ "+to_string(xmin)+"  "+to_string(xmax)+" ]";
    string lineLimitY=side+" LIMITS_Y "+delimiter+"[ "+to_string(ymin)+"  "+to_string(ymax)+" ]";
    string lineLimitZ=side+" LIMITS_Z "+delimiter+"[ "+to_string(zmin)+"  "+to_string(zmax)+" ]";
    string lineFRAME=side+" NFRAMES  "+delimiter+to_string(Nframes);


    int length=80-title.size();


    for (int i =0;i<length;i++)
    {
        cout<<frame;

        if(i==length/2)
        {
            cout<<title;
        }
    }
    cout<<endl;



    cout<<lineA<<setw(length+title.size()-lineA.size()-side.size()+shift)<<side<<endl;
    cout<<lineB<<setw(length+title.size()-lineB.size()-side.size()+shift)<<side<<endl;
    cout<<lineANG<<setw(length+title.size()-lineANG.size()-side.size()+shift)<<side<<endl;
    cout<<lineDi<<setw(length+title.size()-lineDi.size()-side.size()+shift)<<side<<endl;
    cout<<lineImp<<setw(length+title.size()-lineImp.size()-side.size()+shift)<<side<<endl;
    cout<<lineNMol<<setw(length+title.size()-lineNMol.size()-side.size()+shift)<<side<<endl;
    cout<<linePBC<<setw(length+title.size()-linePBC.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitX<<setw(length+title.size()-lineLimitX.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitY<<setw(length+title.size()-lineLimitY.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitZ<<setw(length+title.size()-lineLimitZ.size()-side.size()+shift)<<side<<endl;
    cout<<lineFRAME<<setw(length+title.size()-lineFRAME.size()-side.size()+shift)<<side<<endl;

    for (int i =0;i<length+title.size();i++)
    {
        cout<<frame;

    }
    cout<<endl;

}

void isystem::printMolecules()
{
    vector<cAtom*> vecA;


        for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
        {

            if((*itMol)->getResname()=="calc")
            {

            vecA=(*itMol)->getAtoms();

            cout<<(*itMol)->getResname()<<" "<<(*itMol)->numMol()<<" "<<(*itMol)->getMolMass()<<" "<<endl;

            for (itAtom=vecA.begin();itAtom!=vecA.end();itAtom++)
            {
                (*itAtom)->printTerminal();
                (*itAtom)->getCoordinates(0)->printCoordinates();
            }

            cout<<endl;

            }



        }


}

void isystem::setPBC(double xl, double xh, double yl, double yh, double zl, double zh)
{
    pbcXh=xh;
    pbcXl=xl;
    pbcYh=yh;
    pbcYl=yl;
    pbcZh=zh;
    pbcZl=zl;

    xmin=xl;
    xmax=xh;
    ymin=yl;
    ymax=yh;
    zmin=zl;
    zmax=zh;


}

void isystem::wrapCoordinates()
{
    double pbcx=getPbcX();
    double pbcy=getPbcY();
    double pbcz=getPbcZ();
    pbcx/=2;
    pbcy/=2;
    pbcz/=2;
    ccoordinates *coord;
    double minx=1e10;
    double miny=1e10;
    double minz=1e10;

    double xmove,ymove,zmove,x,y,z,xw,yw,zw;

    // Find min posistion

    for(itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            coord=(*itAtom)->getCoordinates(0);

            if(coord->getX()<minx)
            {
                minx=coord->getX();
            }
            if(coord->getY()<miny)
            {
                miny=coord->getY();
            }
            if(coord->getZ()<minz)
            {
                minz=coord->getZ();

            }

        }
    }



    //cout<<"min "<<minx<<" "<<miny<<" "<<minz<<endl;


    // Move particles to pbcmin and wrap

    xmove=minx+pbcx;
    ymove=miny+pbcy;
    zmove=minz+pbcz;

    for(itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            coord=(*itAtom)->getCoordinates(0);
            x=coord->getX()-xmove;
            y=coord->getY()-ymove;
            z=coord->getZ()-zmove;

            xw=x;
            yw=y;
            zw=z;

            if(x<-pbcx)
            {
                xw=fmod(x,pbcx);
                xw+=pbcx;
            }else if(x>pbcx)
            {
                xw=fmod(x,pbcx);
                xw=xw-pbcx;
            }

            if(y<-pbcy)
            {
                yw=fmod(y,pbcy);
                yw+=pbcy;

            }else if(y>pbcy)
            {
                yw=fmod(y,pbcy);
                yw=yw-pbcy;
            }

            if(z<-pbcz)
            {
                zw=fmod(z,pbcz);
                zw+=pbcz;


            }else if(z>pbcz)
            {
                zw=fmod(z,pbcz);
                zw=zw-pbcz;

            }

            coord->setCoordinates(xw,yw,zw);

        }
    }


}

void isystem::swapImproperDihedral(vector<pair<int, int> > vecIds)
{
    vector<pair<int,int>>::iterator it;
    vector<int> vecRm;


    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        for(it=vecIds.begin();it!=vecIds.end();it++)
        {


            (*itMol)->swapImDi(*it);

        }


    }

    vecRm.push_back(0);

    removeImproper(vecRm);

}



void isystem::removeBonds(vector<int> vecInt)
{


    vector<int>::iterator it;

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        for(it=vecInt.begin();it!=vecInt.end();it++)
        {
            (*itMol)->removeBond(*it);
        }

    }

    int i=1;



    vecBonds.clear();



    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        vector<cBond*> vecBn=(*itMol)->getVecBonds();
        (*itMol)->setResId(i);
        i++;

        for(itBond=vecBn.begin();itBond!=vecBn.end();itBond++)
        {

            vecBonds.push_back(*itBond);
        }

    }



}

void isystem::removeAngle(vector<int> vecInt)
{
    vector<int>::iterator it;



    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        for(it=vecInt.begin();it!=vecInt.end();it++)
        {
            (*itMol)->removeAngle(*it);

        }



    }

    int i=1;

    vecAngles.clear();

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        vector<cAngle*> vecAn=(*itMol)->getVecAngles();
        (*itMol)->setResId(i);
        i++;

        for(itAngle=vecAn.begin();itAngle!=vecAn.end();itAngle++)
        {

            vecAngles.push_back(*itAngle);
        }

    }

}

void isystem::removeImproper(vector<int> vecInt)
{
    vector<int>::iterator it;

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        for(it=vecInt.begin();it!=vecInt.end();it++)
        {
            (*itMol)->removeImproper(*it);
        }

    }

    int i=1;



    vecImproper.clear();



    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        vector<cImproper*> vecIm=(*itMol)->getVecImpropers();
        (*itMol)->setResId(i);
        i++;

        for(itImproper=vecIm.begin();itImproper!=vecIm.end();itImproper++)
        {

            vecImproper.push_back(*itImproper);
        }

    }

}

void isystem::setParameters(cSortPotential *inp)
{

    vecPairPot=inp->getPairPot();
    vecCharge=inp->getChargePot();
    vecBondPot=inp->getBondPot();
    vecAnglePot=inp->getAnglePot();
    vecImproperPot=inp->getImproperPot();
    vecDihedralPot=inp->getDihedralPot();



    for(itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {

        for (itCharge=vecCharge.begin();itCharge!=vecCharge.end();itCharge++)
        {


            if((*itAtom)->getName()==(*itCharge)->getName())
            {
                (*itAtom)->setType((*itCharge)->getIdx());


                (*itAtom)->setCharge((*itCharge)->getCharge());
                break;

            }

        }
    }
    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        (*itMol)->setNetCharge();
    }

    //for(itCharge=vecCharge.begin();itCharge!=vecCharge.end();itCharge++)
    //{
    //    cout<<(*itCharge)->getName()<<" "<<(*itCharge)->getIdx()<<endl;
    //}

    cAtom * ptrAt1,*ptrAt2,*ptrAt3,*ptrAt4;

    for(itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
    {
        ptrAt1=(*itBond)->getAtom1();
        ptrAt2=(*itBond)->getAtom2();


        for(itPot=vecBondPot.begin();itPot!=vecBondPot.end();itPot++)
        {


            if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt2->getName()==(*itPot)->getName2())
            {

                (*itBond)->setType((*itPot)->getId1());

                break;

            }else if(ptrAt1->getName()==(*itPot)->getName2() && ptrAt2->getName()==(*itPot)->getName1())
            {
                 //cout<<"set parm g"<<(*itPot)->getId1()<<endl;
                (*itBond)->setType((*itPot)->getId1());
                break;
            }

        }
    }

    for(itAngle=vecAngles.begin();itAngle!=vecAngles.end();itAngle++)
    {

        ptrAt1=(*itAngle)->getAtom1();
        ptrAt2=(*itAngle)->getAtom2();
        ptrAt3=(*itAngle)->getAtom3();

        for(itPot=vecAnglePot.begin();itPot!=vecAnglePot.end();itPot++)
        {




            if(ptrAt2->getName()==(*itPot)->getName2())
            {




                if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt3->getName()==(*itPot)->getName3())
                {
                    (*itAngle)->setType((*itPot)->getId1());



                    break;

                }else if(ptrAt1->getName()==(*itPot)->getName3() && ptrAt3->getName()==(*itPot)->getName1())
                {
                    (*itAngle)->setType((*itPot)->getId1());



                     break;
                }





            }

        }
    }

    for(itDihedral=vecDihedral.begin();itDihedral!=vecDihedral.end();itDihedral++)
    {

        ptrAt1=(*itDihedral)->getAtom1();
        ptrAt2=(*itDihedral)->getAtom2();
        ptrAt3=(*itDihedral)->getAtom3();
        ptrAt4=(*itDihedral)->getAtom4();

        for(itPot=vecDihedralPot.begin();itPot!=vecDihedralPot.end();itPot++)
        {




            if(ptrAt2->getName()==(*itPot)->getName2() && ptrAt3->getName()==(*itPot)->getName3())
            {






                if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt4->getName()==(*itPot)->getName4())
                {
                    (*itDihedral)->setType((*itPot)->getId1());




                    break;

                }else if(ptrAt1->getName()==(*itPot)->getName4() && ptrAt4->getName()==(*itPot)->getName1())
                {
                    (*itDihedral)->setType((*itPot)->getId1());




                     break;
                }

            }else if(ptrAt2->getName()==(*itPot)->getName3() && ptrAt3->getName()==(*itPot)->getName2())
            {




                if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt4->getName()==(*itPot)->getName4())
                {
                    (*itDihedral)->setType((*itPot)->getId1());




                    break;

                }else if(ptrAt1->getName()==(*itPot)->getName4() && ptrAt4->getName()==(*itPot)->getName1())
                {
                    (*itDihedral)->setType((*itPot)->getId1());

                     break;
                }

            }
            //else
            //{
            //    cout<<ptrAt1->getName()<<" a "
            //        <<ptrAt2->getName()<<" "
            //        <<ptrAt3->getName()<<" "
            //        <<ptrAt4->getName()<<" \n pot  "
            //        <<(*itPot)->getName1()<<" "
            //          <<(*itPot)->getName2()<<" "
            //            <<(*itPot)->getName3()<<" "
            //           <<(*itPot)->getName4()<<" "<<(*itPot)->getId1() <<endl;
            //    break;
            //}

        }
    }





    for(itImproper=vecImproper.begin();itImproper!=vecImproper.end();itImproper++)
    {

        ptrAt1=(*itImproper)->getAtom1();
        ptrAt2=(*itImproper)->getAtom2();
        ptrAt3=(*itImproper)->getAtom3();
        ptrAt4=(*itImproper)->getAtom4();




        for(itPot=vecImproperPot.begin();itPot!=vecImproperPot.end();itPot++)
        {


            if(ptrAt2->getName()==(*itPot)->getName2() && ptrAt3->getName()==(*itPot)->getName3())
            {


                if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt4->getName()==(*itPot)->getName4())
                {
                    (*itImproper)->setType((*itPot)->getId1());


                    break;

                }else if(ptrAt1->getName()==(*itPot)->getName4() && ptrAt4->getName()==(*itPot)->getName1())
                {
                    (*itImproper)->setType((*itPot)->getId1());


                     break;
                }

            }else if(ptrAt2->getName()==(*itPot)->getName3() && ptrAt3->getName()==(*itPot)->getName2())
            {




                if(ptrAt1->getName()==(*itPot)->getName1() && ptrAt4->getName()==(*itPot)->getName4())
                {
                    (*itImproper)->setType((*itPot)->getId1());


                    break;

                }else if(ptrAt1->getName()==(*itPot)->getName4() && ptrAt4->getName()==(*itPot)->getName1())
                {
                    (*itImproper)->setType((*itPot)->getId1());


                     break;
                }

            }

        }
    }


    //cout<<vecAtoms.size()<<" types"<<endl;





    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {


        (*itMol)->removeBond(0);
        (*itMol)->removeAngle(0);
        (*itMol)->removeDihedral(0);
        (*itMol)->removeImproper(0);

    }



    update();


}
void isystem::addOPLS()
{
    //opls nonbonded search

    cAtom * ptrAt1,*ptrAt4;




    //int l=0;

    for(itPot=vecDihedralPot.begin();itPot!=vecDihedralPot.end();itPot++)
    {
        if((*itPot)->getId2()>0)
        {

            for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
            {
                vector<cDihederal*> vecDi=(*itMol)->getVecDihedrals();

                for (itDihedral=vecDi.begin();itDihedral!=vecDi.end();itDihedral++)
                {
                    ptrAt1=(*itDihedral)->getAtom1();
                    ptrAt4=(*itDihedral)->getAtom4();



                    if(ptrAt1->getName()==(*itPot)->getName4() && ptrAt4->getName()==(*itPot)->getName1()
                       ||ptrAt1->getName()==(*itPot)->getName1() && ptrAt4->getName()==(*itPot)->getName4())
                    {
                        //cout<<ptrAt1->getName()<<" a "
                        //     <<ptrAt4->getName()<<" \n pot  "
                        //     <<(*itPot)->getName1()<<" "
                        //     <<(*itPot)->getName4()<<" "<<(*itPot)->getId2() <<endl;
                        //l++;

                        (*itMol)->addBond(new cBond((*itPot)->getId2(),ptrAt1,ptrAt4));

                    }

                }
            }
        }


    }

    vecBonds.clear();

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {
        vector<cBond*> vecBn=(*itMol)->getVecBonds();

        for (itBond=vecBn.begin();itBond!=vecBn.end();itBond++)
        {
            vecBonds.push_back(*itBond);
        }
    }




}







