#ifndef CGROUP_H
#define CGROUP_H
#include<string>
#include<vector>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;
class Cgroup
{
public:
    class nameId
    {
    public:
        nameId(string n);
        string getName(){return name;}
        void setId(int i);
        int getId(int i);
        int getVecSize(){return vecid.size();}

    private:

        string name;
        vector<int>  vecid;
        vector<int>::iterator  it;

    };
    Cgroup(string n,vector<string> v);
    ~Cgroup();
    string getGroupName(){return groupName;}
    vector<Cgroup::nameId*> & getGroupNames(){return vecNames;}
    void print (ofstream &out);
    void printHOOMD(ofstream &out);

private:
    string groupName;
    vector<string>::iterator itSz;
    vector<nameId*> vecNames;
    vector<nameId*>::iterator itNames;
};

#endif // CGROUP_H
