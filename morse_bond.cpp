#include "morse_bond.h"

morse_bond::morse_bond(string n1, string n2, double k, double r, string uni, string f,double a):harmonic_bond(n1,n2,k,r,uni,f)
{
    style="morse";
    alpha=a;
}


morse_bond::morse_bond(int i, string n1, string n2, double k, double r, string uni, string f):harmonic_bond(i,n1,n2,k,r,uni,f)
{

}

morse_bond::morse_bond(string n1, string n2, double k, string uni, string f):harmonic_bond(n1,n2,k,uni,f)
{

}

void morse_bond::print(ofstream &out)
{

    if (out.is_open())
    {

          out<<setw(14)<<left<<prefix<<setw(5)<<getId1()<<setw(10)<<style<<setw(10)
              <<getK()<<setw(15)<<" "
              <<getAlpha()<<setw(15)<<" "
              <<getReq()<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }

}

