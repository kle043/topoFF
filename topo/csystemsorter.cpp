#include "csystemsorter.h"

cSystemSorter::cSystemSorter(csystem * sys1)
{


    sys=sys1;
    vecAtoms=sys->getAtoms();
    vecBonds=sys->getBonds();
    vecAngles=sys->getAngles();
    vecImproper=sys->getImpropers();
    vecMolecule=sys->getVecMol();

}

cSystemSorter::~cSystemSorter()
{


}

void cSystemSorter::sortOnDistance(cSortPotential *inp1)
{

    inp=inp1;
    cout<<"Starting distance search on pdb data\n";


    vecBondPot=inp->getBondPot();




    pbcx=sys->getPbcX();
    pbcy=sys->getPbcY();
    pbcz=sys->getPbcZ();

    for (itBondPot=vecBondPot.begin();itBondPot!=vecBondPot.end();itBondPot++)
    {
        type=1;
       // cout<<(*itBondPot)->getName1()<<" "<<(*itBondPot)->getName2()<<endl;

        string szSel1="name "+(*itBondPot)->getName1();
        string szSel2="name "+(*itBondPot)->getName2();

        cselection s1,s2;

        try
        {

            s1(sys,szSel1);
            s2(sys,szSel2);

        }catch(invalid_argument & e)
        {
            std::cerr << "Invalid argument: " << e.what() << '\n';
        }

        //cout<<s1.num()<<" "<<s2.num()<<endl;


        searchBonds(s1,s2,(*itBondPot)->getDistParam());


        szSel1="";
        szSel2="";

    }






}



void cSystemSorter::searchBonds(cselection & sel1, cselection &sel2,double bond)
{


        ccoordinates * coord1,*coord2;


        vecAtom1=sel1.getAtoms();
        vecAtom2=sel2.getAtoms();

        bool equalSel=false;
        int count=0;

        if (vecAtom1.at(0)->getName()==vecAtom2.at(0)->getName())
        {
            //cout<<" Name "<<vecAtom1.at(0)->getName()<<" "<<vecAtom2.at(0)->getName()<<endl;
            equalSel=true;
        }

        for (itAt1=vecAtom1.begin();itAt1!=vecAtom1.end();itAt1++)
        {

            coord1=(*itAt1)->getCoordinates(0);



            if(equalSel)
            {
                count++;
            }

            for (itAt2=vecAtom2.begin()+count;itAt2!=vecAtom2.end();itAt2++)
            {
               double mbond=measure.getBond(*itAt2,*itAt1,0);

               coord2=(*itAt2)->getCoordinates(0);

               if (fabs(mbond-bond)<0.2)
               {

                   //cout<<(*itAt1)->getName()<<" - "<<(*itAt2)->getName()<<mbond<<" "<<bond<<" "<<count<<endl;

                   sys->addBond(type,(*itAt1)->getIdx(),(*itAt2)->getIdx());




               }else if (sys->getPbcX()-fabs(coord1->getX()-coord2->getX())<bond+0.25)
               {
                   if(coord1->getX()<coord2->getX())
                   {

                       mbond=measure.getBondPBC(*itAt1,*itAt2,0,pbcx,0,0);
                   }else
                   {
                       mbond=measure.getBondPBC(*itAt2,*itAt1,0,pbcx,0,0);

                   }

                   if (fabs(mbond-bond)<0.2)
                   {
                       //cout<<(*itPot)->getName1()<<" - "<<(*itPot)->getName2()<<mbond<<" "<<bond<<endl;

                       //coord1->printCoordinates();
                       //coord2->printCoordinates();

                       //vecBond.push_back(cBond(type,(*itAt1),(*itAt2)));

                        sys->addBond(type,(*itAt1)->getIdx(),(*itAt2)->getIdx());

                   }



               }else if (sys->getPbcY()-fabs(coord1->getY()-coord2->getY())<bond+0.25)
               {
                   if(coord1->getY()<coord2->getY())
                   {
                       mbond=measure.getBondPBC(*itAt1,*itAt2,0,0,pbcy,0);
                   }else
                   {
                       mbond=measure.getBondPBC(*itAt2,*itAt1,0,0,pbcy,0);

                   }
                   if (fabs(mbond-bond)<0.2)
                   {
                      // cout<<(*itPot)->getName1()<<" - "<<(*itPot)->getName2()<<mbond<<" "<<bond<<endl;

                       sys->addBond(type,(*itAt1)->getIdx(),(*itAt2)->getIdx());
                       //vecBond.push_back(cBond(type,(*itAt1),(*itAt2)));

                   }
               }else if (sys->getPbcZ()-fabs(coord1->getZ()-coord2->getZ())<bond+0.2)
               {
                   if(coord1->getZ()<coord2->getZ())
                   {
                       mbond=measure.getBondPBC(*itAt1,*itAt2,0,0,0,pbcz);
                   }else
                   {
                       mbond=measure.getBondPBC(*itAt2,*itAt1,0,0,0,pbcz);

                   }
                   if (fabs(mbond-bond)<0.2)
                   {
                      // cout<<(*itPot)->getName1()<<" - "<<(*itPot)->getName2()<<mbond<<" "<<bond<<endl;

                       sys->addBond(type,(*itAt1)->getIdx(),(*itAt2)->getIdx());
                       //vecBond.push_back(cBond(type,(*itAt1),(*itAt2)));

                   }
               }


            }
        }

        type++;


}

