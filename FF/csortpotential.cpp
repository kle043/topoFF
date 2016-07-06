#include "csortpotential.h"
//hei
class pair_mal
{
public:
    pair_mal(int i1,int i2,string n1,string n2):id1(i1),id2(i2),name1(n1),name2(n2){;}
    int id1,id2;
    string name1,name2;
};

class compareId1
{
public:
    bool operator () ( potential *  lhs,potential * rhs) const
    {
        return lhs->getId1() < rhs->getId1();
    }

};
/*class compareIdGroup
{
public:
    bool operator () ( Cgroup::nameId *  lhs,Cgroup::nameId * rhs) const
    {

        return lhs->getId() < rhs->getId();
    }

};*/
class compareSite
{
public:
    bool operator () ( cSite *  lhs, cSite * rhs) const
    {

        return lhs->getIdx() < rhs->getIdx();
    }

};


cSortPotential::cSortPotential()
{
    cout<<"\nWorking on sorting\n";

}

cSortPotential::~cSortPotential()
{
        for (itPotential=vecPa.begin();itPotential!=vecPa.end();itPotential++)
        {
            delete *itPotential;
        }
        for (itPotential=vecBn.begin();itPotential!=vecBn.end();itPotential++)
        {
            delete *itPotential;
        }
        for (itPotential=vecAn.begin();itPotential!=vecAn.end();itPotential++)
        {
            delete *itPotential;
        }
        for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
        {
            delete *itPotential;
        }
        for (itPotential=vecIm.begin();itPotential!=vecIm.end();itPotential++)
        {
            delete *itPotential;
        }



}
void cSortPotential::removePot()
{
    vector<int>::iterator itInt;

    for (itInt=vecRmAt.begin();itInt!=vecRmAt.end();itInt++)
    {
        for (itPotential=vecPa.begin();itPotential!=vecPa.end();)
        {
            if(*itInt==(*itPotential)->getId1())
            {
                delete *itPotential;
                itPotential=vecPa.erase(itPotential);

            }else if(*itInt==(*itPotential)->getId2())
            {
                delete *itPotential;
                itPotential=vecPa.erase(itPotential);

            }else itPotential++;
        }
    }

    for (itInt=vecRmBn.begin();itInt!=vecRmBn.end();itInt++)
    {
        for (itPotential=vecBn.begin();itPotential!=vecBn.end();)
        {
            if(*itInt==(*itPotential)->getId1())
            {
                delete *itPotential;
                itPotential=vecBn.erase(itPotential);

            }else itPotential++;
        }

    }
    int i=1;
    for (itPotential=vecBn.begin();itPotential!=vecBn.end();itPotential++)
    {
        (*itPotential)->setId1(i);
        i++;

    }
    for (itInt=vecRmAn.begin();itInt!=vecRmAn.end();itInt++)
    {
        for (itPotential=vecAn.begin();itPotential!=vecAn.end();)
        {
            if(*itInt==(*itPotential)->getId1())
            {
                delete *itPotential;

                itPotential=vecAn.erase(itPotential);

            }else itPotential++;
        }

    }
    i=1;

    for (itPotential=vecAn.begin();itPotential!=vecAn.end();itPotential++)
    {
        (*itPotential)->setId1(i);
        i++;

    }

    for (itInt=vecRmDi.begin();itInt!=vecRmDi.end();itInt++)
    {
        for (itPotential=vecDi.begin();itPotential!=vecDi.end();)
        {
            if(*itInt==(*itPotential)->getId1())
            {
                delete *itPotential;
                itPotential=vecDi.erase(itPotential);

            }else itPotential++;
        }

    }
    i=1;

    for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
    {
        (*itPotential)->setId1(i);
        i++;

    }
    for (itInt=vecRmIm.begin();itInt!=vecRmIm.end();itInt++)
    {
        for (itPotential=vecIm.begin();itPotential!=vecIm.end();)
        {
            if(*itInt==(*itPotential)->getId1())
            {
                delete *itPotential;
                itPotential=vecIm.erase(itPotential);

            }else itPotential++;
        }

    }
    i=1;
    for (itPotential=vecIm.begin();itPotential!=vecIm.end();itPotential++)
    {
        (*itPotential)->setId1(i);
        i++;

    }
}

