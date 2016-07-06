#include "cgroup.h"

Cgroup::Cgroup(string n, vector<string> v):groupName(n)
{
    for (itSz=v.begin();itSz!=v.end();itSz++)
    {
        vecAtoms.push_back(new Cgroup::nameId(*itSz));
    }
}

Cgroup::~Cgroup()
{
    for (itAtoms=vecAtoms.begin();itAtoms!=vecAtoms.end();itAtoms++)
    {
        delete *itAtoms;
    }
}

void Cgroup::print(ofstream &out)
{
    if(out.is_open())
    {

        out<<setw(8)<<left<<"group "<<setw(10)<<getGroupName()<<" type "<<left;

        for (itAtoms=vecAtoms.begin();itAtoms!=vecAtoms.end();itAtoms++)
        {
            for (int i=0; i<(*itAtoms)->getVecSize();i++)
            {
                out<<" "<<left<<(*itAtoms)->getId(i)<<" ";
            }
        }
        out<<setw(10)<<right<<"# ";
        for (itAtoms=vecAtoms.begin();itAtoms!=vecAtoms.end();itAtoms++)
        {
            out<<(*itAtoms)->getName()<<" ";
        }

        out<<endl;
    }

}


Cgroup::nameId::nameId(string n):name(n)
{

  //  id=-100;
}

void Cgroup::nameId::setId(int i)
{
    //cout <<"Add "<<i<<" after \n";
    for (it=vecid.begin();it!=vecid.end();it++)
    {
        if(i>*it)
        {
      //      cout <<*(it)<<" before "<<*(it-1)<<endl;
            vecid.insert(it+1,i);
            return;
        }
    }
    vecid.push_back(i);
}

int Cgroup::nameId::getId(int i)
{
    if (i<vecid.size()&&i>=0)
    {
        return vecid.at(i);
    }

    return -1000;

}
