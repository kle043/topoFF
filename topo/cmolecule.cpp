#include "cmolecule.h"

cMolecule::cMolecule(cAtom *at)
{

    visited=false;
    vecAtoms.push_back(at);
    resname=at->getResname();
    mass=at->getMass();
    charge=at->getCharge();





}

cMolecule::cMolecule(cBond *bn)
{
    visited=false;
    mass=0;
    charge=0;
    resname=bn->getAtom1()->getResname();
    addAtom(bn->getAtom1());
    addAtom(bn->getAtom2());




}

void cMolecule::setNetCharge()
{
    charge=0.0;

    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        charge+=(*itAtom)->getCharge();

    }

}

void cMolecule::setResId(int i)
{
    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        (*itAtom)->setResId(i);
    }

}

bool cMolecule::has(int idx)
{
    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        if ((*itAtom)->getIdx()==idx)
        {
            return true;
        }
    }

    return false;

}

int cMolecule::getNAtoms(string name)
{
    int n=0;
    vector<cAtom*>::iterator itAt;
    for (itAt=vecAtoms.begin();itAt!=vecAtoms.end();itAt++)
    {
        if ((*itAt)->getName()==name)
        {
            n++;
        }
    }

    return n;

}

pair<string, int> cMolecule::getNAtomsMax()
{
    pair<string, int> p;
    int natoms;
    string name;
    natoms=0;

    vector<cAtom*>::iterator itAt;


    for (itAt=vecAtoms.begin();itAt!=vecAtoms.end();itAt++)
    {
        name=(*itAt)->getName();
        natoms=getNAtoms(name);



        if (p.second<natoms)
        {


            p.first=name;
            p.second=natoms;


        }


    }


    return p;

}

cBond *cMolecule::getBond(int i)
{
    if(i>vecBonds.size()-1)
    {
        throw invalid_argument( "Index out of bounds in getBondsAt()" );
    }

    return vecBonds.at(i);

}

cAngle *cMolecule::getAngle(int i)
{
    if(i>vecAngles.size()-1)
    {
        throw invalid_argument( "Index out of bounds in getBondsAt()" );
    }

    return vecAngles.at(i);

}

cAtom *cMolecule::getAtom(int idx)
{
    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        if((*itAtom)->getIdx()==idx)
        {
            return (*itAtom);
        }
    }

    return NULL;

}



void cMolecule::addAtom(cAtom *at)
{

    vecAtoms.push_back(at);
    mass+=at->getMass();
    charge+=at->getCharge();

}

void cMolecule::addBond(cBond *bn)
{

    vecBonds.push_back(bn);

    //cout<<bn->getAtom1()->getName()<<" "<<bn->getAtom2()->getName()<<endl;
}

void cMolecule::addImproper(cImproper *im)
{
    vecImpropers.push_back(im);
}

void cMolecule::addDihederal(cDihederal *di)
{
    vecDihedrals.push_back(di);
}



void cMolecule::removeBond(int i)
{

    for (itBond=vecBonds.begin();itBond!=vecBonds.end();)
    {
        if((*itBond)->getType()==i)
        {



           // cout<<(*itBond)->getAtom1()->getName()<<" - "<<(*itBond)->getAtom2()->getName()<<endl;

            delete *itBond;

            itBond=vecBonds.erase(itBond);


        }else itBond++;
    }
}

void cMolecule::removeAngle(int i)
{
    for (itAngle=vecAngles.begin();itAngle!=vecAngles.end();)
    {


        if((*itAngle)->getType()==i)
        {

            delete *itAngle;

            itAngle=vecAngles.erase(itAngle);


        }else itAngle++;
    }

}
void cMolecule::removeDihedral(int i)
{
    for (itDihedral=vecDihedrals.begin();itDihedral!=vecDihedrals.end();)
    {


        if((*itDihedral)->getType()==i)
        {

            delete *itDihedral;
            //cout<<"removing "
            //   <<(*itDihedral)->getAtom1()->getIdx()<<" "
            //   <<(*itDihedral)->getAtom2()->getIdx()<<" "
            //   <<(*itDihedral)->getAtom3()->getIdx()<<" "
            //   <<(*itDihedral)->getAtom4()->getIdx()<<" "
            //   <<endl;

            itDihedral=vecDihedrals.erase(itDihedral);


        }else itDihedral++;
    }

}

void cMolecule::removeImproper(int i)
{
    for (itImproper=vecImpropers.begin();itImproper!=vecImpropers.end();)
    {


        if((*itImproper)->getType()==i)
        {

            delete *itImproper;



            itImproper=vecImpropers.erase(itImproper);


        }else itImproper++;
    }

}

void cMolecule::swapImDi(pair<int,int> ids)
{
    for (itImproper=vecImpropers.begin();itImproper!=vecImpropers.end();itImproper++)
    {

        if((*itImproper)->getType()==ids.first)
        {
            cAtom * ptrAt1=(*itImproper)->getAtom1();
            cAtom * ptrAt2=(*itImproper)->getAtom2();
            cAtom * ptrAt3=(*itImproper)->getAtom3();
            cAtom * ptrAt4=(*itImproper)->getAtom4();

            vecDihedrals.push_back(new cDihederal(ids.second,ptrAt1,ptrAt2,ptrAt3,ptrAt4));
            (*itImproper)->setType(0);

        }

    }
}



