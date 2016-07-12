#include "readff.h"
readFF::readFF(const vector<string> &f): files(f)
{

    string homedir = getenv("HOME");

    path=homedir+"/lammps/database/ffFiles/";

    enum inputType {lj,buck,bond,angle,charge,dihedral,improper} state;
    enum bondType {harm,morse,defaultState} bondstate;
    enum dihedralType {opls,harmDi,defaultDihedral} dihedralstate;
    enum ImproperType {harmIm,cvff,defaultImproper} improperstate;
    cout << "Reading ff Files "<<endl;

    for (itFiles=files.begin();itFiles!=files.end();itFiles++)
    {

        cout << "Working on file "<<*itFiles<<endl;
        bondstate=defaultState;
        dihedralstate=defaultDihedral;
        improperstate=defaultImproper;
        location=path+*itFiles;
        instream.open(location.c_str());

        string line,stTemp,units[2],style;
        string name1,name2,name3,name4;
        double A,rho,C,req,K,col,d,n;
        double epsilon,sigma,alpha,k1,k2,k3,k4;
        bool defaultBond=1;
        string first;

        instream.precision(8);


        if (instream.is_open())
        {
            while(instream.is_open())
            {
                first="";

                instream >>first;

              // cout<<first<<endl;

                if (instream.eof())
                {
                    break;
                }

                if (first.at(0)=='#')
                {
                    getline(instream,line);

                }else
                {
                    if(first=="units")
                    {
                      instream>>units[0]>>units[1];
                //     cout <<"Units are "<< units[0]<<" "<<units[1]<<endl;

                    }else if(first.substr(0,5)=="buck/")
                    {
                        style=first;
                  //     cout << "\nStyle are "<<style<<endl;
                       state=buck;
                    }else if(first.substr(0,3)=="lj/")
                    {
                        style=first;
                        state=lj;
                    //   cout << "\nStyle are "<<style<<endl;

                    }else if(first.substr(0,4)=="ljAB")
                    {
                        style=first;
                        state=lj;

                       // cout<<"LJ AB\n";

                    }else if (first.substr(0,5)=="bond_")
                    {
                        state=bond;
                        instream>>units[0];

                    }else if (first.substr(0,9)=="dihedral_")
                    {
                        state=dihedral;
                        instream>>units[0];

                    }else if (first.substr(0,9)=="improper_")
                    {
                       // cout<<"imp"<<endl;
                        state=improper;
                        instream>>units[0];
                    }else if (first.substr(0,6)=="angle_")
                    {
                        state=angle;
                        instream>>units[0];


                    }else if(first=="group")
                    {
                        instream>>name1;
                        getline(instream,line);
                        vecGroup.push_back(new Cgroup(name1,getNames(line)));

                    }else if(first=="charge")
                    {
                        state=charge;

                    }else
                    {

                        switch (state) {
                        case lj:
                        {
                            name1=first;
                            instream >>name2>>epsilon>>sigma;
                          //  cout<<name2<<" "<<epsilon<<endl;
                            vecPotential.push_back(new lennardJones(name1,name2,style,units[0],units[1],*itFiles,epsilon,sigma));
                            break;
                        }
                        case buck:
                        {
                            name1=first;
                            instream>>name2>>A>>rho>>C;
                            vecPotential.push_back(new buckingham (name1,name2,style,units[0],units[1],*itFiles,A,rho,C));
                            break;

                        }case charge:
                        {
                            instream>>col;
                            vecAtom.push_back(new atom(first,col));
                            break;


                        }case bond:
                        {

                            if (first=="harmonic")
                            {
                                bondstate=harm;
                                defaultBond=0;
                                break;

                            }else if(first=="morse")
                            {
                                bondstate=morse;
                                defaultBond=0;
                                break;
                            }

                            switch (bondstate) {
                            case harm:
                            {
                                name1=first;
                                style="harmonic";
                                instream>>name2>>K>>req;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecBonds.push_back(new harmonic_bond(name1,name2,K,req,units[0],*itFiles));
                                break;

                            }
                            case morse:
                            {
                                style="morse";
                                name1=first;
                                instream>>name2>>K>>alpha>>req;
                                vecBonds.push_back(new morse_bond(name1,name2,K,req,units[0],*itFiles,alpha));
                              //  cout<<"Morse"<<endl;
                               // cout<<name1<<" "<<" "<<name2<<" "<<K<<" "<<alpha<<" "<<req<<endl;
                                break;

                            }
                            default:
                            {
                                name1=first;
                                instream>>name2>>K>>req;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecBonds.push_back(new harmonic_bond(name1,name2,K,req,units[0],*itFiles));
                                break;

                            }
                            }
                            break;
                        }
                        case angle:
                        {
                            name1=first;
                            instream>>name2>>name3>>K>>req;
//                            cout<<"Angle "<< name1<<" "<<name2<<" "<<name3<<" "<<K<<" "<<req<<endl;
                            vecAngles.push_back(new harmonic_angle(name1,name2,name3,K,req,units[0],*itFiles));
                            break;
                        }
                        case dihedral:
                        {
                            if (first=="harmonic")
                            {
                                dihedralstate=harmDi;
                                break;

                            }else if(first=="opls")
                            {
                                dihedralstate=opls;
                                break;
                            }

                            switch (dihedralstate) {
                            case harmDi:
                            {
                                name1=first;
                                style="harmonic";
                                instream>>name2>>name3>>name4>>K>>d>>n;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecDihedrals.push_back(new harmonic_dihedral(name1,name2,name3,name4,K,d,n,units[0],*itFiles));
                                break;

                            }
                            case opls:
                            {
                                style="opls";
                                name1=first;
                                instream>>name2>>name3>>name4>>k1>>k2>>k3>>k4;
                                vecDihedrals.push_back(new opls_dihedral(name1,name2,name3,name4,k1,k2,k3,k4,units[0],*itFiles));
                                //cout<<"opls"<<endl;
                                //cout<<name1<<" "<<" "<<name2<<" "<<k1<<" "<<k4<<endl;
                                break;

                            }
                            default:
                            {
                                name1=first;
                                style="harmonic";
                                instream>>name2>>name3>>name4>>K>>d>>n;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecDihedrals.push_back(new harmonic_dihedral(name1,name2,name3,name4,K,d,n,units[0],*itFiles));
                                break;

                            }
                            }
                            break;
                        }
                        case improper:
                        {
                            //cout<<"case improper "<<first<<endl;
                            if (first=="harmonic")
                            {
                                improperstate=harmIm;
                                break;

                            }else if(first=="cvff")
                            {
                                improperstate=cvff;
                                break;
                            }

                            switch (improperstate) {
                            case harmIm:
                            {
                                name1=first;
                                style="harmonic";
                                instream>>name2>>name3>>name4>>K>>n;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecImproper.push_back(new harmonic_improper(name1,name2,name3,name4,K,n,units[0],*itFiles));
                                break;

                            }
                            case cvff:
                            {
                                name1=first;
                                style="cvff";
                                instream>>name2>>name3>>name4>>K>>d>>n;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecImproper.push_back(new cvff_improper(name1,name2,name3,name4,K,d,n,units[0],*itFiles));
                                //cout<<vecImproper.size()<<endl;
                                break;

                            }
                            default:
                            {
                                name1=first;
                                style="harmonic";
                                instream>>name2>>name3>>name4>>K>>d;
  //                              cout<<"Bond "<< name1<<" "<<name2<<" "<<K<<" "<<req<<endl;
                                vecImproper.push_back(new harmonic_improper(name1,name2,name3,name4,K,d,units[0],*itFiles));
                                break;

                            }
                            }
                            break;
                        }

                        default: break;
                        } //case end

                    }
                }



            }



        }else
        {
            string n="Could not open ff file"+*itFiles;
            throw invalid_argument(n);
            cout<<"ERROR:: Could not open file!!!"<<endl;
        }



        cout << "finished \n\n";

        processFile.clear();

        instream.close();




    }






}

