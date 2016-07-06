#include "buckingham.h"
buckingham::buckingham(buckingham &obj):potential(obj.getId1(),obj.getId2(),obj.getName1(),obj.getName2(),obj.getStyle(),obj.getFile())
{
  A=obj.getA();
  rho=obj.getRho();
  C=obj.getC();
  style=obj.style;

}

buckingham::buckingham(string n1, string n2, string st, string f, double a, double r, double c):potential(n1,n2,st,f),A(a),rho(r),C(c)
{

    vecParameters.push_back(A);
    vecParameters.push_back(rho);
    vecParameters.push_back(C);
}
buckingham::buckingham(string n1, string n2, string st, string uni, string disuni, string f, double a, double r, double c):potential(n1,n2,st,uni,disuni,f)
{
    A=getEnergyFactor()*a;
    C=getEnergyFactor()*c;
    rho=getDistanceFactor()*r;

    if (rho>1&& A > 0)
    {
        cout<< "Going from buckingham full style to normal style i.e Ae-rho -C !!"<<endl;

        double cA=A;
        double cC=C/getEnergyFactor();
        double cRho=rho;
        A=((6*cA)/(cC-6))*exp(cC);
        rho=cRho/cC;
        C=(cC*cA*pow(cRho,6))/(cC-6);


    }

    vecParameters.push_back(A);
    vecParameters.push_back(rho);
    vecParameters.push_back(C);

}

void buckingham::print(ofstream & out)
{
    if (out.is_open())
    {
        out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
             <<getId2()<<setw(30)
             <<getStyle()<<setw(20)
             <<getA()<<setw(20)
             <<getRho()<<setw(10)
             <<getC()<<setw(5)<<right<<"#"
             <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;
    }else
    {
        cout<<"Could not write to file\n";
    }


}

void buckingham::printTerminal()
{
          cout<<getId1()<<" "
              <<getId2()<<" "
              <<getStyle()<<" "
              <<getA()<<" "
              <<getRho()<<" "
              <<getC()<<" "<<"#"
              <<getName1()<<" "<<getName2()<< endl;

}
