#include "cffstream.h"

cffStream::cffStream(cSortPotential &pot)
{
    vecPa=pot.getPairPot();
    vecBn=pot.getBondPot();
    vecAn=pot.getAnglePot();
    vecIm=pot.getImproperPot();
    vecDi=pot.getDihedralPot();
    vecFepSites=pot.getFepSites();
    vecGroup=pot.getGroups();
    vecSite=pot.getChargePot();


}



void cffStream::writeLammps(string file)
{


    filename=file+".fflammps";

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        //cout<<cwd<<" kk "<<endl;
    }else
    {
        cout << "Could not print output\n";
        return;
    }
    path=cwd;
    path=path+"/";


    location=path+filename;
    outfile.open(location.c_str());
    outfile.precision(8);
    outfile.width(4);


    for (itPotential=vecPa.begin();itPotential!=vecPa.end();itPotential++)
    {
        (*itPotential)->print(outfile);
    }



    outfile<<"\n";
    for (itPotential=vecBn.begin();itPotential!=vecBn.end();itPotential++)
    {
        (*itPotential)->print(outfile);
    }
    outfile<<"\n";

    for (itPotential=vecAn.begin();itPotential!=vecAn.end();itPotential++)
    {
        (*itPotential)->print(outfile);
    }
    outfile<<"\n";


    for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
    {
        (*itPotential)->print(outfile);

    }
    outfile<<"\n";

    for (itPotential=vecIm.begin();itPotential!=vecIm.end();itPotential++)
    {
        (*itPotential)->print(outfile);

    }
    outfile<<"\n";



    for (itSite=vecSite.begin();itSite!=vecSite.end();itSite++)
    {
        (*itSite)->print(outfile);

    }

    outfile<<"\n\n";

    for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
    {
        (*itGroup)->print(outfile);
    }


    outfile.close();

    if(!vecFepSites.empty())
    {



        location=path+"/"+file+".fep";

        outfile.open(location.c_str());
        outfile<<"fix fADAPT all adapt/fep ${fepSteps} pair ";


        if((*vecFepSites.begin())->getLambda()==0.0)
        {
            outfile<<(*vecFepSites.begin())->getStyle()<<" lambda "<<(*vecFepSites.begin())->getId1()<<" "<<(*vecFepSites.begin())->getId2()<<" v_lambda &";
        }else
        {
            outfile<<(*vecFepSites.begin())->getStyle()<<" lambda "<<(*vecFepSites.begin())->getId1()<<" "<<(*vecFepSites.begin())->getId2()<<" v_down &";

        }
        outfile<<endl;

        for (itPotential=vecFepSites.begin()+1;itPotential!=vecFepSites.end()-1;itPotential++)
        {
            if((*itPotential)->getLambda()==0.0)
            {
                outfile<<setw(42)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_lambda &";
            }else
            {
                outfile<<setw(42)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_down &";

            }

            outfile<<endl;

        }

        if((*(vecFepSites.end()-1))->getLambda()==0.0)
        {
            outfile<<setw(42)<<right<<"pair "<<(*(vecFepSites.end()-1))->getStyle()<<" lambda "<<(*(vecFepSites.end()-1))->getId1()<<" "<<(*(vecFepSites.end()-1))->getId2()<<" v_lambda after yes #";

        }else
        {
            outfile<<setw(42)<<right<<"pair "<<(*(vecFepSites.end()-1))->getStyle()<<" lambda "<<(*(vecFepSites.end()-1))->getId1()<<" "<<(*(vecFepSites.end()-1))->getId2()<<" v_down after yes #";

        }



        outfile<<"\n\n";

        outfile<<"variable dlambda equal v_fepSteps/v_runtime\n";
        outfile<<"variable dDown equal -v_dlambda\n\n";

        outfile<<"compute cFEP all fep ${T_start} pair ";
        if((*vecFepSites.begin())->getLambda()==0.0)
        {
            outfile<< (*vecFepSites.begin())->getStyle()<<" lambda "<<(*vecFepSites.begin())->getId1()<<" "<<(*vecFepSites.begin())->getId2()<<" v_dlambda &";

        }else
        {
            outfile<< (*vecFepSites.begin())->getStyle()<<" lambda "<<(*vecFepSites.begin())->getId1()<<" "<<(*vecFepSites.begin())->getId2()<<" v_dDown &";

        }

        outfile<<endl;

        for (itPotential=vecFepSites.begin()+1;itPotential!=vecFepSites.end()-1;itPotential++)
        {
            if((*itPotential)->getLambda()==0.0)
            {
                outfile<<setw(37)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_dlambda &";

            }else
            {
                outfile<<setw(37)<<right<<"pair "<<(*itPotential)->getStyle()<<" lambda "<<(*itPotential)->getId1()<<" "<<(*itPotential)->getId2()<<" v_dDown &";

            }

            outfile<<endl;

        }


        if((*(vecFepSites.end()-1))->getLambda()==0.0)
        {
            outfile<<setw(37)<<right<<"pair "<<(*(vecFepSites.end()-1))->getStyle()<<" lambda "<<(*(vecFepSites.end()-1))->getId1()<<" "<<(*(vecFepSites.end()-1))->getId2()<<" v_dlambda volume yes #";

        }else
        {
            outfile<<setw(37)<<right<<"pair "<<(*(vecFepSites.end()-1))->getStyle()<<" lambda "<<(*(vecFepSites.end()-1))->getId1()<<" "<<(*(vecFepSites.end()-1))->getId2()<<" v_dDown volume yes #";

        }


        outfile<<"\n\n";



        outfile.close();
    }




    cout<<"Force Field written:: Look in "<<filename<<endl;
}

