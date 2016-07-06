#ifndef ATOM_H
#define ATOM_H
#include<string>
#include<vector>
#include <iomanip>
#include <fstream>
#include <iostream>
using namespace std;
class atom
{
public:
    atom(string n,double c);
    string getName(){return name;}
    void setId(int i){id=i;}
    double getCharge(){return charge;}
    int getId(){return id;}
    void print (ofstream &out);
    void addSpace(){name=name+"\n\n";}
private:
    string name;
    int id;
    double charge;
};

#endif // ATOM_H
