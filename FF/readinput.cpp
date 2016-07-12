#include "readinput.h"

readInput::readInput(string fn):filename(fn)
{
    printii=false;
    string homedir = getenv("HOME");
    //path="/home/kle043/lammps/database/inputFiles/";
    path=homedir+"/md/database/inputFiles/";
    location=path+filename;
    instream.open(location.c_str());



    string file,line,szbonds;
    int tempId;
    double tempD;
    bool pure=false;
    vector<string> vecTemp;
    string tempName,temp,mix1,mix2;
    enum inputType {pair,bondCheck,angleCheck,mixCheck,mixGeo,filesCheck,ii,ij,dihedral,improper,fep,remove} state;

    state=filesCheck;

    cout<<"Reading input file\n";
    cout<<"File(s): ";


    if (instream.is_open())
    {

        while(!instream.eof())
        {

            instream>>temp;
            tempName="";

            if(instream.eof()) break;




               // cout <<" f "<<temp<<endl;
            if(temp.substr(0,1)=="#")
            {
                getline(instream,line);
            }else
            {

                if (temp=="Pair")
                {
                    instream>>temp>>temp;
                    state=pair;
                }else if (temp=="mix")
                {
                    state=mixCheck;
                    instream>>temp;
                }else if (temp=="fep")
                {
                    cout <<"fep"<<endl;
                    state=fep;
                    instream>>temp;
                }else if (temp=="mixGeo")
                {
                    state=mixGeo;
                    instream>>temp;
                }else if (temp=="Bond")
                {
                    instream>>temp>>temp;
                    state=bondCheck;
                }else if (temp=="Angle")
                {
                    instream>>temp>>temp;
                    state=angleCheck;

                }else if (temp=="Dihedral")
                {
                    instream>>temp>>temp;
                    state=dihedral;

                }else if (temp=="Improper")
                {
                    instream>>temp>>temp;
                    state=improper;
                    //cout<<"improper "<<endl;

                }else if (temp=="remove")
                {
                    //cout<<endl;
                    state=remove;

                }else if(temp=="write")
                {
                    instream>>temp;

                    if(temp=="ii")
                    {
                        state=ii;
                    }else
                    {
                        state=ij;
                    }

                }else
                {

                }

                switch (state) {
                case filesCheck:
                {
                    files.push_back(temp);
                    cout<<temp<<" ";

                    std::size_t found =temp.find(".pure.");

                    if(pure)
                    {
                        cout<<"\n\nPure file not last, can give wrong mixing. \n\n";
                    }

                    if (found!=std::string::npos)
                    {
                        pure=true;

                    }

                    break;
                }
                case mixCheck:
                {
                    mix2=temp;
                    instream>>mix1;
                    vecMix.push_back(new cmixAtoms(mix1,mix2,"LB"));
                    //cout<<"Mixing "<<mix1<<" "<<(*(vecMix.end()-1))->getMixing()<<endl;
                    break;

                }
                case mixGeo:
                {
                    mix2=temp;
                    instream>>mix1;
                    vecMix.push_back(new cmixAtoms(mix1,mix2,"geo"));
                //    cout<<"Mixing "<<mix1<<" "<<mix2<<endl;
                    break;

                }
                case fep:
                {
                    mix2=temp;

                    instream>>mix1>>temp;
                    tempD=atof(temp.c_str());
                    vecFep.push_back(new fepAtoms(mix1,mix2,tempD));
                    //cout<<"Fep "<<mix1<<" "<<mix2<<" "<<tempD<<" "<<temp<<endl;
                    break;

                }
                case pair:
                {

                    tempId=atoi(temp.c_str());
                    instream>>tempName;
                  //  cout <<"Pair "<<temp<<" "<<tempName<<endl;
                    vecPair.push_back(new input(tempId,tempName));
                    break;
                }
                case bondCheck:
                {
                    tempId=atoi(temp.c_str());
                    instream>>szbonds;
                //    cout <<"Bond "<<tempId<<" "<<szbonds<<endl;
                    vecTemp=getNames(szbonds);
                    vecBonds.push_back(new input(tempId,vecTemp.at(0),vecTemp.at(1)));
                    break;

                }
                case dihedral:
                {
                    //cout<<"Dihedral\n";
                    tempId=atoi(temp.c_str());
                    instream>>szbonds;
              //      cout <<"Angle "<<tempId<<" "<<szbonds<<endl;
                    vecTemp=getNames(szbonds);
                    vecDihedral.push_back(new input(tempId,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2),vecTemp.at(3),false));
                    break;
                }
                case improper:
                {
                    tempId=atoi(temp.c_str());
                    instream>>szbonds;
                    //cout <<" "<<tempId<<" "<<szbonds<<endl;
                    vecTemp=getNames(szbonds);
                    vecImproper.push_back(new input(tempId,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2),vecTemp.at(3),true));
                    break;
                }
                case ii:
                {
                    printii=true;
                   // cout <<" style ii\n";

                    break;

                }
                case ij:
                {

                    //cout <<" style ij\n";
                    break;

                }
                case remove:
                {
                    string str;
                    getline(instream, str);

                    enum removeType {stop,bond,angle,atom,improper} rmType;



                    istringstream ss(str);
                    string num;

                    if(temp=="atom") rmType=atom;
                    if(temp=="bond") rmType=bond;
                    if(temp=="angle") rmType=angle;
                    if(temp=="angle") rmType=improper;
                    //cout<<temp<<endl;

                    while(ss >> num)
                    {




                        switch (rmType) {
                        case atom:
                        {
                            cout <<"\nremoving atom "<<num<<endl;
                            vecRmAt.push_back(atoi(num.c_str()));
                            break;
                        }
                        case bond:
                        {
                            cout <<"\nremoving bond "<<num<<endl;
                            vecRmBn.push_back(atoi(num.c_str()));
                            break;
                        }
                        case angle:
                        {
                            cout <<"\nremoving angle "<<num<<endl;
                            vecRmAn.push_back(atoi(num.c_str()));
                            break;

                        }
                        case improper:
                        {
                            cout <<"\nremoving improper "<<num<<endl;
                            vecRmIm.push_back(atoi(num.c_str()));
                            break;
                        } default:
                            break;
                        }



                    }

                   // cout<<endl;



                    break;

                }
                case angleCheck:
                {
                    tempId=atoi(temp.c_str());
                    instream>>szbonds;
              //      cout <<"Angle "<<tempId<<" "<<szbonds<<endl;
                    vecTemp=getNames(szbonds);
                    vecAngles.push_back(new input(tempId,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2)));
                    break;

                }default:
                    break;
                }
            }

        }
    }else
    {
        throw invalid_argument("Could not open input file");

    }

    cout<<"\n\n";

}

