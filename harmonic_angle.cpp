#include "harmonic_angle.h"

harmonic_angle::harmonic_angle(string n1,string n2,string n3,double k,double a,string uni,string f):harmonic_bond(n1,n2,k,uni,f)
{
    prefix="angle_coeff";
    angle=a;
    setName3(n3);
}
harmonic_angle::harmonic_angle(string n1, string n2, string n3, string uni, string f):harmonic_bond(n1,n2,uni,f)
{

    setName3(n3);
}

harmonic_angle::harmonic_angle(int i,string n1,string n2,string n3,double k,double a,string uni,string f):harmonic_bond(n1,n2,k,uni,f)
{
    setId1(i);
    prefix="angle_coeff";
    angle=a;
    setName3(n3);
}

void harmonic_angle::print(ofstream &out)
{
    if (out.is_open())
    {

          out<<setw(14)<<left<<prefix<<setw(5)<<getId1()<<setw(10)
              <<getK()<<setw(15)<<" "
              <<getAngle()<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }


}

void harmonic_angle::printTerminal()
{
          cout<<prefix<<" "<<getId1()<<" "
              <<getK()<<" "
              <<getAngle()<<" "<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<" "<< getFile()<< endl;

}