void cMolecule::findAngles()
{
    for (itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
    {
        for (itBond2=itBond+1;itBond2!=vecBonds.end();itBond2++)
        {
            if((*itBond)->getIdx1()==(*itBond2)->getIdx1())
            {
                addAngle(new cAngle(0,(*itBond)->getAtom2(),(*itBond)->getAtom1(),(*itBond2)->getAtom2()));

            }else if((*itBond)->getIdx1()==(*itBond2)->getIdx2())
            {
                addAngle(new cAngle(0,(*itBond)->getAtom2(),(*itBond)->getAtom1(),(*itBond2)->getAtom1()));

            }else if((*itBond)->getIdx2()==(*itBond2)->getIdx1())
            {
                addAngle(new cAngle(0,(*itBond)->getAtom1(),(*itBond)->getAtom2(),(*itBond2)->getAtom2()));

            }else if((*itBond)->getIdx2()==(*itBond2)->getIdx2())
            {
                addAngle(new cAngle(0,(*itBond)->getAtom1(),(*itBond)->getAtom2(),(*itBond2)->getAtom1()));
            }

        }

        //cout<<resname<<" "<<mass<<(*itBond)->getAtom1()->getName()<<" "<<(*itBond)->getAtom2()->getName()<<" "<<(*itBond)->getIdx1()<<" "<<(*itBond)->getIdx2()<<endl;
    }

}

void cMolecule::find_1_4()
{

    int idx1=-1;
    int idx2=-1;
    int idx1bn=-1;
    int idx2bn=-1;


    cmeasure measure;

    for (itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
    {
        for (itBond2=itBond+1;itBond2!=vecBonds.end();itBond2++)
        {
            if((*itBond)->hasIdx((*itBond2)->getIdx1()))
            {
                idx2=(*itBond2)->getIdx2();
                idx2bn=(*itBond2)->getIdx1();


            }else if((*itBond)->hasIdx((*itBond2)->getIdx2()) )
            {
                idx2=(*itBond2)->getIdx1();
                idx2bn=(*itBond2)->getIdx2();

            }

            if((*itBond2)->hasIdx((*itBond)->getIdx1()))
            {
                idx1=(*itBond)->getIdx2();
                idx1bn=(*itBond)->getIdx1();


            }else if((*itBond2)->hasIdx((*itBond)->getIdx2()))
            {
                idx1=(*itBond)->getIdx1();
                idx1bn=(*itBond)->getIdx2();

            }

            for (itBond3=itBond2+1;itBond3!=vecBonds.end();itBond3++)
            {
                if((*itBond3)->hasIdx(idx1) && !(*itBond3)->hasIdx(idx2))
                {

                    //is bonded to 1, 1 is central bond



                    cAtom * at1,*at2,*at3,*at4;

                    if((*itBond2)->getAtom1()->getIdx()==idx2)
                    {

                        at1=(*itBond2)->getAtom1();
                        at2=(*itBond2)->getAtom2();
                    }else
                    {
                        at1=(*itBond2)->getAtom2();
                        at2=(*itBond2)->getAtom1();
                    }

                    if((*itBond3)->getAtom1()->getIdx()==idx1)
                    {
                        at3=(*itBond3)->getAtom1();
                        at4=(*itBond3)->getAtom2();
                    }else
                    {
                        at3=(*itBond3)->getAtom2();
                        at4=(*itBond3)->getAtom1();
                    }

                    addDihederal(new cDihederal(0,at1,at2,at3,at4));


                }else if((*itBond3)->hasIdx(idx2) && !(*itBond3)->hasIdx(idx1))
                {

                    //is bonded to 2, 2 is central bond


                    cAtom * at1,*at2,*at3,*at4;
                    if((*itBond)->getAtom1()->getIdx()==idx1)
                    {

                        at1=(*itBond)->getAtom1();
                        at2=(*itBond)->getAtom2();
                    }else
                    {
                        at1=(*itBond)->getAtom2();
                        at2=(*itBond)->getAtom1();
                    }

                    if((*itBond3)->getAtom1()->getIdx()==idx2)
                    {
                        at3=(*itBond3)->getAtom1();
                        at4=(*itBond3)->getAtom2();
                    }else
                    {
                        at3=(*itBond3)->getAtom2();
                        at4=(*itBond3)->getAtom1();
                    }



                    //cout
                    //    <<at1->getName()<<" "
                    //    <<at2->getName()<<" "
                    //    <<at3->getName()<<" "
                    //    <<at4->getName()<<" "<<endl;
                    //cout
                    //    <<at1->getIdx()<<" "
                    //    <<at2->getIdx()<<" "
                    //    <<at3->getIdx()<<" "
                    //    <<at4->getIdx()<<" "<<endl;

                    addDihederal(new cDihederal(0,at1,at2,at3,at4));




                }else if ((*itBond3)->hasIdx(idx2bn))
                {
                    //cout<<" D "<<idx1bn<<" "<<idx2bn<<"  "
                    //<<(*itBond)->getAtom1()->getIdx()<<" "
                    //<<(*itBond)->getAtom2()->getIdx()<<" - "
                    //<<(*itBond2)->getAtom1()->getIdx()<<" "
                    //<<(*itBond2)->getAtom2()->getIdx()<<" - "
                    //<<(*itBond3)->getAtom1()->getIdx()<<" "
                    //<<(*itBond3)->getAtom2()->getIdx()<<" "<<endl;

                    cAtom * at1,*at2,*at3,*at4;

                    if((*itBond)->getAtom1()->getIdx()==idx1bn)
                    {
                        at1=(*itBond)->getAtom2();
                        at2=(*itBond)->getAtom1();

                    }else
                    {
                        at1=(*itBond)->getAtom1();
                        at2=(*itBond)->getAtom2();
                    }

                    if((*itBond2)->getAtom1()->getIdx()==idx1bn)
                    {
                        at3=(*itBond2)->getAtom2();


                    }else
                    {
                        at3=(*itBond2)->getAtom1();


                    }

                    if((*itBond3)->getAtom1()->getIdx()==idx1bn)
                    {

                        at4=(*itBond3)->getAtom2();
                    }else
                    {

                        at4=(*itBond3)->getAtom1();
                    }

                    double angle=measure.getDihedral(at1,at2,at3,at4,0);

                    if(fabs(180-angle)<1.5)
                    {
                        addImproper(new cImproper(0,at1,at2,at3,at4));
                    }

                    //cout
                    //   <<at1->getIdx()<<" "
                    //   <<at2->getIdx()<<" "
                    //   <<at3->getIdx()<<" "
                    //   <<at4->getIdx()<<" "<<angle<<endl;


                }

            }

            idx1=-1;
            idx2=-1;
            idx1bn=-1;
            idx2bn=-1;


        }





    }


}








/*void cMolecule::findImpropers()
{



    for (itAngle=vecAngles.begin();itAngle!=vecAngles.end();itAngle++)
    {
        for (itAngle2=itAngle+1;itAngle2!=vecAngles.end();itAngle2++)
        {


            if((*itAngle)->getIdx1()==(*itAngle2)->getIdx1() )
            {
                if((*itAngle)->getIdx3()!=(*itAngle2)->getIdx3() )
                {


                    cout<<(*itAngle)->getAtom1()->getIdx()<<" a "
                        <<(*itAngle)->getAtom2()->getIdx()<<" "
                        <<(*itAngle)->getAtom3()->getIdx()<<" - ";
                    cout<<(*itAngle2)->getAtom1()->getIdx()<<" "
                        <<(*itAngle2)->getAtom2()->getIdx()<<" "
                        <<(*itAngle2)->getAtom3()->getIdx()<<" - "<<endl;


                   addImproper(new cImproper(0,(*itAngle)->getAtom1(),(*itAngle)->getAtom2(),(*itAngle)->getAtom3(),(*itAngle2)->getAtom3()));


                }


            }else if ((*itAngle)->getIdx3()==(*itAngle2)->getIdx3())
            {
                if((*itAngle)->getIdx1()!=(*itAngle2)->getIdx1() )
                {


                    cout<<(*itAngle)->getAtom1()->getIdx()<<" b "
                        <<(*itAngle)->getAtom2()->getIdx()<<" "
                        <<(*itAngle)->getAtom3()->getIdx()<<" - ";
                    cout<<(*itAngle2)->getAtom1()->getIdx()<<" "
                        <<(*itAngle2)->getAtom2()->getIdx()<<" "
                        <<(*itAngle2)->getAtom3()->getIdx()<<" - "<<endl;


                   addImproper(new cImproper(0,(*itAngle)->getAtom1(),(*itAngle)->getAtom2(),(*itAngle)->getAtom3(),(*itAngle2)->getAtom3()));


                }
            }else if ((*itAngle)->getIdx1()==(*itAngle2)->getIdx3())
            {
                if((*itAngle2)->getIdx1()!=(*itAngle)->getIdx3() )
                {


                    cout<<(*itAngle)->getAtom1()->getIdx()<<" c "
                        <<(*itAngle)->getAtom2()->getIdx()<<" "
                        <<(*itAngle)->getAtom3()->getIdx()<<" - ";
                    cout<<(*itAngle2)->getAtom1()->getIdx()<<" "
                        <<(*itAngle2)->getAtom2()->getIdx()<<" "
                        <<(*itAngle2)->getAtom3()->getIdx()<<" - "<<endl;


                   addImproper(new cImproper(0,(*itAngle)->getAtom1(),(*itAngle)->getAtom2(),(*itAngle)->getAtom3(),(*itAngle2)->getAtom3()));


                }
            }






        }
    }



}*/