void cSortPotential::sortData(readInput &inputData, readFF &ffData, bool op, bool ho)
{
    opls=op;
    hoomd=ho;
    vecRmAt=inputData.getVecRmAtom();
    vecRmBn=inputData.getVecRmBond();
    vecRmAn=inputData.getVecRmAngle();
    vecRmIm=inputData.getVecRmImproper();

    if (inputData.getPairIds().empty())
    {

        throw help("Pair ids not found, returning now");
        //cout<<" \n";
        //return;

    }
    sortGroup(inputData.getPairIds(),ffData.getGroups());
    sortMixing(ffData.getPotential(),inputData.getMixing());
    sortCharges(inputData.getPairIds(),ffData.getAtoms());
    sortPair(inputData.getPairIds(),ffData.getPotential(), inputData.ifii());
    sortFep(inputData.getFepAtoms());
    sortBonds(inputData.getBondIds(),ffData.getBondsInteractions());
    sortAngles(inputData.getAngleIds(),ffData.getAngleInteractions());
    sortDihedrals(inputData.getDihedralIds(),ffData.getDihedralInteractions());
    sortImpropers(inputData.getImproperIds(),ffData.getImproperInteractions());

}

void cSortPotential::sortPair(const vector<input *> &inp, const vector<potential *> &pot, bool ii)
{
    inputVec=inp;
    vecPotential=pot;
    int temp;
    bool check =true;

    potential *ptrPot;

    string testsz="";

    cout<<"\nSorting Pair\n";


    // Add functionality for adding potentials
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {

        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            if ((*itPotential)->getName1()==(*it)->getSiteName())
            {

               (*itPotential)->setId1((*it)->getId());

            }

            if((*itPotential)->getName2()==(*it)->getSiteName())
            {
               (*itPotential)->setId2((*it)->getId());

            }
        }

    }
    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if ((*itPotential)->getId1()>(*itPotential)->getId2())
        {
            temp=(*itPotential)->getId1();
            (*itPotential)->setId1((*itPotential)->getId2());
            (*itPotential)->setId2(temp);

        }
    }
    vector<pair_mal> list;
    vector<pair_mal>::iterator itlist;
    vector<input*>::iterator itInput;


    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        if(ii)
        {
                pair_mal a((*it)->getId(),(*it)->getId(),(*it)->getSiteName(),(*it)->getSiteName());
                list.push_back(a);
        }else
        {


            for (itInput=it;itInput!=inputVec.end();itInput++)
            {
                pair_mal a((*it)->getId(),(*itInput)->getId(),(*it)->getSiteName(),((*itInput)->getSiteName()));
                list.push_back(a);

            }
        }
    }


    for (itlist=list.begin();itlist!=list.end();itlist++)
    {
        check=true;
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            if(itlist->id1==(*itPotential)->getId1()&&itlist->id2==(*itPotential)->getId2())
            {

                //fullPotential.push_back(*itPotential);


                vecPa.push_back(*itPotential);



                check=false;
            }

            if(ii)
            {
                (*itPotential)->emptyStyle();
            }



        }

        if (check)
        {
            ptrPot=new coulLong(itlist->id1,itlist->id2,ii,itlist->name1,itlist->name2);

            vecPa.push_back(ptrPot);

                
               // cout << "Creating new pot"<<endl;

            //if potential does not exists, create new empty

        }

    }

    // Check for equal styles
    string pure=".pure.";
    for (itPotential=vecPa.begin();itPotential!=vecPa.end()-1;)
    {
        //(*itPotential)->printTerminal();
        //cout<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<endl;

        if ((*itPotential)->getId1()==(*(itPotential+1))->getId1()&&(*itPotential)->getId2()==(*(itPotential+1))->getId2())
        {

            std::size_t found =(*itPotential)->getFile().find(pure);

            if (found!=std::string::npos)
            {
                cout<<(*itPotential)->getName1()<<" "<<(*itPotential)->getName2()<<" removed "<<(*itPotential)->getFile()<<endl;
                delete *itPotential;
                itPotential=vecPa.erase(itPotential);

            }else
            {
                cout<<(*(itPotential+1))->getName1()<<" "<<(*(itPotential+1))->getName2()<<" removed "<<(*(itPotential+1))->getFile()<<endl;
                delete *(itPotential+1);
                itPotential=(vecPa.erase(itPotential+1));

            }

        }else itPotential++;
    }

   /* for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        for(itPot2=fullPotential.begin();itPot2!=fullPotential.end();itPot2++)
        {
    cout<<"Hei before"<<endl;
            if((*itPotential)->getName1()==(*itPot2)->getName1()&&(*itPotential)->getName2()==(*itPot2)->getName2())
            {
    cout<<"Hei IF"<<endl;
                potential * newPot=(*itPotential)->clone();
                newPot->setId1((*itPot2)->getId1());
                newPot->setId2((*itPot2)->getId2());
                potential *old =(*itPot2);
                (*itPot2)=newPot;
                delete old;

            }
        }
    cout<<"Hei END"<<endl;

    }*/ // Created for richard to give justed one set of paramaters then copy is to other sites

   // (*(fullPotential.end()-1))->addSpace();




}

