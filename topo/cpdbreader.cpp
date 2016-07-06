#include "cpdbreader.h"

cpdbReader::cpdbReader(csystem *sys, string file)
{
    string szindex,resname,name,type,szcharge,szmass,dummy,field,temp,szresid,szX,szY,szZ,dummyX;
    ifstream inFile(file.c_str());

    cout<<"Reading "<<file<<endl;

    int idx=1;
    if(sys->num()!=0)
    {
        idx=sys->num()+1;
    }


    if (inFile.good())
    {
        while(getline(inFile,temp))
        {



            std::size_t foundNATOMS = temp.find("ATOM");
            std::size_t foundHETATM = temp.find("HETATM");

            std::size_t foundCRYST = temp.find("CRYST");

            if (foundCRYST!=std::string::npos)
            {
                istringstream ss(temp);

                double pbcx,pbcy,pbcz;

                ss>>dummy>>pbcx>>pbcy>>pbcz;

               // cout<<dummy<<" "<<pbcx<<" "<<pbcy<<" "<<pbcz<<endl;


                sys->setPBC(0.0,pbcx,0.0,pbcy,0.0,pbcz);


            }




            if(foundNATOMS!=std::string::npos ||foundHETATM!=std::string::npos )
            {

                temp.erase(21,9);
                //temp.erase(58,temp.size()-58);

                istringstream ss(temp);

                //cout<<temp<<endl;

                foundNATOMS=string::npos;
                foundHETATM=string::npos;

                ss>>dummy>>dummy>>name>>resname>>szX>>szY>>szZ;



                //if(dummyX.size()!=1)
                //{
                //
                //    //cout <<dummyX<<" "<<dummyX.size()<<endl;
                //    string temp=szX;
                //    szX=dummy;
                //    dummy=szY;
                //    szY=temp;
                //    szZ=dummy;
                //
                //}




                sys->addAtom(idx,0,resname,name,type,atof(szcharge.c_str()),atof(szmass.c_str()),0);


                //cout<<szX<<" "<<szY<<" "<<szZ<<" "<<dummy<<" "<<name<<" "<<resname<<endl;
                //cout<<dummy<<" "<<szresid<<" "<<szindex<<" "<<szcharge<<" "<<szX<<" "<<szY<<" "<<szZ<<" "<<dummy<<" "<<name<<" "<<resname<<endl;
                sys->addCoord(idx-1,atof(szX.c_str()),atof(szY.c_str()),atof(szZ.c_str()));

                idx++;



            }




        }



    }else
    {
        cout <<"Hmmm, what file?\n"<<file<<endl;
        return;
    }

    inFile.close();

}

