#include "lennardJones.h"
lennardJones::lennardJones(lennardJones &obj):potential(obj.getId1(),obj.getId2(),obj.getName1(),obj.getName2(),obj.getStyle(),obj.getFile())
{
    epsilon=obj.getEpsilon();
    sigma=obj.getSigma();
    style=obj.style;
    vecParameters.clear();
    vecParameters.push_back(epsilon);
    vecParameters.push_back(sigma);
    stylename="lj";

}

lennardJones::lennardJones(string n1, string n2, string st,string f, double eps, double sig):potential(n1,n2,st,f),epsilon(eps),sigma(sig)
{
    stylename="lj";
    vecParameters.clear();
    vecParameters.push_back(epsilon);
    vecParameters.push_back(sigma);

}

lennardJones::lennardJones(string n1, string n2, string st, string uni, string disuni, string f, double eps, double sig):potential(n1,n2,st,uni,disuni,f)
{
    stylename="lj";

    if(disuni=="AB")
    {
        double e=1.0/6.0;
        double AB=eps/sig;
        epsilon=getEnergyFactor()*(sig*sig)/(4*eps);
        sigma=getDistanceFactor()*pow(AB,e);
        vecParameters.clear();
        vecParameters.push_back(epsilon);
        vecParameters.push_back(sigma);
       // cout<<"format = AB "<<e<<" "<<sigma<<endl;

    }else
    {

        epsilon=getEnergyFactor()*eps;
        sigma=getDistanceFactor()*sig;
        vecParameters.clear();
        vecParameters.push_back(epsilon);
        vecParameters.push_back(sigma);
    }
   // cout<<eps<<" " <<getEnergyFactor()<<  endl;

}

lennardJones::lennardJones(int i1, int i2, bool ii,string n1, string n2):potential(i1,i2,n1,n2,ii)
{
    stylename="lj";
    //Creating empty potential
    epsilon=0;
    sigma=0;

}

void lennardJones::printHOOMD(ofstream &out, double e, double d)
{
    string pure=".pure.";
    std::size_t found = getFile().find(pure);
    string mix="mix";
    std::size_t foundmix = getFile().find(mix);

    if (found!=std::string::npos && foundmix==std::string::npos)
    {

    }else
    {
        if(getSigma()==0.00)
        {

            sigma=1.0;

            epsilon/=4;

            out<<"    lj.pair_coeff.set('"<<getName1()<<"','"<<getName2()<<"',"
            <<"epsilon="<<getEpsilon()*e<<",sigma="<<getSigma()/d<<",alpha=0.0) #"
            <<getFile()<<endl;







        }else
        {

            out<<"    lj.pair_coeff.set('"<<getName1()<<"','"<<getName2()<<"',"
           <<"epsilon="<<getEpsilon()*e<<",sigma="<<getSigma()/d<<") #"
           <<getFile()<<endl;
        }
    }



}

void lennardJones::printLatex(ofstream &out, double e)
{
    out<<"      "<<getName1()<<" & "<<getName2()<<" & "<<getEpsilon()*e<<" & "<<getSigma()<<" \\\\ \n";

}


void lennardJones::print(ofstream &out)
{
    string pure=".pure.";
    std::size_t found = getFile().find(pure);
    string mix="mix";
    std::size_t foundmix = getFile().find(mix);
    std::size_t foundsoft = getStyle().find("soft");





    if (out.is_open())
    {
        if (found!=std::string::npos && foundmix==std::string::npos)
        {
            out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
                <<getId2()<<setw(30)
                <<"coul/long"<<setw(20)
                <<" "<<setw(20)
                <<" "<<setw(15)<<right<<"#"
                <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;

        }else if(foundsoft!=std::string::npos)
        {
            out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
                <<getId2()<<setw(30)
                <<getStyle()<<setw(20)
                <<getEpsilon()<<setw(20)
                <<getSigma()<<setw(14)
                <<fixed<<setprecision(1)<<getLambda()<< resetiosflags(ios::fixed)<<setprecision(5)<<right<<"#"
                <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;


        }else
        {

          out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
              <<getId2()<<setw(30)
              <<getStyle()<<setw(20)
              <<getEpsilon()<<setw(20)
              <<getSigma()<<setw(15)<<right<<"#"
              <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;

        }
    }else
    {
        cout<<"Could not write to file\n";
    }

}

void lennardJones::printTerminal()
{
          cout<<getId1()<<" "
              <<getId2()<<" "
              <<getStyle()<<" "
              <<getEpsilon()<<" "
              <<getSigma()<<" "<<"#"
              <<getName1()<<" "<<getName2()<< endl;

}