void cSortPotential::sortFep(vector<fepAtoms *> vecFep)
{



    vector<Cgroup::nameId*>::iterator itAtoms,itAtoms2;

    for(itFep=vecFep.begin();itFep!=vecFep.end();itFep++)
    {
        vector<Cgroup::nameId*> vecGroup1,vecGroup2;


        for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
        {

           if((*itGroup)->getGroupName()==(*itFep)->getName1())
           {
              // cout <<(*itFep)->getName1()<<" equal\n";
               vecGroup1=(*itGroup)->getGroupNames();
           }

           if((*itGroup)->getGroupName()==(*itFep)->getName2())
           {
               vecGroup2=(*itGroup)->getGroupNames();
               //cout <<(*itFep)->getName2()<<" equal\n";
           }


        }

        if(vecGroup1.empty() || vecGroup2.empty())
        {
            cout<<"Did not find group for fep"<<endl;
        }else
        {

            vector<pair_mal> list;
            vector<pair_mal>::iterator itlist;

            for (itAtoms=vecGroup1.begin();itAtoms!=vecGroup1.end();itAtoms++)
            {
                for (int i=0; i<(*itAtoms)->getVecSize();i++)
                {
                    for (itAtoms2=vecGroup2.begin();itAtoms2!=vecGroup2.end();itAtoms2++)
                    {
                        for (int l=0; l<(*itAtoms2)->getVecSize();l++)
                        {
                            if((*itAtoms)->getId(i)>(*itAtoms2)->getId(l))
                            {
                                pair_mal a((*itAtoms2)->getId(l),(*itAtoms)->getId(i),(*itAtoms2)->getName(),(*itAtoms)->getName());
                                list.push_back(a);

                            }else
                            {
                                pair_mal a((*itAtoms)->getId(i),(*itAtoms2)->getId(l),(*itAtoms)->getName(),(*itAtoms2)->getName());
                                list.push_back(a);

                            }

                        }

                    }

                }

            }






            for (itPotential=fullPotential.begin();itPotential!=fullPotential.end();itPotential++)
            {


                for (itlist=list.begin();itlist!=list.end();itlist++)
                {
                    if(itlist->id1==(*itPotential)->getId1()&&itlist->id2==(*itPotential)->getId2())
                    {


                        (*itPotential)->setStyle((*itPotential)->getStyle()+"/soft");

                        //(*itPotential)->printTerminal();
                        (*itPotential)->setLambda((*itFep)->getLambda());
                        vecFepOut.push_back(*itPotential);


                        //cout<<itlist->id1<<" "<<itlist->id2<<" "<<itlist->name1<<" "<<itlist->name2<<endl;
                    }
                }




            }
        }

    }


 //   for (itAtoms=vecAtomsName->begin();itAtoms!=vecAtomsName->end();itAtoms++)
 //   {
 //       for (int i=0; i<(*itAtoms)->getVecSize();i++)
 //       {
 //           cout<<" "<<left<<(*itAtoms)->getId(i)<<" ";
 //       }
 //
 //   }

    cout<<endl;

}
void cSortPotential::sortBonds(const vector<input *> &inp, const vector<potential *> &pot)
{
    inputVec=inp;
    vecPotential=pot;
    if(inputVec.empty()&&vecPotential.empty())
    {
        return;
    }


    bool pureStyle=true;
    if(inputVec.empty()&&vecPotential.empty())
    {
        return;
    }

    string style=(*vecPotential.begin())->getStyle();
    bool check;
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        check=true;
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            if(*((*it)->getBondAtoms())==(*itPotential)->getName1()&&*((*it)->getBondAtoms()+1)==(*itPotential)->getName2())
            {
                (*itPotential)->setId1((*it)->getId());
                check=false;

            }else if(*((*it)->getBondAtoms())==(*itPotential)->getName2()&&*((*it)->getBondAtoms()+1)==(*itPotential)->getName1())
            {
                (*itPotential)->setId1((*it)->getId());
                check=false;

            }



        }
        if (check)
        {
            //if potential does not exists, create new empty
            vecPotential.push_back(new harmonic_bond((*it)->getId(),*((*it)->getBondAtoms()),*((*it)->getBondAtoms()+1),0,0,"kj","Missing"));

        }

    }

    for (itPotential=vecPotential.begin()+1;itPotential!=vecPotential.end();itPotential++)
    {
        if (style!=(*itPotential)->getStyle())
        {
            pureStyle=false;
            break;
        }
    }

    if(pureStyle &&!hoomd)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }


    sort(vecPotential.begin(),vecPotential.end(),compareId1());

    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            //fullPotential.push_back(*itPotential);


            vecBn.push_back(*itPotential);

        }if((*itPotential)->getId1()==0)
        {
            vecBn.push_back(*itPotential);
            vecRmBn.push_back((*itPotential)->getId1());
        }
    }

}

