#include "cxmlwriter.h"

cxmlwriter::cxmlwriter()
{

}

void cxmlwriter::write(isystem *sys1, string filename,bool isbody)
{
    sys=sys1;
    double M=1;
    double E=1;
    double D=1;
    filename=filename+".xml";
    ofstream out(filename.c_str());
    out.precision(12);;
    pbcx=sys->getPbcX();
    pbcy=sys->getPbcY();
    pbcz=sys->getPbcZ();
    pbcx/=2;
    pbcy/=2;
    pbcz/=2;

    out<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl;
    out<<"<hoomd_xml version=\"1.4\">"<<endl;
    out<<"<configuration time_step=\"0\" natoms=\""<<sys->num()<<"\">"<<endl;

    out<<"<box lx=\""<<sys->getPbcX()<<"\""
       <<" ly=\""<<sys->getPbcY()<<"\""
       <<" lz=\""<<sys->getPbcZ()<<"\" xy=\"0\" xz=\"0\" yz=\"0\"/>"<<endl;




   // double charge

     factorCharge=Ec/sqrt((4*PI*Ps*D*1e-10*1e3*E)/NA); // When writing mod charges in xml using kj/mol as energy and so on.

    //factorCharge=1.0;

    //cout<<setprecision(15)<<factorCharge<<endl;





    ccoordinates *coord;
    cAtom * ptrAt;

    vecMol=sys->getVecMol();

    sys->wrapCoordinates();



    int i=0;

    string type,mass,charge;

    out<<"<type num=\""<<sys->num()<<"\">"<<endl;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            ptrAt=*itAtom;
            out<<ptrAt->getName()<<" ";
            ptrAt->setIdx(i);

            i++;
        }

        out<<endl;

    }

    out<<"</type>"<<endl;

    out<<"<mass>"<<endl;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            ptrAt=*itAtom;
            out<<ptrAt->getMass()/M<<" ";

        }
        out<<endl;

    }

    out<<"</mass>"<<endl;

    out<<"<charge>"<<endl;


    double netcharge=0.00;
    double ch;

   // balanceCharge();


    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            ptrAt=*itAtom;

            out<<fixed<<ptrAt->getCharge()*factorCharge<<" ";
            netcharge+=ptrAt->getCharge()*factorCharge;



        }
        out<<endl;
        //cout<<netcharge<<endl;




    }
    if(fabs(netcharge)>1e-8)
    {

       cout<< " Net charge ="<<netcharge<<endl;

    }

    out<<"</charge>"<<endl;


    out<<"<position>"<<endl;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            coord=(*itAtom)->getCoordinates(0);

            out<<coord->getX()<<" "<<coord->getY()<<" "<<coord->getZ()<<endl;

        }
    }

    out<<"</position>"<<endl;

    int body=-1;


    out<<"<body>"<<endl;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        if (isbody)
        {
            body++;

        }

        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            ptrAt=*itAtom;
            out<<body<<" ";

        }
        out<<endl;

    }

    out<<"</body>"<<endl;



    out<<"<bond>"<<endl;

    cBond * ptrBn;

    i=1;
    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecBonds=(*itMol)->getVecBonds();


        for (itBond=vecBonds.begin();itBond!=vecBonds.end();itBond++)
        {
            ptrBn=*itBond;

            out<<ptrBn->getType()<<" "<<ptrBn->getIdx1()<<" "<<ptrBn->getIdx2()<<endl;

        }
    }

    out<<"</bond>"<<endl;



    if(!sys->getAnglePot().empty())
    {
        cAngle * ptrAn;

        out<<"<angle>"<<endl;

        for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
        {
            vecAngles=(*itMol)->getVecAngles();


            for (itAngle=vecAngles.begin();itAngle!=vecAngles.end();itAngle++)
            {

                ptrAn=*itAngle;

                out<<ptrAn->getType()<<" "<<ptrAn->getIdx1()<<" "<<ptrAn->getIdx2()<<" "<<ptrAn->getIdx3()<<endl;


            }
        }

        out<<"</angle>"<<endl;
    }

    if(sys->NDihedrals()>0)
    {

        cDihederal * ptrDi;
        out<<"<dihedral>"<<endl;

        for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
        {
            vecDihedrals=(*itMol)->getVecDihedrals();


            for (itDihedral=vecDihedrals.begin();itDihedral!=vecDihedrals.end();itDihedral++)
            {

                ptrDi=*itDihedral;

                out<<ptrDi->getType()<<" "<<ptrDi->getIdx1()<<" "<<ptrDi->getIdx2()<<" "<<ptrDi->getIdx3()<<" "<<ptrDi->getIdx4()<<endl;


            }
        }

        out<<"</dihedral>"<<endl;
    }

    if(sys->NImpropers()>0)
    {

        cImproper * ptrIm;
        out<<"<improper>"<<endl;

        for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
        {
            vecImpropers=(*itMol)->getVecImpropers();


            for (itImproper=vecImpropers.begin();itImproper!=vecImpropers.end();itImproper++)
            {

                ptrIm=*itImproper;

                out<<ptrIm->getType()<<" "<<ptrIm->getIdx1()<<" "<<ptrIm->getIdx2()<<" "<<ptrIm->getIdx3()<<" "<<ptrIm->getIdx4()<<endl;


            }
        }

        out<<"</improper>"<<endl;
    }
    /*out<<"<image>"<<endl;
    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        vecAtoms=(*itMol)->getAtoms();

        for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
        {
            coord=(*itAtom)->getCoordinates(0);

            getImage(coord);


            out<<image[0]<<" "<<image[1]<<" "<<image[2]<<endl;




        }
    }
    out<<"</image>"<<endl;*/
    out<<"</configuration>"<<endl;
    out<<"</hoomd_xml>"<<endl;

    out.close();

    cout<<"xml file written, see "<<filename<<endl;



}

