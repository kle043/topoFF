#include "cgroup.h"

Cgroup::Cgroup(string n, vector<string> v):groupName(n)
{
    for (itSz=v.begin();itSz!=v.end();itSz++)
    {
        vecNames.push_back(new Cgroup::nameId(*itSz));
    }
}

Cgroup::~Cgroup()
{
    for (itNames=vecNames.begin();itNames!=vecNames.end();itNames++)
    {
        delete *itNames;
    }
}

void Cgroup::print(ofstream &out)
{
    if(out.is_open())
    {

        out<<setw(8)<<left<<"group "<<setw(10)<<getGroupName()<<" type "<<left;

        for (itNames=vecNames.begin();itNames!=vecNames.end();itNames++)
        {
            for (int i=0; i<(*itNames)->getVecSize();i++)
            {
                out<<" "<<left<<(*itNames)->getId(i)<<" ";
            }
        }
        out<<setw(10)<<right<<"# ";
        for (itNames=vecNames.begin();itNames!=vecNames.end();itNames++)
        {
            out<<(*itNames)->getName()<<" ";
        }

        out<<endl;
    }

}

void Cgroup::printHOOMD(ofstream &out)
{
    for (itNames=vecNames.begin();itNames!=vecNames.end();itNames++)
    {
        out<<"        self."<<(*itNames)->getName()<<"=group.type(name='g"<<(*itNames)->getName()<<"',type='"
           <<(*itNames)->getName()<<"')"<<endl;
    }

    if(vecNames.size()>1)
    {

        out<<"        self."<<getGroupName()<<"=group.union(name='g"<<getGroupName()<<"',a=self."
           <<(*(vecNames.begin()+1))->getName()<<",b=self."<<(*(vecNames.begin()))->getName() <<")"<<endl;

        for (itNames=vecNames.begin()+2;itNames!=vecNames.end();itNames++)
        {

            out<<"        self."<<getGroupName()<<"=group.union(name='g"<<getGroupName()<<"',a=self."
               <<getGroupName()<<",b=self."<<(*itNames)->getName() <<")"<<endl;

        }
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