void cSortPotential::sortAngles(const vector<input *> &inp, const vector<potential *> &pot)
{
    inputVec=inp;
    vecPotential=pot;
    if(inputVec.empty()&&vecPotential.empty())
    {
        return;
    }
    bool check;
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        check=true;
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            if (*((*it)->getAngleAtoms()+1)==(*itPotential)->getName2())
            {
                if(*((*it)->getAngleAtoms())==(*itPotential)->getName1()&&*((*it)->getAngleAtoms()+2)==(*itPotential)->getName3())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }else if(*((*it)->getAngleAtoms())==(*itPotential)->getName3()&&*((*it)->getAngleAtoms()+2)==(*itPotential)->getName1())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }
            }



        }
        if (check)
        {
            //if potential does not exists, create new empty
            vecPotential.push_back(new harmonic_angle((*it)->getId(),*((*it)->getAngleAtoms()),*((*it)->getAngleAtoms()+1),*((*it)->getAngleAtoms()+2),0,0,"kj","Missing"));

        }

    }

    sort(vecPotential.begin(),vecPotential.end(),compareId1());

    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {

            //fullPotential.push_back(*itPotential);


            vecAn.push_back(*itPotential);

        }
    }


}
void cSortPotential::sortDihedrals(const vector<input *> &inp, const vector<potential *> &pot)
{
    inputVec=inp;
    vecPotential=pot;
    bool pureStyle=true;
    if(inputVec.empty()&&vecPotential.empty())
    {
        return;
    }

    string style=(*vecPotential.begin())->getStyle();

    //cout<<style<<endl;


    bool check;
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        check=true;
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {

           // cout<<*((*it)->getImproperAtoms ()+1)<<" "<<(*itPotential)->getName2()<<" p "
             //   <<*((*it)->getImproperAtoms ()+2)<<" "<<(*itPotential)->getName3()<<" \n";

            if ((*((*it)->getDihedralAtoms ()+1)==(*itPotential)->getName2()&&*((*it)->getDihedralAtoms ()+2)==(*itPotential)->getName3())||(*((*it)->getDihedralAtoms ()+1)==(*itPotential)->getName3()&&*((*it)->getDihedralAtoms ()+2)==(*itPotential)->getName2()))
            {

                if(*((*it)->getDihedralAtoms ())==(*itPotential)->getName1()&&*((*it)->getDihedralAtoms ()+3)==(*itPotential)->getName4())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }else if(*((*it)->getDihedralAtoms ())==(*itPotential)->getName4()&&*((*it)->getDihedralAtoms ()+3)==(*itPotential)->getName1())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }
            }





        }

        if (check)
        {
            //if potential does not exists, create new empty
            cout <<"Creating new dihedral\n";
            vecPotential.push_back(new harmonic_dihedral((*it)->getId(),*((*it)->getDihedralAtoms ()),*((*it)->getDihedralAtoms ()+1),*((*it)->getDihedralAtoms ()+2),*((*it)->getDihedralAtoms ()+3),0.0,0.0,0.0,"kj","Missing"));

        }

    }
    for (itPotential=vecPotential.begin()+1;itPotential!=vecPotential.end();itPotential++)
    {
        if (style!=(*itPotential)->getStyle())
        {
            pureStyle=false;
            break;
        }
    }

    if(pureStyle&&!hoomd)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }

    sort(vecPotential.begin(),vecPotential.end(),compareId1());

    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {

        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            //fullPotential.push_back(*itPotential);



            vecDi.push_back(*itPotential);

        }
    }

    int l=0;

    if(opls)
    {
        int id=(*(vecBn.end()-1))->getId1()+1;
        for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
        {
            for(itPot2=vecPa.begin();itPot2!=vecPa.end();itPot2++)
            {
                if((*itPotential)->getName1()==(*itPot2)->getName1() &&  (*itPotential)->getName4()==(*itPot2)->getName2()
                   || (*itPotential)->getName1()==(*itPot2)->getName2() &&  (*itPotential)->getName4()==(*itPot2)->getName1())
                {
                   //cout<< (*itPotential)->getId1()<<" - "<<(*itPotential)->getId2()<<endl;
                    //cout<< (*itPot2)->getName1()<<" - "<<(*itPot2)->getName2()<<endl;

                    (*itPotential)->setId2(id);


                    vector<double> vecD=(*itPot2)->getParameters();

                    //cout<<id<<" "<<vecD.at(0)<<" "<<vecD.at(1)<<endl;

                    if(vecD.size()==2)
                    {
                        (*itPotential)->addParameter(vecD.at(0));
                         (*itPotential)->addParameter(vecD.at(1));

                    }else
                    {
                        cout<<"ERROR: creating 1-4 nonbonded from dihederal\n";
                    }

                    id++;
                    l++;


                }
            }



            //(*itPotential)->printTerminal();
        }
        //cout<<id<<endl;
    }

    //cout<<"llll "<< l<<endl;


    //cout<<"Sort di "<<vecDi.size()<<endl;


}

