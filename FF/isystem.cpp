#include "isystem.h"

void isystem::readTrajectory(string filename, int b, int e, int skip, bool wrap)
{
    int idx;
    int tmp=skip-1;
    DCD_R dcdf(filename.c_str());

    xmin=FLT_MAX;
    xmax=FLT_MIN;
    ymin=FLT_MAX;
    ymax=FLT_MIN;
    zmin=FLT_MAX;
    zmax=FLT_MIN;
    const float *x,*y,*z;
    float xw,yw,zw;
    double progress=0;

    dcdf.read_header();
    //dcdf.printHeader();



    Nframes=dcdf.getNFILE();

    if(e>Nframes || e==0)
    {
        e=Nframes;
    }



    cout<<"# Started reading dcd file\n";
    Nframes=0;

    for(int i=0;i<e;i++)
    {

        progress=100*Nframes/(e-b);

        cout<<"\r# " <<progress<<"  % of file read"<<flush;

        dcdf.read_oneFrame();

        if(i==0)
        {
            pbcXh=*(dcdf.getPbc());
            pbcXl=*(dcdf.getPbc()+1);
            pbcYh=*(dcdf.getPbc()+2);
            pbcYl=*(dcdf.getPbc()+3);
            pbcZl=*(dcdf.getPbc()+4);
            pbcZh=*(dcdf.getPbc()+5);

        }

        if(i>b-1)
        {
            tmp++;

            if(i<=e && tmp==skip)
            {
                tmp=-1;

                x=dcdf.getX();
                y=dcdf.getY();
                z=dcdf.getZ();




                for (itAtom=vecAtoms.begin();itAtom!=vecAtoms.end();itAtom++)
                {


                    idx=(*itAtom)->getIdx();

                    if (wrap)
                    {

                        xw=fmod(*(x+idx-1),pbcXh);
                        yw=fmod(*(y+idx-1),pbcYh);
                        zw=fmod(*(z+idx-1),pbcZh);
                        if(xw<pbcXl)
                        {
                            xw+=pbcXh;
                        }

                        if(yw<pbcYl)
                        {
                            yw+=pbcYh;
                        }if(xw<pbcZl)
                        {
                            zw+=pbcZh;
                        }

                        //if (idx==8952)
                        //{
                        //    cout<<(*itAtom)->getName()<<" "<<(*itAtom)->getIdx()<<" "<<xw<<" "<<yw<<" "<<zw<<endl;
                        //    cout<<*(x+idx-1)<<" "<<*(y+idx-1)<<" "<<*(z+idx-1)<<endl;
                        //}
                        (*itAtom)->addCoord(xw,yw,zw);


                    }else
                    {



                        (*itAtom)->addCoord(*(x+idx-1),*(y+idx-1),*(z+idx-1));

                        if(*(x+idx-1)>xmax)
                        {
                            xmax=*(x+idx-1);

                        }
                        if(*(x+idx-1)<xmin)
                        {
                            xmin=*(x+idx-1);

                        }
                        if(*(y+idx-1)>ymax)
                        {
                            ymax=*(y+idx-1);

                        }
                        if(*(y+idx-1)<ymin)
                        {
                            ymin=*(y+idx-1);

                        }
                        if(*(z+idx-1)>zmax)
                        {
                            zmax=*(z+idx-1);

                        }
                        if(*(z+idx-1)<zmin)
                        {
                            zmin=*(z+idx-1);

                        }

                    }




                }
                //cout <<"read"<<" "<<i<<" "<<e<<" "<<Nframes<<endl;
                Nframes++;
            }

            //cout<<skip<<" "<<tmp<<endl;

        }



    }

    progress=100*Nframes/(e-b);
    cout<<"\r# " <<progress<<"  % of file read"<<flush;

    cout<<endl;

    cout<<"# finished with dcd file\n";




        if(wrap)
        {
            xmin=pbcXl;
            xmax=pbcXh;
            ymin=pbcYl;
            ymax=pbcYh;
            zmin=pbcZl;
            zmax=pbcZh;
        }

        //cout <<"PBC "<<pbcXh<<" "<<pbcXl<<endl;

}