void cxmlwriter::getImage(ccoordinates *coord)
{


    if (coord->getX()>pbcx)
    {
         image[0]=-coord->getX()/pbcx;
    }else
    {
         image[0]=-coord->getX()/pbcx;
    }
    if (coord->getY()>pbcy)
    {
        image[1]=-coord->getY()/pbcy;
    }else
    {
        image[1]=-coord->getY()/pbcy;
    }
    if (coord->getZ()>pbcz)
    {
        image[2]=-coord->getZ()/pbcz;
    }else
    {
        image[2]=-coord->getZ()/pbcz;
    }










}

void cxmlwriter::balanceCharge()
{
    cAtom* ptrAtom;
    cMolecule *ptrMol;
    pair<string,int> p;

    double hoomdCharge=0;
    double charge=0;

    for(itMol=vecMol.begin();itMol!=vecMol.end();itMol++)
    {
        ptrMol=*itMol;

        p=ptrMol->getNAtomsMax();
        //cout<<setprecision(12)<<fixed<<ptrMol->getResname()<<" - ";
        hoomdCharge=getHoomdCharge(ptrMol,p.first);



        if(ptrMol->getNetCharge()==0)
        {
            setResHoomdCharge(ptrMol,p.first,hoomdCharge,p.second);
            //cout<<" "<<hoomdCharge<<endl;

        }


    }

}

void cxmlwriter::setResHoomdCharge(cMolecule *ptrMol, string name, double hoomdCharge, int natoms)
{
    vecAtoms=ptrMol->getAtoms();
    cAtom* ptrAtom;
    double charge=0;

    double frac,charge2;

    charge=-hoomdCharge/natoms;
    charge2=SetPrecision(charge,11);
    frac=fmod(hoomdCharge,charge);

    cout<<setprecision(12)<<fixed<<hoomdCharge<<" "<<charge<<endl;


    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        ptrAtom=*itAtom;

        if(name==ptrAtom->getName())
        {


            ptrAtom->setHCharge(charge);
            //cout<<ptrAtom->getName()<<" "<<charge<<" ";

        }




    }
    //cout<<" f "<<frac<<" ";

}

double cxmlwriter::getHoomdCharge(cMolecule * ptrMol,string name)
{
    vecAtoms=ptrMol->getAtoms();
    cAtom* ptrAtom;
    double hoomdcharge=0;
    double charge=0;

    for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
    {
        ptrAtom=*itAtom;

        if(name!=ptrAtom->getName())
        {
            charge=ptrAtom->getCharge()*factorCharge;
            hoomdcharge+=charge;
            charge=SetPrecision(charge,11);
            ptrAtom->setHCharge(charge);
            //cout<<ptrAtom->getName()<<" "<<charge<<" ";

        }


    }

    return hoomdcharge;

}

double cxmlwriter::SetPrecision(double value, double precision)
{
    return (floor((value * pow(10, precision) + 0.5)) / pow(10, precision));
}



