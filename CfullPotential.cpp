#include "CfullPotential.h"
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
class compareAtom
{
public:
    bool operator () ( atom *  lhs, atom * rhs) const
    {

        return lhs->getId() < rhs->getId();
    }

};


CfullPotential::CfullPotential()
{
    cout<<"\nWorking on sorting\n";

}

CfullPotential::~CfullPotential()
{
        for (itPotential=fullPotential.begin();itPotential!=fullPotential.end();itPotential++)
        {
            delete *itPotential;
        }

}

void CfullPotential::sortPair(const vector<input *> &inp, const vector<potential *> &pot, bool ii)
{
    inputVec=inp;
    vecPotential=pot;
    int temp;
    bool check =true;

    string testsz="";




    // Add functionality for adding potentials
    for (it=inputVec.begin();it!=inputVec.end();it++)
    {

        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            if ((*itPotential)->getName1()==(*it)->getNameAtom())
            {

               (*itPotential)->setId1((*it)->getId());

            }

            if((*itPotential)->getName2()==(*it)->getNameAtom())
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
                pair_mal a((*it)->getId(),(*it)->getId(),(*it)->getNameAtom(),(*it)->getNameAtom());
                list.push_back(a);
        }else
        {


            for (itInput=it;itInput!=inputVec.end();itInput++)
            {
                pair_mal a((*it)->getId(),(*itInput)->getId(),(*it)->getNameAtom(),((*itInput)->getNameAtom()));
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

                fullPotential.push_back(*itPotential);
                check=false;
            }

            if(ii)
            {
                (*itPotential)->emptyStyle();
            }



        }

        if (check)
        {
                fullPotential.push_back(new coulLong(itlist->id1,itlist->id2,ii,itlist->name1,itlist->name2));
               // cout << "Creating new pot"<<endl;

            //if potential does not exists, create new empty

        }

    }

    // Check for equal styles
    string pure=".pure.";
    for (itPotential=fullPotential.begin();itPotential!=fullPotential.end()-1;)
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
                itPotential=fullPotential.erase(itPotential);

            }else
            {
                cout<<(*(itPotential+1))->getName1()<<" "<<(*(itPotential+1))->getName2()<<" removed "<<(*(itPotential+1))->getFile()<<endl;
                delete *(itPotential+1);
                itPotential=(fullPotential.erase(itPotential+1));

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

    (*(fullPotential.end()-1))->addSpace();




}

void CfullPotential::sortFep(vector<fepAtoms *> vecFep)
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
               vecGroup1=(*itGroup)->getGroupAtoms();
           }

           if((*itGroup)->getGroupName()==(*itFep)->getName2())
           {
               vecGroup2=(*itGroup)->getGroupAtoms();
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
void CfullPotential::sortBonds(const vector<input *> &inp, const vector<potential *> &pot)
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

    if(pureStyle)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }


    sort(vecPotential.begin(),vecPotential.end(),compareId1());
    (*(vecPotential.end()-1))->addSpace();
    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            fullPotential.push_back(*itPotential);
        }
    }

}

void CfullPotential::sortAngles(const vector<input *> &inp, const vector<potential *> &pot)
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
    (*(vecPotential.end()-1))->addSpace();
    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {

            fullPotential.push_back(*itPotential);
        }
    }


}
void CfullPotential::sortDihedrals(const vector<input *> &inp, const vector<potential *> &pot)
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

    if(pureStyle)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }

    sort(vecPotential.begin(),vecPotential.end(),compareId1());
    (*(vecPotential.end()-1))->addSpace();
    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            fullPotential.push_back(*itPotential);
        }
    }


}

void CfullPotential::sortImpropers(const vector<input *> &inp, const vector<potential *> &pot)
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

    if(pureStyle)
    {
        for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
        {
            (*itPotential)->setStyle("");
        }
    }

    sort(vecPotential.begin(),vecPotential.end(),compareId1());
    (*(vecPotential.end()-1))->addSpace();
    for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        if((*itPotential)->getId1()>0) // remove non active potentials
        {
            fullPotential.push_back(*itPotential);
        }
    }

}

