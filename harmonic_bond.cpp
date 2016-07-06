#include "harmonic_bond.h"
harmonic_bond::harmonic_bond(int i,string n1,string n2,double k,double r,string uni,string f):potential(n1,n2,uni,f)
{
    setId1(i);
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;

}

harmonic_bond::harmonic_bond(string n1,string n2,double k,double r,string uni,string f):potential(n1,n2,uni,f)
{
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;
    style="harmonic";

}

harmonic_bond::harmonic_bond(string n1, string n2, double k, double r, string uni, string f, string s):potential(n1,n2,uni,f)
{
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;
    style=s;

}
harmonic_bond::harmonic_bond(string n1,string n2,double k,string uni,string f):potential(n1,n2,uni,f)
{
    K=getEnergyFactor()*k;

}

harmonic_bond::harmonic_bond(string n1, string n2, string uni, string f):potential(n1,n2,uni,f)
{

}

void harmonic_bond::print(ofstream &out)
{
    if (out.is_open())
    {

          out<<setw(14)<<left<<prefix<<setw(5)<<getId1()<<setw(10)<<style<<setw(10)
              <<getK()<<setw(15)<<" "
              <<getReq()<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }

}



void harmonic_bond::printTerminal()
{
          cout<<prefix<<" "<<getId1()<<" "
              <<getK()<<" "
              <<getReq()<<" "<<right<<"#"
              <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;

}
