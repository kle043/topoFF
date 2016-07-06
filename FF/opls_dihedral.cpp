#include "opls_dihedral.h"

opls_dihedral::opls_dihedral(string n1, string n2, string n3, string n4, double k1, double k2, double k3,double k4, string uni, string f):harmonic_dihedral(n1,n2,n3,n4,uni,f)
{
    style="opls";
    stylename="opls";
    K1=getEnergyFactor()*k1;
    K2=getEnergyFactor()*k2;
    K3=getEnergyFactor()*k3;
    K4=getEnergyFactor()*k4;
}

void opls_dihedral::print(ofstream &out)
{
    if (out.is_open())
    {

          out<<setw(20)<<left<<prefix<<setw(5)<<getId1()<<setw(10)<<style<<setw(10)
              <<K1<<setw(20)<<" "
              <<K2<<setw(20)<<" "
              <<K3<<setw(30)<<" "
              <<K4<<setw(30)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<"-"<<getName4()<<"-"<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }
}

void opls_dihedral::printHOOMD(ofstream &out, double e, double d)
{
    if (out.is_open())
    {

         out<<"    opls_dihedral.set_coeff('"<<getId1()<<"',k1="<<K1*e
             <<",k2="<<K2*e
             <<",k3="<<K3*e
             <<",k4="<<K4*e
             <<")# "<<getName1()<<" - "<<getName2()<<" - "<<getName3()<<" - "<<getName4()<<endl;

         if(!vecParameters.empty())
         {
            out<<"    bnlj.bond_coeff.set('"<<getId2()<<"',epsilon="<<vecParameters.at(0)*e<<",sigma="<<vecParameters.at(1)/d<<",scale=0.5)# "<<getName1()<<" - "<<getName4()<<endl;
         }

    }else
    {
        cout<<"Could not write to file\n";
    }
}
