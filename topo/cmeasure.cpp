#include "cmeasure.h"

cmeasure::cmeasure()
{


}

double cmeasure::getBond(cAtom *atom1, cAtom *atom2, int frame)
{

    ccoordinates coord1,coord2;

    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);


    return getBond(coord1,coord2);


}

double cmeasure::getBondPBC(cAtom *atom1, cAtom *atom2, int frame, double x, double y, double z)
{
    ccoordinates coord1,coord2;

    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);

    double pbcx=coord1.getX()+x;
    double pbcy=coord1.getY()+y;
    double pbcz=coord1.getZ()+z;

    coord1.setCoordinates(pbcx,pbcy,pbcz);



    return getBond(coord1,coord2);

}

double cmeasure::getAngle(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame)
{


    ccoordinates coord1,coord2,coord3;


    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);
    coord3=*atom3->getCoordinates(frame);

    return getAngle(coord1,coord2,coord3);



}

double cmeasure::getDihedral(cAtom *atom1, cAtom *atom2, cAtom *atom3, cAtom *atom4, int frame)
{
    ccoordinates coord1,coord2,coord3,coord4;


    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);
    coord3=*atom3->getCoordinates(frame);
    coord4=*atom4->getCoordinates(frame);

    ccoordinates vec1,vec2,vec3,vecX1,vecX2;


    vec1=coord2-coord1;
    vec2=coord3-coord2;
    vec3=coord4-coord3;


    vecX1=vec1.cross(vec2);
    vecX2=vec2.cross(vec3);


    return vecAngle(vecX1,vecX2);
}

double cmeasure::getAnglePBC(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame, double x, double y, double z)
{
    ccoordinates coord1,coord2,coord3;


    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);
    coord3=*atom3->getCoordinates(frame);

    double pbcx=coord1.getX()+x;
    double pbcy=coord1.getY()+y;
    double pbcz=coord1.getZ()+z;

    coord1.setCoordinates(pbcx,pbcy,pbcz);

    return getAngle(coord1,coord2,coord3);

}

double cmeasure::getBiSector(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame)
{
    ccoordinates coord1,coord2,coord3;


    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);
    coord3=*atom3->getCoordinates(frame);

    return getBiSector(coord1,coord2,coord3);


}

double cmeasure::getNBiSector(cAtom *atom1, cAtom *atom2, cAtom *atom3, int frame)
{
    ccoordinates coord1,coord2,coord3;


    coord1=*atom1->getCoordinates(frame);
    coord2=*atom2->getCoordinates(frame);
    coord3=*atom3->getCoordinates(frame);

    return getNBiSector(coord1,coord2,coord3);

}

double cmeasure::safeAcos(double x)
{
    if (x < -1.0)
    {
        x = -1.0 ;
    }else if (x > 1.0)
    {
        x = 1.0 ;
    }
    return acos (x)* 180.0 / pi ;

}


double cmeasure::getBond(ccoordinates & coord1, ccoordinates & coord2)
{


    double dis;

    dis=sqrt(pow(coord1.getX()-coord2.getX(),2)+pow(coord1.getY()-coord2.getY(),2)+pow(coord1.getZ()-coord2.getZ(),2));

    return dis;

}

double cmeasure::getAngle(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3)
{

    ccoordinates vec1,vec2;

    vec1=coord1-coord2;
    vec2=coord3-coord2;

    return vecAngle(vec1,vec2);

}

double cmeasure::getBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3)
{
     ccoordinates vec1,vec2,vec3;

     vec1=coord1-coord2;
     vec2=coord3-coord2;

     double l1=vecLength(vec1);
     double l2=vecLength(vec2);



     vec1=vec1/l1;
     vec2=vec2/l2;

     vec3=vec1+vec2;


     double l3=vecLength(vec3);

     vec3=vec3/l3;


     return vecAngle(vec3,vec1);

}

double cmeasure::getNBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3)
{
    ccoordinates vec1,vecN;


    vec1=vecBiSector(coord1,coord2,coord3);

    vecN(0.0,0.0,1.0);



    return vecAngle(vec1,vecN);

}

ccoordinates cmeasure::vecBiSector(ccoordinates &coord1, ccoordinates &coord2, ccoordinates &coord3)
{
    ccoordinates vec1,vec2,vec3;


    vec1=coord1-coord2;
    vec2=coord3-coord2;
    double l1=vecLength(vec1);
    double l2=vecLength(vec2);


    vec1=vec1/l1;
    vec2=vec2/l2;


    vec3=vec1+vec2;

    double l3=vecLength(vec3);



    vec3=vec3/l3;

    return vec3;

}

double cmeasure::vecLength(ccoordinates &vec1)
{
    double dis;

    dis=sqrt(pow(vec1.getX(),2)+pow(vec1.getY(),2)+pow(vec1.getZ(),2));

    return dis;

}

double cmeasure::vecAngle(ccoordinates &vec1, ccoordinates &vec2)
{
    double l1=vecLength(vec1);
    double l2=vecLength(vec2);

    double dot=vec1*vec2;

    double param=dot/(l1*l2);


    return safeAcos(param);

}



