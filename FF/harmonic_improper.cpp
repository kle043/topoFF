#include "harmonic_improper.h"
harmonic_improper::harmonic_improper(string n1, string n2, string n3, string n4, double k, double n, string uni, string f):harmonic_angle(n1,n2,n3,k,n,uni,f)
{
    prefix="improper_coeff";
    style="harmonic";
    stylename="harmonic";
    setName4(n4);
}

harmonic_improper::harmonic_improper(int i, string n1, string n2, string n3, string n4, double k, double n, string uni, string f):harmonic_angle(i,n1,n2,n3,k,n,uni,f)
{
    setId1(i);
    prefix="improper_coeff";
    style="harmonic";
    stylename="harmonic";
    setName4(n4);


}
void harmonic_improper::print(ofstream &out)
{
// cout<<"improper print"<<endl;
    if (out.is_open())
    {

          out<<setw(20)<<left<<prefix<<setw(5)<<getId1()<<setw(10)<<style<<setw(10)
              <<getK()<<setw(15)<<" "
              <<getAngle()<<setw(10)<<right<<"#"
              <<getName1()<<"-"<<getName2()<<"-"<<getName3()<<" "<<getName4()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }
}
void harmonic_improper::printHOOMD(ofstream &out, double e, double d)
{
    double ang=getAngle()*3.14159/180;
    if (out.is_open())
    {

        out<<"    harmonic_improper.set_coeff('"<<getId1()<<"',k="<<2*getK()*e<<",chi="<<ang
            <<")# "<<getName1()<<" - "<<getName2()<<" - "<<getName3()<<" - "<<getName4()<<endl;

    }else
    {
        cout<<"Could not write to file\n";
    }

}
