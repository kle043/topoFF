#include "opls_dihedral.h"

opls_dihedral::opls_dihedral(string n1, string n2, string n3, string n4, double k1, double k2, double k3,double k4, string uni, string f):harmonic_dihedral(n1,n2,n3,n4,uni,f)
{
    style="opls";
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
              <<K1<<setw(15)<<" "
              <<K2<<setw(15)<<" "
              <<K3<<setw(15)<<" "
              <<K4<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<" "<<getName4()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }
}