void cSortPotential::sortImpropers(const vector<input *> &inp, const vector<potential *> &pot)
{


    inputVec=inp;
    vecPotential=pot;
    bool pureStyle=true;
    if(inputVec.empty()&&vecPotential.empty())
    {
        return;
    }

    string style=(*vecPotential.begin())->getStyle();



    bool check;
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        check=true;
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {

           // cout<<*((*it)->getImproperAtoms ()+1)<<" "<<(*itPotential)->getName2()<<" p "
            //    <<*((*it)->getImproperAtoms ()+2)<<" "<<(*itPotential)->getName3()<<" \n";

            if ((*((*it)->getImproperAtoms ()+1)==(*itPotential)->getName2()&&*((*it)->getImproperAtoms ()+2)==(*itPotential)->getName3())||(*((*it)->getImproperAtoms ()+1)==(*itPotential)->getName3()&&*((*it)->getImproperAtoms ()+2)==(*itPotential)->getName2()))
            {

                if(*((*it)->getImproperAtoms ())==(*itPotential)->getName1()&&*((*it)->getImproperAtoms ()+3)==(*itPotential)->getName4())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }else if(*((*it)->getImproperAtoms ())==(*itPotential)->getName4()&&*((*it)->getImproperAtoms ()+3)==(*itPotential)->getName1())
                {
                    (*itPotential)->setId1((*it)->getId());
                    check=false;

                }
            }





        }

        if (check)
        {
            //if potential does not exists, create new empty
            //cout <<"Creating new improper\n";
            vecPotential.push_back(new harmonic_improper((*it)->getId(),*((*it)->getImproperAtoms ()),*((*it)->getImproperAtoms ()+1),*((*it)->getImproperAtoms ()+2),*((*it)->getImproperAtoms ()+3),0.0,0.0,"kj","Missing"));

        }

    }
    for (itPotential=vecPotential.begin()+1;itPotential!=vecPotential.end();itPotential++)
    {
        if (style!=(*itPotential)->getStyle())
        {
            pureStyle=false;
            break;
        }
    }

    if(pureStyle&&!hoomd)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }

    sort(vecPotential.begin(),vecPotential.end(),compareId1());

    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {

        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            //fullPotential.push_back(*itPotential);           

            vecIm.push_back(*itPotential);

        }
    }

}

