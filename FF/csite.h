#ifndef CSite_H
#define CSite_H
#include<string>
#include<vector>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;
class cSite
{
public:
    cSite(string n,double c);
    string getName(){return name;}
    void setIdx(int i){id=i;}
    double getCharge(){return charge;}
    int getIdx(){return id;}
    void print (ofstream &out);
    void printLatex (ofstream &out);

private:
    string name;
    int id;
    double charge;
};

#endif // CSite_H
