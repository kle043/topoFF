#ifndef POTENTIAL_H
#define POTENTIAL_H
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

class potential
{
public:
    potential (){;}
    virtual ~potential(){;}
    potential(int i1, int i2, string n1, string n2, bool ii);
    potential(int i1,int i2,string n1,string n2,string uni,string f);
    potential(string n1,string n2,string uni,string f);
    potential (string n1, string n2, string st, string uni, string disUni, string f);
    string const & getFile () {return file;}
    string const & getStyle () {return style;}
    void emptyStyle(){style="";}
    string const & getName1 () {return name1;}
    string const & getName2 () {return name2;}
    string const & getName3 () {return name3;}
    string const & getName4 () {return name4;}
    double getLambda(){return lambda;}
    void setStyle(string s){style=s;}
    void setLambda(double d){lambda=d;}
    void setName1(string n){name1=n;}
    void setName2(string n){name2=n;}
    void setName3(string n){name3=n;}
    void setName4(string n){name4=n;}
    int const & getId1 () {return id1;}
    int const & getId2 () {return id2;}
    void setId1 (const int &i) {id1=i;}
    void setId2 (const int &i) {id2=i;}
    void addSpace(){file=file+"\n\n";}
    double getEnergyFactor(){return energyFactor;}
    double getDistanceFactor(){return distanceFactor;}
    void setVisited( ){visited=true;}
    bool isVisited(){return visited;}
    virtual void print(ofstream & out)=0;
    virtual vector<double> & getParameters(){return vecParameters;}
    virtual void printTerminal(){;}
    virtual potential * clone() {return NULL;}

protected:
    string prefix;
    vector<double> vecParameters;
    string style;

private:
    string name1;
    string name2; //
    string name3; //for angle 3 name
    string name4; //for dihedral 3 name
    string units;
    string disUnits;
    string file;
    bool visited;
    double energyFactor,lambda;
    double distanceFactor;

    int id1;
    int id2;

};

#endif // POTENTIAL_H