void readInput::clearVec()
{
    vecPair.clear();
    vecBonds.clear();
    vecAngles.clear();
    vecDihedral.clear();
    vecImproper.clear();
}

void readInput::addPair(int id, string sz)
{
    vecPair.push_back(new input(id,sz));

}

void readInput::addBond(int id, string sz)
{
    vector<string> vecTemp=getNames(sz);
    vecBonds.push_back(new input(id,vecTemp.at(0),vecTemp.at(1)));

}

void readInput::addAngle(int id, string sz)
{
    vector<string> vecTemp=getNames(sz);
    vecAngles.push_back(new input(id,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2)));

}

void readInput::addDihedral(int id, string sz)
{
    vector<string> vecTemp=getNames(sz);
    vecDihedral.push_back(new input(id,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2),vecTemp.at(3),false));


}

void readInput::addImproper(int id, string sz)
{
    vector<string> vecTemp=getNames(sz);
    vecImproper.push_back(new input(id,vecTemp.at(0),vecTemp.at(1),vecTemp.at(2),vecTemp.at(3),true));

}

readInput::~readInput()
{
    for (it=vecPair.begin();it!=vecPair.end();it++)
    {
        delete *it;
    }
    for (it=vecBonds.begin();it!=vecBonds.end();it++)
    {
        delete *it;
    }

    for (it=vecAngles.begin();it!=vecAngles.end();it++)
    {
        delete *it;
    }
    for (it=vecDihedral.begin();it!=vecDihedral.end();it++)
    {
        delete *it;
    }
    for (it=vecImproper.begin();it!=vecImproper.end();it++)
    {
        delete *it;
    }
    for (itFep=vecFep.begin();itFep!=vecFep.end();itFep++)
    {
        delete *itFep;
    }

    for (itMix=vecMix.begin();itMix!=vecMix.end();itMix++)
    {
        delete *itMix;
    }

}

vector<string> readInput::getNames(string in)
{
    vector<string> result;



    string::iterator itStart=in.begin();
    string::iterator it;
    for (it=in.begin();it!=in.end();it++)
    {
        if (*it=='-')
        {
           string temp(itStart,it);
           itStart=it+1;
         //  cout<<temp<<" get\n";
           result.push_back(temp);

        }
    }
    string temp(itStart,it);
   // cout<<temp<<" get\n";
    result.push_back(temp);

    return result;
}
