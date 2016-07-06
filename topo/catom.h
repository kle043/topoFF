#ifndef CAtom_H
#define CAtom_H
#include <string>
#include <iostream>
#include "ccoordinates.h"
#include <vector>
#include <stdexcept>
using namespace std;

class cAtom
{
public:
    cAtom(){;}
    ~cAtom();
    void setVisited(){visited=true;}
    void unSetVisited(){visited=false;}
    bool getVisited(){return visited;}
    void setCharge(double c){charge=c;}
    const double & getCharge() const {return charge;}
    void setHCharge(double c){hcharge=c;}
    const double & getHCharge() const {return hcharge;}
    void setType(int t){typeId=t;}
    void setIdx(int i){index=i;}
    void setPBC(){pbc=true;}
    void unPBC(){pbc=false;}
    bool getPBC(){return pbc;}
    cAtom(int i, int rid, string resN, string N, string T, double ch, double m, int t);
    cAtom(int i, int rid, string resN, string N, string T, double ch, double m, int t,double x,double y,double z);
    void addCoord(double x,double y,double z);
    const int & getIdx() const {return index;}
    void setResId(int i){resid=i;}
    int getResId(){return resid;}
    const double & getMass() const {return mass;}
    const int & getType() const {return typeId;}
    const string & getResname() const {return resname;}
    const string & getName() const {return name;}
    ccoordinates * & getCoordinates(int idx) {return vecCoord.at(idx);}
    vector<ccoordinates*> & getVecCoordinates(){return vecCoord;}
    int  getNframes() {return vecCoord.size();}
    void printTerminal();

private:
    int index,resid;
    bool visited,pbc;
    vector<ccoordinates*> vecCoord;
    vector<ccoordinates*>::iterator itCoord;
    string resname,name,type;
    double charge,mass,hcharge;
    int typeId;


};

#endif // CAtom_H
