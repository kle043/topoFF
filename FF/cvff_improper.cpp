#include "cvff_improper.h"
cvff_improper::cvff_improper(string n1, string n2, string n3, string n4, double k, double ind, double n,string uni, string f):harmonic_angle(n1,n2,n3,k,n,uni,f)
{
    prefix="improper_coeff";
    style="cvff";
    setName4(n4);
    d=ind;
    stylename="cvff";
}

void cvff_improper::print(ofstream &out)
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

void cvff_improper::printHOOMD(ofstream &out, double e, double d)
{



    if (out.is_open())
    {
        if(getId1()<0) setId1(-getId1());


        out<<"    harmonic_dihedral.set_coeff('"<<getId1()<<"',k="<<2*getK()*e<<",d="<<getD()<<",n="<<getAngle()
            <<")# "<<getName1()<<" - "<<getName2()<<" - "<<getName3()<<" - "<<getName4()<<endl;

    }else
    {
        cout<<"Could not write to file\n";
    }

}

void cvff_improper::printLatex(ofstream &out, double e)
{
    out<<"      "<<getName1()<<"-"<<getName2()<<"-"<<getName3()<<"-"<<getName4()<<" & "<<getK()*e<<" & "<<getD()<<" & "<<getAngle()<<" \\\\ \n";

}