void CfullPotential::sortGroup(const vector<input *> &inp,const vector<Cgroup *> &grp)
{
    inputVec=inp;
    vecGroup=grp;
    vector<Cgroup::nameId*>::iterator itAtoms;


    for (it=inputVec.begin();it!=inputVec.end();it++)
    {


        for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
        {
            vector<Cgroup::nameId*>* vecAtomsName=&(*itGroup)->getGroupAtoms();

           // cout<< (*itGroup)->getGroupName()<<endl;

            for (itAtoms=vecAtomsName->begin();itAtoms!=vecAtomsName->end();itAtoms++)
            {
                if ((*it)->getNameAtom()==(*itAtoms)->getName())
                {
                   // cout <<(*it)->getId()<<" "<<(*it)->getNameAtom()<< " "<<(*itGroup)->getGroupName()<<endl;
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

void CfullPotential::sortCharges(const vector<input *> &inp, const vector<atom *> &atm)
{
    inputVec=inp;
    vecAtom=atm;

    for (it=inputVec.begin();it!=inputVec.end();it++)
    {
        //cout <<"Charge "<<(*it)->getNameAtom()<<endl;
        for (itAtom=vecAtom.begin();itAtom!=vecAtom.end();itAtom++)
        {
            if((*itAtom)->getName()==(*it)->getNameAtom())
            {
               // cout << (*itAtom)->getName()<<" "<< (*it)->getNameAtom()<<endl;
                if((*itAtom)->getId()<0)
                {
                    (*itAtom)->setId((*it)->getId());
                }else
                {
                    atom * newAtom=new atom((*it)->getNameAtom(),(*itAtom)->getCharge());
                    newAtom->setId((*it)->getId());
                    vecAtomCopy.push_back(newAtom);
                }
                break;
            }
        }
    }

    for (itAtom=vecAtomCopy.begin();itAtom!=vecAtomCopy.end();itAtom++)
    {
        vecAtom.push_back(*itAtom);
    }


    sort(vecAtom.begin(),vecAtom.end(),compareAtom());

    (*(vecAtom.end()-1))->addSpace();
}

void CfullPotential::printToFile(string s)
{
    string::iterator itSz;
    for (itSz=s.begin();itSz!=s.end();itSz++)
    {
        if(*itSz=='.')
        {
            s.erase(itSz,s.end());
            break;
        }
    }

    filename=s+".fflammps";
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        cout<<cwd<<endl;
    }else
    {
        cout << "Could not print output\n";
        return;
    }
    path=cwd;
    path=path+"/";

    location=path+filename;
    outfile.open(location.c_str());
    outfile.precision(8);
    outfile.width(4);
    for (itPotential=fullPotential.begin();itPotential!=fullPotential.end();itPotential++)
    {

        (*itPotential)->print(outfile);
        //(*itPotential)->printTerminal();



    }

    for (itAtom=vecAtom.begin();itAtom!=vecAtom.end();itAtom++)
    {
        (*itAtom)->print(outfile);
    }
    for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
    {
        (*itGroup)->print(outfile);
    }

    outfile.close();

    if(!vecFepOut.empty())
    {



        location=path+"/"+s+".fep";

        outfile.open(location.c_str());
        outfile<<"fix fADAPT all adapt/fep ${fepSteps} pair ";


        if((*vecFepOut.begin())->getLambda()==0.0)
        {
            outfile<<(*vecFepOut.begin())->getStyle()<<" lambda "<<(*vecFepOut.begin())->getId1()<<" "<<(*vecFepOut.begin())->getId2()<<" v_lambda &";
        }else
        {
            outfile<<(*vecFepOut.begin())->getStyle()<<" lambda "<<(*vecFepOut.begin())->getId1()<<" "<<(*vecFepOut.begin())->getId2()<<" v_down &";

        }
        outfile<<endl;

        for (itPotential=vecFepOut.begin()+1;itPotential!=vecFepOut.end()-1;itPotential++)
        {
            if((*itPotential)->getLambda()==0.0)
            {
                outfile<<setw(42)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_lambda &";
            }else
            {
                outfile<<setw(42)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_down &";

            }

            outfile<<endl;

        }

        if((*(vecFepOut.end()-1))->getLambda()==0.0)
        {
            outfile<<setw(42)<<right<<"pair "<<(*(vecFepOut.end()-1))->getStyle()<<" lambda "<<(*(vecFepOut.end()-1))->getId1()<<" "<<(*(vecFepOut.end()-1))->getId2()<<" v_lambda after yes #";

        }else
        {
            outfile<<setw(42)<<right<<"pair "<<(*(vecFepOut.end()-1))->getStyle()<<" lambda "<<(*(vecFepOut.end()-1))->getId1()<<" "<<(*(vecFepOut.end()-1))->getId2()<<" v_down after yes #";

        }


        outfile<<"\n\n";

        outfile<<"variable dlambda equal v_fepSteps/v_runtime\n";
        outfile<<"variable dDown equal -v_dlambda\n\n";

        outfile<<"compute cFEP all fep ${T_start} pair ";
        if((*vecFepOut.begin())->getLambda()==0.0)
        {
            outfile<< (*vecFepOut.begin())->getStyle()<<" lambda "<<(*vecFepOut.begin())->getId1()<<" "<<(*vecFepOut.begin())->getId2()<<" v_dlambda &";

        }else
        {
            outfile<< (*vecFepOut.begin())->getStyle()<<" lambda "<<(*vecFepOut.begin())->getId1()<<" "<<(*vecFepOut.begin())->getId2()<<" v_dDown &";

        }

        outfile<<endl;

        for (itPotential=vecFepOut.begin()+1;itPotential!=vecFepOut.end()-1;itPotential++)
        {
            if((*itPotential)->getLambda()==0.0)
            {
                outfile<<setw(37)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_dlambda &";

            }else
            {
                outfile<<setw(37)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_dDown &";

            }

            outfile<<endl;

        }

        if((*(vecFepOut.end()-1))->getLambda()==0.0)
        {
            outfile<<setw(37)<<right<<"pair "<<(*(vecFepOut.end()-1))->getStyle()<<" lambda "<<(*(vecFepOut.end()-1))->getId1()<<" "<<(*(vecFepOut.end()-1))->getId2()<<" v_dlambda volume yes #";

        }else
        {
            outfile<<setw(37)<<right<<"pair "<<(*(vecFepOut.end()-1))->getStyle()<<" lambda "<<(*(vecFepOut.end()-1))->getId1()<<" "<<(*(vecFepOut.end()-1))->getId2()<<" v_dDown volume yes #";

        }


        outfile<<"\n\n";



        outfile.close();
    }




    cout<<"FINISHED:: Look in "<<filename<<endl;
}