void cSortPotential::sortGroup(const vector<input *> &inp,const vector<Cgroup *> &grp)
{
    inputVec=inp;
    vecGroup=grp;
    vector<Cgroup::nameId*>::iterator itAtoms;


    for (it=inputVec.begin();it!=inputVec.end();it++)
    {


        for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
        {
            vector<Cgroup::nameId*>* vecAtomsName=&(*itGroup)->getGroupNames();

           // cout<< (*itGroup)->getGroupName()<<endl;

            for (itAtoms=vecAtomsName->begin();itAtoms!=vecAtomsName->end();itAtoms++)
            {
                if ((*it)->getSiteName()==(*itAtoms)->getName())
                {
                   // cout <<(*it)->getId()<<" "<<(*it)->getSiteName()<< " "<<(*itGroup)->getGroupName()<<endl;
                    (*itAtoms)->setId((*it)->getId());
                }


            }


        }
    }

   /* for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
    {
        vector<Cgroup::nameId*>* vecAtomsName=&(*itGroup)->getGroupAtoms();

        sort(vecAtomsName->begin(),vecAtomsName->end(),compareIdGroup());
    }*/

}

void cSortPotential::sortCharges(const vector<input *> &inp, vector<cSite *> &atm)
{
    inputVec=inp;


    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        //cout <<"Charge "<<(*it)->getSiteName()<<endl;
        for (itSite=atm.begin();itSite!=atm.end();itSite++)
        {
            if((*itSite)->getName()==(*it)->getSiteName())
            {
               // cout << (*itSite)->getName()<<" "<< (*it)->getNameSite()<<endl;
                if((*itSite)->getIdx()<0)
                {
                    (*itSite)->setIdx((*it)->getId());
                    vecSite.push_back(*itSite);
                }else
                {
                    cSite * newSite=new cSite((*it)->getSiteName(),(*itSite)->getCharge());
                    newSite->setIdx((*it)->getId());
                    vecSiteCopy.push_back(newSite);
                }
                break;
            }
        }
    }

    for (itSite=vecSiteCopy.begin();itSite!=vecSiteCopy.end();itSite++)
    {
        vecSite.push_back(*itSite);
    }


    sort(vecSite.begin(),vecSite.end(),compareSite());


}