void cffStream::writeHoomd(string file)
{


    filename="setup.py."+file;
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        //cout<<cwd<<" kk "<<endl;
    }else
    {
        cout << "Could not print output\n";
        return;
    }
    path=cwd;
    path=path+"/";

    location=path+filename;
    outfile.open(location.c_str());
    outfile.precision(8);
    outfile.width(4);

    double energy=numeric_limits<double>::max();
    double dist;

    bool buck=false;
    bool lj=false;
    bool dihederal=false;
    bool opls=false;
    bool bnlj=false;
    bool harmDi=false;



    outfile<<"from hoomd_script import *\n";
    outfile<<"from hoomd_plugins import potentials\n\n";

    outfile<<"def ffSetup(system,r_cut=12.0):\n\n";
    //outfile<<"    ######### parameters ##########\n\n";
    //outfile<<"
    //outfile<<"    #kappa=0.0\n\n";

    outfile<<"    ######### Styles ##############\n\n";

    if(vecHasStyle(vecPa,"lj"))
    {
        lj=true;
        outfile<<"    lj = pair.lj(r_cut=r_cut)\n";
    }
    if(vecHasStyle(vecPa,"buck"))
    {
        buck=true;
        outfile<<"    buck = potentials.pair.buck(r_cut=r_cut)\n";
    }

    outfile<<"    #coul = pair.coul(r_cut=r_cut)\n";

    if(vecHasStyle(vecBn,"harmonic"))
    {

        outfile<<"    harmonic = bond.harmonic()\n";
    }else if(!vecBn.empty())
    {
        outfile<<"    harmonic = bond.harmonic()\n";
    }


    if(!vecDi.empty()&&!(*vecDi.begin())->getParameters().empty())
    {
        bnlj=true;

        outfile<<"    bnlj=potentials.bond.lj_coul()\n";
    }
    if(vecHasStyle(vecAn,"harmonic"))
    {
        outfile<<"    harmonic_angle = angle.harmonic()\n";
    }

    if(vecHasStyle(vecDi,"opls"))
    {
        opls=true;
        outfile<<"    opls_dihedral = dihedral.opls()\n";
    }

    if(vecHasStyle(vecIm,"harmonic"))
    {
        outfile<<"    harmonic_improper = improper.harmonic()\n";

    }
    if(vecHasStyle(vecIm,"cvff"))
    {
             outfile<<"    harmonic_dihedral = dihedral.harmonic()\n";
             harmDi=true;

    }

    outfile<<"\n\n";

    outfile<<"    ######### Default Parameters ############\n\n";

    if(lj||buck)
    {

        outfile<<"    ntypes=len(system.particles.types)\n";
        outfile<<"    for i in range(ntypes):\n";
        outfile<<"        for j in range(i,ntypes):\n";
        outfile<<"            A=system.particles.types[i]\n";
        outfile<<"            B=system.particles.types[j]\n";

        if(lj)
            outfile<<"            lj.pair_coeff.set(A,B,epsilon=0,sigma=1)\n";
        if(buck)
            outfile<<"            buck.pair_coeff.set(A,B,A=0,rho=0.2,C=0)\n";

            outfile<<"            #coul.pair_coeff.set(A,B, kappa=kappa)\n\n\n";
    }

    if(bnlj)
    {
        outfile<<"    snapshot = system.take_snapshot(bonds=True)\n";
        outfile<<"    ntypes=len(snapshot.bonds.types)\n";
        outfile<<"    for i in range(ntypes):\n";
        outfile<<"        name=snapshot.bonds.types[i]\n";
        outfile<<"        harmonic.bond_coeff.set(name,k=0.0,r0=1.529)\n";
        outfile<<"        bnlj.bond_coeff.set(name,epsilon=0.0,sigma=1.5,scale=0.0)\n\n\n";
    }

    if(harmDi&&opls)
    {
        outfile<<"    snapshot = system.take_snapshot(bonds=True)\n";
        outfile<<"    ntypes=len(snapshot.dihedrals.types)\n";
        outfile<<"    for i in range(ntypes):\n";
        outfile<<"        name=snapshot.dihedrals.types[i]\n";
        outfile<<"        harmonic_dihedral.set_coeff(name,k=0.0,d=1,n=0)\n";
        outfile<<"        opls_dihedral.set_coeff(name,k1=0.0, k2=0.0, k3=0.0, k4=0.0)\n\n\n";
    }


    outfile<<"    ######### Parameters ############\n\n";



    energy=4.184; //convert kj/mol
    //energy=1;
    dist=1;
    hoomdMass=1;


    for (itPotential=vecPa.begin();itPotential!=vecPa.end();itPotential++)
    {
        (*itPotential)->printHOOMD(outfile,energy,dist);
    }

    outfile<<"\n";
    for (itPotential=vecBn.begin();itPotential!=vecBn.end();itPotential++)
    {
        (*itPotential)->printHOOMD(outfile,energy,dist);
    }
    outfile<<"\n";

    for (itPotential=vecAn.begin();itPotential!=vecAn.end();itPotential++)
    {
        (*itPotential)->printHOOMD(outfile,energy,dist);

    }
    outfile<<"\n";

    for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
    {
        (*itPotential)->printHOOMD(outfile,energy,dist);

    }
    outfile<<"\n";

    for (itPotential=vecIm.begin();itPotential!=vecIm.end();itPotential++)
    {
        (*itPotential)->printHOOMD(outfile,energy,dist);


    }
    outfile<<"\n";

    //for (itPotential=vecDi.begin();itPotential!=vecDi.end();itPotential++)
    //{
    //    (*itPotential)->print(outfile);
    //}
    //outfile<<"\n";
    //for (itPotential=vecIm.begin();itPotential!=vecDi.end();itPotential++)
    //{
    //    (*itPotential)->print(outfile);
    //}
    //outfile<<"\n";

    hoomdDist=dist;

    hoomdEnergy=1;

    outfile<<"                      ##########Convertion factors######## \n";

    outfile<<"                      #       epsilon  = "<<hoomdEnergy<<" kj/mol"<<endl;
    outfile<<"                      #       distance = "<<hoomdDist<<" A"<<endl;
    outfile<<"                      #       mass = "<<hoomdMass<<" g/mol"<<endl;
    outfile<<"                      #       charg = "<<0.0268582<<" e"<<endl;
    outfile<<"                      #       k_B = "<<8.314472e-3<<" kJ/mol/K"<<endl;
    outfile<<"                      #       temp = "<<120.27904<<" K"<<endl;
    outfile<<"                      #       press = "<<16388.24603<<" atm"<<endl;
    outfile<<"                      #       time = "<<100<<" fs"<<endl;
    outfile<<"                      ####################################\n\n";

    //outfile<<"Th=T/120.27904\n";
    //outfile<<"Ph=P/16388.24603\n";
    //outfile<<"th=t/100\n";
    //outfile<<"Trh=Tr*th\n";
    //outfile<<"Prh=Pr*th\n";


    outfile<<"class groups:\n";
    outfile<<"    def __init__(self):\n";
    outfile<<"        self.all=group.all()\n";
    for (itGroup=vecGroup.begin();itGroup!=vecGroup.end();itGroup++)
    {
        (*itGroup)->printHOOMD(outfile);
    }


    outfile.close();

    cout<<"Force Field written:: Look in "<<filename<<endl;

}

bool cffStream::vecHasStyle(vector<potential*> p,string s)
{
    string style;

    vector<potential*>::iterator itP;
    for (itP=p.begin();itP!=p.end();itP++)
    {
        style=(*itP)->getStyleName();

        if (style.substr(0,s.size())==s)
        {
            return true;
        }
    }

    return false;

}



