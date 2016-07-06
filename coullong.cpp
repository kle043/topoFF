#include "coullong.h"

coulLong::coulLong(coulLong &obj):potential(obj.getId1(),obj.getId2(),obj.getName1(),obj.getName2(),obj.getStyle(),obj.getFile())
{

}

coulLong::coulLong(int i1, int i2, bool ii,string n1, string n2):potential(i1,i2,n1,n2,ii)
{
    setStyle("coul/long");

}

void coulLong::print(ofstream &out)
{
    std::size_t foundsoft = getStyle().find("soft");

    if (out.is_open())
    {
        if(foundsoft!=std::string::npos)
        {

          out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
              <<getId2()<<setw(70)
              <<getStyle()<<setw(13)
              <<fixed<<setprecision(1)<<getLambda()<< resetiosflags(ios::fixed)<<setprecision(8)
              <<" "<<right<<"#"
              <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;
        }else
        {
            out<<setw(12)<<left<<prefix<<setw(4)<<getId1()<<setw(5)
                <<getId2()<<setw(30)
                <<getStyle()<<setw(20)
                <<" "<<setw(20)
                <<" "<<setw(15)<<right<<"#"
                <<getName1()<<" "<<getName2()<<" "<< getFile()<< endl;

        }
    }else
    {
        cout<<"Could not write to file\n";
    }

}

void coulLong::printTerminal()
{

        cout<<getId1()<<" "
            <<getId2()<<" "
            <<getStyle()<<" #"
            <<getName1()<<" "<<getName2()<< endl;

}
