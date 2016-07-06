#include "mix.h"


void Cmix::performMixing(vector<potential *> &vecPotential, vector<cmixAtoms*> &vecId)
{
    potential * temp1,*temp2;
    for(itCmix=vecId.begin();itCmix!=vecId.end();itCmix++)
    {
        bool check1=true;
        bool check2=true;

        //cout <<(*itCmix)->getName1()<<" "<<(*itCmix)->getName2()<<endl;

        for (itPot=vecPotential.begin();itPot!=vecPotential.end();itPot++)
        {
           // cout<<(*itPot)->getName2()<<" "<<(*itPot)->getFile()<<endl;
            if((*itCmix)->getName1()==(*itPot)->getName1()&&(*itCmix)->getName1()==(*itPot)->getName2())
            {
                check1=false;
                temp1=(*itPot);
            }
            if((*itCmix)->getName2()==(*itPot)->getName1()&&(*itCmix)->getName2()==(*itPot)->getName2())
            {
                check2=false;
                temp2=(*itPot);
            }

        }
        if(check2||check1)
        {
            cout << "ERROR: Did not find pure potential for mixing!!! "<<endl;
        }else if(temp1->getParameters().size()==2&&temp2->getParameters().size()==2)
        {

           vecPotential.push_back(lj_mix(temp1,temp2,(*itCmix)->getMixing()));
        }else if(temp1->getParameters().size()==3&&temp2->getParameters().size()==3)
        {
           vecPotential.push_back(geometric(temp1,temp2));
        }else if(temp1->getParameters().size()!=temp2->getParameters().size())
        {
            cout<<temp1->getName1()<<" "<<temp1->getParameters().size()<<" "<<temp2->getParameters().size()<<endl;
            cout<< "ERROR:: I can NOT mix lennard jones and buckingham for YOU!!"<<endl;
        }

    }

}

potential *Cmix::lj_mix(potential *&pot1, potential *&pot2,string mixingrule)
{
    double eps,sig;
    potential * temp;



       // cout <<"Before "<< pot1->getParameters().at(0)<<" "<<pot2->getParameters().at(0)<<endl;



            string file=pot1->getFile()+" "+pot2->getFile()+" mix";
            if(pot1->getStyle().substr(0,3)==pot2->getStyle().substr(0,3))
            {
                if(mixingrule=="LB")
                {
                    cout<<"LB mix "<<pot1->getName1()<<" - "<<pot2->getName1()<<" \n";
                    eps=sqrt(pot1->getParameters().at(0)*pot2->getParameters().at(0));
                    sig=(pot1->getParameters().at(1)+pot2->getParameters().at(1))/2;
                }else if(mixingrule=="geo")
                {
                    cout<<"Geo mix "<<pot1->getName1()<<" - "<<pot2->getName1()<<" \n";

                    eps=sqrt(pot1->getParameters().at(0)*pot2->getParameters().at(0));
                    sig=sqrt(pot1->getParameters().at(1)*pot2->getParameters().at(1));

                }

                temp=new lennardJones(pot1->getName1(),pot2->getName2(),pot1->getStyle(),file,eps,sig);

            }else if(pot1->getStyle().substr(0,3)=="ljA" || pot2->getStyle().substr(0,3)=="ljA")
            {
                // For mixing lj and ljAB to give ljAB

                if(pot1->getStyle().substr(0,3)=="ljA")
                {
                    cout<<"Geo mix ljAB "<<pot1->getName1()<<" - "<<pot2->getName1()<<" \n";
                    double A,B;
                    A=4*pot2->getParameters().at(0)*pow(pot2->getParameters().at(1),12);
                    B=4*pot2->getParameters().at(0)*pow(pot2->getParameters().at(1),6);
                    eps=sqrt(pot1->getParameters().at(1)*A);
                    sig=sqrt(pot1->getParameters().at(1)*B);

                    temp=new lennardJones(pot1->getName1(),pot2->getName2(),pot1->getStyle(),file,eps,sig);

                }else if(pot2->getStyle().substr(0,3)=="ljA")
                {
                    cout<<"Geo mix ljAB "<<pot1->getName1()<<" - "<<pot2->getName1()<<" \n";

                    double A,B;
                    A=4*pot1->getParameters().at(0)*pow(pot1->getParameters().at(1),12);
                    B=4*pot1->getParameters().at(0)*pow(pot1->getParameters().at(1),6);
                    eps=sqrt(pot2->getParameters().at(1)*A);
                    sig=sqrt(pot2->getParameters().at(1)*B);

                    temp=new lennardJones(pot1->getName1(),pot2->getName2(),pot2->getStyle(),file,eps,sig);
                }





            }else
            {
                cout<<"Check Mixing types "<<endl;
            }


        //cout <<"eps is " <<eps<<" "<<pot1->getName1()<<" "<<pot2->getName2()<<endl;



        return temp;



}

potential *Cmix::geometric(potential *pot1, potential *pot2)
{
    double A,rho,C;
    potential * temp;

    cout<<"Geo mix buck "<<pot1->getName1()<<" - "<<pot2->getName1()<<" \n";


    A=sqrt(pot1->getParameters().at(0)*pot2->getParameters().at(0));
    rho=sqrt(pot1->getParameters().at(1)*pot2->getParameters().at(1));
    C=sqrt(pot1->getParameters().at(2)*pot2->getParameters().at(2));

    temp=new buckingham(pot1->getName1(),pot2->getName2(),pot1->getStyle(),"Mixing!! ",A,rho,C);
    temp->printTerminal();

    return temp;

}