void cSortPotential::sortMixing(vector<potential *> &vecPot, vector<cmixAtoms *> &vecMixAt)
{


    vector<cmixAtoms *>::iterator itMix;
    vector<cmixAtoms *> vecMixAt_Sorted;
    bool name1;
    bool name2;
    vector<Cgroup::nameId*>* vecAtomsName1;
    vector<Cgroup::nameId*>* vecAtomsName2;
    vector<Cgroup::nameId*>::iterator itAtoms1;
    vector<Cgroup::nameId*>::iterator itAtoms2;
    string gName1, gName2;


    for (itMix=vecMixAt.begin();itMix!=vecMixAt.end();itMix++)
    {
        name1=false;
        name2=false;
        for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
        {

            if((*itGroup)->getGroupName()==(*itMix)->getName1())
            {
                //cout<<(*itGroup)->getGroupName()<<" "<<(*itMix)->getName1()<<endl;
                gName1=(*itGroup)->getGroupName();
                name1=true;
                vecAtomsName1=&(*itGroup)->getGroupNames();

            }
            if((*itGroup)->getGroupName()==(*itMix)->getName2())
            {

                gName2=(*itGroup)->getGroupName();
                name2=true;
                vecAtomsName2=&(*itGroup)->getGroupNames();

            }

        }

        if(name1 && name2)
        {

            bool equalSel=false;
            int count=0;



            if(vecAtomsName1->at(0)==vecAtomsName2->at(0))
            {
                equalSel=true;


            }

            for (itAtoms1=vecAtomsName1->begin();itAtoms1!=vecAtomsName1->end();itAtoms1++)
            {
                if(equalSel)
                {
                    count++;
                }

                for (itAtoms2=vecAtomsName2->begin()+count;itAtoms2!=vecAtomsName2->end();itAtoms2++)
                {
                    if((*itAtoms1)->getName()!=(*itAtoms2)->getName())
                    {

                        vecMixAt_Sorted.push_back(new cmixAtoms((*itAtoms1)->getName(),(*itAtoms2)->getName(),(*itMix)->getMixing()));

                        cout<<"Mix from group "<<gName1<<" "<<gName2<<" "<<(*itAtoms1)->getName()<<" "<<(*itAtoms2)->getName()<<endl;

                    }
                }

            }





        }else if(name1)
        {
            for (itAtoms1=vecAtomsName1->begin();itAtoms1!=vecAtomsName1->end();itAtoms1++)
            {
                vecMixAt_Sorted.push_back(new cmixAtoms((*itAtoms1)->getName(),(*itMix)->getName2(),(*itMix)->getMixing()));
            }

        }else if(name2)
        {
            for (itAtoms2=vecAtomsName2->begin();itAtoms2!=vecAtomsName2->end();itAtoms2++)
            {
                vecMixAt_Sorted.push_back(new cmixAtoms((*itAtoms2)->getName(),(*itMix)->getName1(),(*itMix)->getMixing()));
            }

        }else
        {
            vecMixAt_Sorted.push_back(*itMix);
        }
    }

    vecMixAt.clear();

    for (itMix=vecMixAt_Sorted.begin();itMix!=vecMixAt_Sorted.end();itMix++)
    {
        vecMixAt.push_back(*itMix); // move objects over to vecMix located in readinput where destructor is;

    }



    Cmix mix;
    mix.performMixing(vecPot,vecMixAt_Sorted);
}

void cSortPotential::printToFile(string s)
{

}

double cSortPotential::getCharge(string name)
{
    for (itSite=vecSite.begin();itSite!=vecSite.end();itSite++)
    {
        if((*itSite)->getName()==name)
        {
            return (*itSite)->getCharge();
        }
    }
    return 0.0;
}

void cSortPotential::goHOOMD(string s)
{






}

vector<pair<int, int> > cSortPotential::getVecSwapImDi()
{
    vector<pair<int,int> > vecIds;
    int newId=vecDi.size()+1;
    pair<int,int> newP;

    for (itPotential=vecIm.begin();itPotential!=vecIm.end();itPotential++)
    {
        if((*itPotential)->getStyle()=="cvff" && hoomd)
        {
            newP.first=(*itPotential)->getId1();
            newP.second=newId;
            vecIds.push_back(newP);
            (*itPotential)->setId1(newId);
            newId++;
        }
    }

    return vecIds;

}






