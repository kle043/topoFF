#include "ccoordinates.h"

ccoordinates::ccoordinates(double &ix, double &iy, double &iz):x(ix),y(iy),z(iz)
{

}

void ccoordinates::setCoordinates(double &ix, double &iy, double &iz)
{
    x=ix;
    y=iy;
    z=iz;
}

double &ccoordinates::getPos(string d)
{
    if(d=="z")
    {
        return z;
    }
    if(d=="y")
    {
       return y;

    }

    return x;




}

ccoordinates ccoordinates::operator ()(double ix, double iy, double iz)
{
   x=ix;
   y=iy;
   z=iz;

}

ccoordinates ccoordinates::operator+(ccoordinates &coord1)
{

    double x=this->getX()+coord1.getX();
    double y=this->getY()+coord1.getY();
    double z=this->getZ()+coord1.getZ();
    ccoordinates coord(x,y,z);

    return coord;

}

ccoordinates ccoordinates::operator/(double &n)
{
    double x=this->getX()/n;
    double y=this->getY()/n;
    double z=this->getZ()/n;
    ccoordinates coord(x,y,z);

    return coord;

}

ccoordinates ccoordinates::cross(ccoordinates &coord1)
{
    double x=this->getY()*coord1.getZ()-this->getZ()*coord1.getY();
    double y=this->getZ()*coord1.getX()-this->getX()*coord1.getZ();
    double z=this->getX()*coord1.getY()-this->getY()*coord1.getX();

    ccoordinates coord(x,y,z);

    return coord;


}

double ccoordinates::operator*(ccoordinates &coord1)
{
    double x=this->getX()*coord1.getX();
    double y=this->getY()*coord1.getY();
    double z=this->getZ()*coord1.getZ();

    double res=x+y+z;

    return res;

}

ccoordinates ccoordinates::operator*(double &n)
{
    double x=n*this->getX();
    double y=n*this->getY();
    double z=n*this->getZ();
    ccoordinates coord(x,y,z);
    return coord;


}

ccoordinates ccoordinates::operator-(ccoordinates &coord1)
{
    double x=this->getX()-coord1.getX();
    double y=this->getY()-coord1.getY();
    double z=this->getZ()-coord1.getZ();
    ccoordinates coord(x,y,z);

    return coord;

}

void ccoordinates::printCoordinates()
{
    cout<<x<<" "<<y<<" "<<z<<endl;

}