int isystem::numMol(string resname)
{
    for (itVecMol=vecVecMolecule.begin();itVecMol!=vecVecMolecule.end();itVecMol++)
    {
        if((*(*itVecMol)->begin())->getResname()==resname)
        {
            return (*itVecMol)->size();
        }
    }

    return 0;

}

int isystem::numMol_at(int i)
{
    if(i>vecVecMolecule.size()-1)
    {
         throw invalid_argument( "Molecule vector out of bounds" );

    }

    return vecVecMolecule.at(i)->size();


}

vector<cMolecule *> &isystem::getVecMol_name(string resname)
{
    for (itVecMol=vecVecMolecule.begin();itVecMol!=vecVecMolecule.end();itVecMol++)
    {
        if((*(*itVecMol)->begin())->getResname()==resname)
        {
            return **itVecMol;
        }
    }

}

vector<cMolecule *> &isystem::getVecMol_at(int i)
{
    if(i>vecVecMolecule.size()-1)
    {
         throw invalid_argument( "Molecule vector out of bounds" );

    }

    return *vecVecMolecule.at(i);




}


void isystem::printSummary()
{


    string frame="=";
    string side="=";
    string title=" SYSTEM ";
    string delimiter=": ";

    int shift=1;

    string lineA=side+" NATOMS   "+delimiter+to_string(num());
    string lineB=side+" NBONDS   "+delimiter+to_string(vecBonds.size());
    string lineANG=side+" NANGLES  "+delimiter+to_string(vecAngles.size());
    string lineNMol=side+" NMolTypes  "+delimiter+to_string(vecVecMolecule.size());
    string linePBC=side+" PBC      "+delimiter+"[ "+to_string(getPbcX())+" "+to_string(getPbcY())+" "+to_string(getPbcZ())+" ]";
    string lineLimitX=side+" LIMITS_X "+delimiter+"[ "+to_string(xmin)+"  "+to_string(xmax)+" ]";
    string lineLimitY=side+" LIMITS_Y "+delimiter+"[ "+to_string(ymin)+"  "+to_string(ymax)+" ]";
    string lineLimitZ=side+" LIMITS_Z "+delimiter+"[ "+to_string(zmin)+"  "+to_string(zmax)+" ]";
    string lineFRAME=side+" NFRAMES  "+delimiter+to_string(Nframes);


    int length=80-title.size();


    for (int i =0;i<length;i++)
    {
        cout<<frame;

        if(i==length/2)
        {
            cout<<title;
        }
    }
    cout<<endl;



    cout<<lineA<<setw(length+title.size()-lineA.size()-side.size()+shift)<<side<<endl;
    cout<<lineB<<setw(length+title.size()-lineB.size()-side.size()+shift)<<side<<endl;
    cout<<lineANG<<setw(length+title.size()-lineANG.size()-side.size()+shift)<<side<<endl;
    cout<<lineNMol<<setw(length+title.size()-lineNMol.size()-side.size()+shift)<<side<<endl;
    cout<<linePBC<<setw(length+title.size()-linePBC.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitX<<setw(length+title.size()-lineLimitX.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitY<<setw(length+title.size()-lineLimitY.size()-side.size()+shift)<<side<<endl;
    cout<<lineLimitZ<<setw(length+title.size()-lineLimitZ.size()-side.size()+shift)<<side<<endl;
    cout<<lineFRAME<<setw(length+title.size()-lineFRAME.size()-side.size()+shift)<<side<<endl;

    for (int i =0;i<length+title.size();i++)
    {
        cout<<frame;

    }
    cout<<endl;

}

void isystem::printMolecules()
{
    vector<cAtom*> vecA;

    for (itVecMol=vecVecMolecule.begin();itVecMol!=vecVecMolecule.end();itVecMol++)
    {
        for (itMol=(*itVecMol)->begin();itMol!=(*itVecMol)->end();itMol++)
        {
            if((*itMol)->getResname()=="h2o")
            {

            vecA=(*itMol)->getAtoms();

            cout<<(*itMol)->getResname()<<" "<<(*itMol)->numMol()<<" "<<(*itMol)->getMolMass()<<" ";

            for (itAtom=vecA.begin();itAtom!=vecA.end();itAtom++)
            {
                (*itAtom)->printTerminal();
            }

            cout<<endl;

            }

        }
    }

}







