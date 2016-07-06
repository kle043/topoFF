#include "atom.h"

atom::atom(string n, double c):name(n),charge(c)
{
    id=-1;
}

void atom::print(ofstream &out)
{
    if (out.is_open())
    {
        out<<setw(14)<<left<<"set   type"<<setw(4)<<getId()<<" charge  "<<setw(10)<<getCharge()<<" # "<<getName()<<right<<endl;
    }else
    {

        cout<<"Could not write to file\n";
    }


}
