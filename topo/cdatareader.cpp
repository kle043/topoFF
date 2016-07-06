#include "cdatareader.h"

cdataReader::cdataReader(csystem *sys, string file, readInput *inp)
{

    inp->clearVec();
    string sztypeId,resname,name,names,type,szcharge,szmass,dummy,field,temp,szresid,szIdx1,szIdx2,szIdx3,szIdx4,szX,szY,szZ;
    ifstream inFile(file.c_str());
    int natoms,nbonds,nangles,ndihedrals,nimpropers,ntypes,btypes,atypes,dtypes,imtypes;

    if (inFile.good())
    {
        while(getline(inFile,temp))
        {

            //cout <<temp<<endl;



            if(temp.find("atoms")!=std::string::npos)
            {

                istringstream ss(temp);             
                ss>> field;
                //cout<<field<<endl;
                natoms=atoi(field.c_str());
                //cout<<"found \n";

            }


            if(temp.find("bonds")!=std::string::npos)
            {

                istringstream ss(temp);
                ss>> field;
                //cout<<field<<endl;
                nbonds=atoi(field.c_str());


            }




            if(temp.find("angles")!=std::string::npos)
            {

                istringstream ss(temp);
                ss>> field;
                //cout<<field<<endl;
                nangles=atoi(field.c_str());
            }

            if(temp.find("dihedrals")!=std::string::npos)
            {

                istringstream ss(temp);
                ss>> field;
                //cout<<field<<endl;
                ndihedrals=atoi(field.c_str());
            }

            if(temp.find("impropers")!=std::string::npos)
            {

                istringstream ss(temp);
                ss>> field;
                //cout<<field<<endl;
                nimpropers=atoi(field.c_str());
            }

            if(temp.find("atom types")!=std::string::npos)
            {
                istringstream ss(temp);
                ss>> field>>dummy;
               // cout<<field<<endl;

                ntypes=atoi(field.c_str());

            }

            if(temp.find("bond types")!=std::string::npos)
            {
                istringstream ss(temp);
                ss>> field>>dummy;
                //cout<<field<<endl;

                btypes=atoi(field.c_str());

            }
            if(temp.find("angle types")!=std::string::npos)
            {
                istringstream ss(temp);
                ss>> field>>dummy;
               // cout<<field<<endl;
                atypes=atoi(field.c_str());
            }

            if(temp.find("dihedral types")!=std::string::npos)
            {
                istringstream ss(temp);
                ss>> field>>dummy;
                //cout<<field<<endl;
                dtypes=atoi(field.c_str());
            }
            if(temp.find("improper types")!=std::string::npos)
            {
                istringstream ss(temp);
                ss>> field>>dummy;
                //cout<<field<<endl;
                imtypes=atoi(field.c_str());
            }
            if(temp.find("xlo xhi")!=std::string::npos)
            {
                double l,h;
                vector<double> vecpbc;





                for (int i =0;i<3;i++)
                {
                    istringstream ss(temp);

                    ss>> l>>h>>dummy>>dummy;

                    getline(inFile,temp);
                    vecpbc.push_back(l);
                    vecpbc.push_back(h);


                }

                sys->setPBC(vecpbc.at(0),vecpbc.at(1),vecpbc.at(2),vecpbc.at(3),vecpbc.at(4),vecpbc.at(5));



            }

            if(temp.find("Bond Coeffs")!=std::string::npos)
            {
                getline(inFile,temp);

                for (int i=0;i<btypes;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>dummy>>szIdx1>>names;

                    inp->addBond(atoi(szIdx1.c_str()),names);

                 //   cout<<dummy<<" "<<szIdx1<<" "<<names<<endl;

                }
           }

            if(temp.find("Angle Coeffs")!=std::string::npos)
            {
                getline(inFile,temp);

                for (int i=0;i<atypes;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>dummy>>szIdx1>>names;
                    inp->addAngle(atoi(szIdx1.c_str()),names);



                }
           }

            if(temp.find("Dihedral Coeffs")!=std::string::npos)
            {
                getline(inFile,temp);

                for (int i=0;i<dtypes;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>dummy>>szIdx1>>names;
                    inp->addDihedral(atoi(szIdx1.c_str()),names);



                }
           }

            if(temp.find("Improper Coeffs")!=std::string::npos)
            {
                getline(inFile,temp);



                for (int i=0;i<imtypes;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>dummy>>szIdx1>>names;
                    inp->addImproper(atoi(szIdx1.c_str()),names);


                    //cout<<dummy<<" i "<<szIdx1<<" "<<names<<endl;

                }
           }




            if(temp.find("Masses")!=std::string::npos)
            {
                getline(inFile,temp);

                for (int i=0;i<ntypes;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>szIdx1>>szmass>>dummy>>name;
                    vecMasses.push_back(atof(szmass.c_str()));
                    vecNames.push_back(name);
                    //cout<<dummy<<" s "<<szmass<<" "<<vecMasses.size()<<" "<<name<<endl;
                    inp->addPair(atoi(szIdx1.c_str()),name);

                }
           }



            if(temp.find("Atoms")!=std::string::npos)
            {
                getline(inFile,temp);

                for (int i=0;i<natoms;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);

                    ss>>szIdx1>>szresid>>sztypeId>>szcharge>>szX>>szY>>szZ>>dummy>>name>>resname;

                    int idx=atoi(szIdx1.c_str());
                    int iTy=atoi(sztypeId.c_str());

                    sys->addAtom(idx,atoi(szresid.c_str()),resname,vecNames.at(iTy-1),type,atof(szcharge.c_str()),vecMasses.at(iTy-1),iTy);

                    //cout<<dummy<<" "<<szresid<<" "<<szindex<<" "<<szcharge<<" "<<szX<<" "<<szY<<" "<<szZ<<" "<<dummy<<" "<<name<<" "<<resname<<endl;
                    sys->addCoord(idx-1,atof(szX.c_str()),atof(szY.c_str()),atof(szZ.c_str()));

                }
           }


            if(temp.find("Bonds")!=std::string::npos)
            {

                getline(inFile,temp);



                for (int i=0;i<nbonds;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);


                    ss>>dummy>>sztypeId>>szIdx1>>szIdx2;


                    sys->addBond(atoi(sztypeId.c_str()),atoi(szIdx1.c_str()),atoi(szIdx2.c_str()));





                    //cout<<temp<<endl;
                    //ss>>

                }


            }

            if(temp.find("Angle")!=std::string::npos)
            {

                getline(inFile,temp);



                for (int i=0;i<nangles;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);
                    ss>>dummy>>sztypeId>>szIdx1>>szIdx2>>szIdx3;
                    //cout<<szangle1<<" "<<szangle2<<" "<<szangle3<<endl;
                    sys->addAngle(atoi(sztypeId.c_str()),atoi(szIdx1.c_str()),atoi(szIdx2.c_str()),atoi(szIdx3.c_str()));

                }


            }
            if(temp.find("Dihedrals")!=std::string::npos)
            {

                getline(inFile,temp);

                for (int i=0;i<ndihedrals;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);
                    ss>>dummy>>sztypeId>>szIdx1>>szIdx2>>szIdx3>>szIdx4;
                    //cout<<szangle1<<" "<<szangle2<<" "<<szangle3<<endl;
                    sys->addDihedral(atoi(sztypeId.c_str()),atoi(szIdx1.c_str()),atoi(szIdx2.c_str()),atoi(szIdx3.c_str()),atoi(szIdx4.c_str()));

                }
            }

            if(temp.find("Impropers")!=std::string::npos)
            {

                getline(inFile,temp);

                for (int i=0;i<nimpropers;i++)
                {
                    getline(inFile,temp);

                    istringstream ss(temp);
                    ss>>dummy>>sztypeId>>szIdx1>>szIdx2>>szIdx3>>szIdx4;

                    sys->addImproper(atoi(sztypeId.c_str()),atoi(szIdx1.c_str()),atoi(szIdx2.c_str()),atoi(szIdx3.c_str()),atoi(szIdx4.c_str()));

                }
            }

        }

    }else
    {
        cout <<"Hmmm, what file?\n"<<file<<endl;
        return;
    }

    inFile.close();

}

