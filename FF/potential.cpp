#include "potential.h"
potential::potential(string n1, string n2, string uni, string f):name1(n1),name2(n2),units(uni),file(f)
{

    visited=false;
    id1=-1;
    id2=-1;

    if(units=="ev")
    {
        energyFactor=23.0609;
     //   energyFactor=3.82929389*6.0221415;
    }else if (units=="kj")
    {
        energyFactor=1/4.1840;

    }else if(units=="kcal")
    {
        energyFactor=1;
    }else if (units=="K")
    {
        energyFactor=(8.314/4184);
    }



    if(uni.substr(0,3)=="lj/"|| uni.substr(0,5)=="buck/")
    {
        prefix="pair_coeff";
        style=units;
    }


}

potential::potential(string n1, string n2, string st, string uni,string disUni, string f):name1(n1),name2(n2),style(st),units(uni),disUnits(disUni),file(f)
{
    visited=false;
    id1=-1;
    id2=-1;
    prefix="pair_coeff";
    if(units=="ev")
    {
        energyFactor=23.0609;
        //energyFactor=3.82929389*6.0221415;
    }else if (units=="kj")
    {
        energyFactor=1/4.1840;

    }else if(units=="kcal")
    {
        energyFactor=1;
    }else if (units=="K")
    {
        energyFactor=(8.314/4184);
    }

    if (disUnits=="A")
    {
        distanceFactor=1;
    }else if (disUnits=="nm")
    {
        distanceFactor=10;
    }else if(disUnits=="Rm")
    {
        double r=1.0/6.0;
        distanceFactor=1.0/pow(2,r);
        //cout <<distanceFactor<<" "<<r<<endl;
    }else if (disUnits=="AB")
    {
        distanceFactor=1;
    }

}
potential::potential(int i1,int i2,string n1,string n2,bool ii): id1(i1),id2(i2),name1(n1),name2(n2)
{
    visited=false;

    if (ii)
    {
        style="";
    }else
    {

    }
    prefix="pair_coeff";
    file="MISSING!";


}

potential::potential(int i1, int i2, string n1, string n2, string uni, string f):id1(i1),id2(i2),name1(n1),name2(n2),units(uni),file(f)
{
    visited=false;
    prefix="pair_coeff";

}
/*potential::potential(int i1, int i2):id1(i1),id1(i2)
{

}*/