void cSystemSorter::findMolecules()
{
    vector<cBond*> vecBn=sys->getBonds();




    stack<cAtom*> stackAt;

    cAtom *ptrAtom;

    cMolecule *ptrMol;



    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {

        if(!(*itAtom)->getVisited())
        {
            ptrMol=new cMolecule(*itAtom);
            sys->addMolecule(ptrMol);
            (*itAtom)->setVisited();

         stackAt.push(*itAtom);

         while(!stackAt.empty())
         {
            ptrAtom=stackAt.top();
            stackAt.pop();



              //cout<<ptrAtom->getName()<<" stack\n";


            for (itBond=vecBn.begin();itBond!=vecBn.end();)
            {




                   if(ptrAtom->getIdx()==(*itBond)->getIdx1())
                   {

                       ptrMol->addBond(*itBond);




                       if(!ptrMol->has((*itBond)->getIdx2()))
                       {
                           ptrMol->addAtom((*itBond)->getAtom2());
                           (*itBond)->getAtom2()->setVisited();
                           stackAt.push((*itBond)->getAtom2());


                       }

                       itBond=vecBn.erase(itBond);


                   }else if(ptrAtom->getIdx()==(*itBond)->getIdx2())
                   {
                       ptrMol->addBond(*itBond);




                       if(!ptrMol->has((*itBond)->getIdx1()))
                       {
                           ptrMol->addAtom((*itBond)->getAtom1());
                           (*itBond)->getAtom1()->setVisited();
                           stackAt.push((*itBond)->getAtom1());

                       }

                       itBond=vecBn.erase(itBond);


                   }else itBond++;

            }


         }



         ptrMol->findAngles();
         ptrMol->find_1_4();



        }

    }

    int i=1;

    vecMolecule=sys->getVecMol();

    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        (*itAtom)->unSetVisited();
    }

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        (*itMol)->setResId(i);

        i++;
    }












}

void cSystemSorter::updateAngles()
{


    vecMolecule=sys->getVecMol();

    for (itMol=vecMolecule.begin();itMol!=vecMolecule.end();itMol++)
    {

        vector<cAngle*> vecAng=(*itMol)->getVecAngles();



        for (itAngle=vecAng.begin();itAngle!=vecAng.end();itAngle++)
        {
            sys->addAngle(*itAngle);
        }

        vector<cDihederal*> vecDi=(*itMol)->getVecDihedrals();

        for (itDihedral=vecDi.begin();itDihedral!=vecDi.end();itDihedral++)
        {
            sys->addDihedral(*itDihedral);
        }


        vector<cImproper*> vecIm=(*itMol)->getVecImpropers();

        for (itImproper=vecIm.begin();itImproper!=vecIm.end();itImproper++)
        {
            sys->addImproper(*itImproper);
        }
    }

}



