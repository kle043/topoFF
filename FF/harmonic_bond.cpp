#include "harmonic_bond.h"
harmonic_bond::harmonic_bond(int i,string n1,string n2,double k,double r,string uni,string f):potential(n1,n2,uni,f)
{
    setId1(i);
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;
    stylename="harmonic";

}

harmonic_bond::harmonic_bond(string n1,string n2,double k,double r,string uni,string f):potential(n1,n2,uni,f)
{
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;
    style="harmonic";
    stylename="harmonic";

}

harmonic_bond::harmonic_bond(string n1, string n2, double k, double r, string uni, string f, string s):potential(n1,n2,uni,f)
{
    prefix="bond_coeff";
    K=getEnergyFactor()*k;
    req=r;
    style=s;
    stylename="harmonic";

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

void harmonic_bond::printHOOMD(ofstream &out, double e, double d)
{
    if (out.is_open())
    {

         out<<"    harmonic.bond_coeff.set('"<<getId1()<<"',k="<<2*getK()*e<<",r0="<<getReq()/d
             <<")# "<<getName1()<<" - "<<getName2()<<endl;
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

void harmonic_bond::printLatex(ofstream &out, double e)
{
    out<<"      "<<getName1()<<" - "<<getName2()<<" & "<<getK()*e<<" & "<<getReq()<<" \\\\ \n";


}
