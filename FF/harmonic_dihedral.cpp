#include "harmonic_dihedral.h"


harmonic_dihedral::harmonic_dihedral(string n1, string n2, string n3, string n4, string uni, string f):harmonic_angle(n1,n2,n3,uni,f)
{
    prefix="dihedral_coeff";
    setName4(n4);
    stylename="harmonic";
}

harmonic_dihedral::harmonic_dihedral(int i, string n1, string n2, string n3, string n4, double k, double ind, double n, string uni, string f):harmonic_angle(i,n1,n2,n3,k,n,uni,f)
{
    setId1(i);
    prefix="dihedral_coeff";
    style="harmonic";
    stylename="harmonic";
    setName4(n4);
    d=ind;


}

harmonic_dihedral::harmonic_dihedral(string n1, string n2, string n3, string n4, double k, double ind, double n, string uni, string f):harmonic_angle(n1,n2,n3,k,n,uni,f)
{
    prefix="dihedral_coeff";
    style="harmonic";
    stylename="harmonic";
    setName4(n4);
    d=ind;

}

void harmonic_dihedral::print(ofstream &out)
{
   // cout<<"Dihedral print"<<endl;
    if (out.is_open())
    {

          out<<setw(20)<<left<<prefix<<setw(5)<<getId1()<<setw(10)<<style<<setw(10)
              <<getK()<<setw(15)<<" "
              <<getD()<<setw(15)<<" "
              <<getAngle()<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<" "<<getName4()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }
}