readFF::~readFF()
{
   /* for (itPotential=vecPotential.begin();itPotential!=vecPotential.end();itPotential++)
    {
        delete *itPotential;
    }
    for (itPotential=vecAngles.begin();itPotential!=vecAngles.end();itPotential++)
    {
        delete *itPotential;
    }
    for (itPotential=vecBonds.begin();itPotential!=vecBonds.end();itPotential++)
    {
        delete *itPotential;
    }

    for (itAtom=vecAtom.begin();itAtom!=vecAtom.end();itAtom++)
    {
        delete *itAtom;
    }*/

    //Cfullpotential is resposible for killing left over objects

}

vector<string> readFF::getNames(string in)
{
    vector<string> result;
    bool check=false;
    string::iterator itStart=in.begin();
    string::iterator it;
    for (it=in.begin();it!=in.end();it++)
    {
       if (*it==' '&&check)
       {
          check=false;
          string temp(itStart,it);
          result.push_back(temp);

   //     cout << temp<< " RESULT\n";

       }else if(*it!=' '&&!check)
       {
           itStart=it;
           check=true;
       }



    }

    if (!isspace(*(in.end()-1)))
    {
           string temp(itStart,in.end());
           result.push_back(temp);
         //  cout << temp<< " END\n";
    }


    return result;

}
