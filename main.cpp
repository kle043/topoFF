#include <iostream>
#include "FF/readff.h"
#include "FF/readinput.h"
#include "FF/csortpotential.h"
#include "FF/cffstream.h"
#include "topo/csystem.h"
#include "topo/cdatareader.h"
#include "topo/cdatawriter.h"
#include "commandlineparser.h"
#include "topo/cpdbreader.h"
#include "topo/csystemsorter.h"
#include "topo/cxmlwriter.h"
int main(int argc,char *argv[])
{

    /* Pure files must be the last to be loaded
     * Added pure functionallity .pure. files are not included
     * Mixing updated mixGeo perform geometric mixing LJ if style LJAB vs LJ LJAB is default.
     *
     * -opls keyword added, (adds bond between outer atoms in dihederals
     * -body writes out bodies
     *
     * hoomd is now default, for lammps use -lmp
     *
     * Added read several pdb files
     *
     * Added mixing for group names, .i.e teg teg and so on.
     *
     * FIXES:
     * Need fail proof pdb reader,almost done!
     * Need fix for dihederal not found if wrapped coords
     *
     */


    commandLineParser parse;
    string inFile, dataFile,pdbFile;

    parse.addSearchString(".in");
    parse.addSearchString(".pdb");
    parse.addSearchString("data.");


    parse.addArguments(argc,argv);

    parse.search();

    parse.printArguments();

    if (parse.has(".in"))
    {

        inFile=parse.getString(".in");

    }else
    {
        cout <<"No inputFile! "<<endl;
        return 0;
    }


    try
    {


        readInput inputData(inFile);
        readFF ffFiles(inputData.getFiles());
        csystem sys;

        if (parse.has("data."))
        {
            dataFile=parse.getString("data.");

            cdataReader readData(&sys,dataFile,&inputData);
            cSystemSorter sorter(&sys);


            sorter.findMolecules();

        }

        bool opls=false;

        if (parse.has("-opls"))
        {
            opls=true;

        }

        bool hoomd=true;

        if (parse.has("-lmp"))
        {
            hoomd=false;
        }

        cSortPotential potential;
        potential.sortData(inputData,ffFiles,opls,hoomd);



        if (parse.has(".pdb"))
        {
            cout<<"Number of pdb files "<<parse.getNValues(".pdb")<<endl;

            for (int i =0;i <parse.getNValues(".pdb");i++)
            {

                pdbFile=parse.getString(".pdb",i);

                cpdbReader readPdb(&sys,pdbFile);
            }


            cSystemSorter sorter(&sys);

            sorter.sortOnDistance(&potential);
            sorter.findMolecules();
            sorter.updateAngles();




        }

        if(parse.has(".pdb") ||  parse.has("data."))
        {

            sys.printSummary();

            sys.setParameters(&potential);

            if(!potential.getVecRmBond().empty() ||!potential.getVecRmAngle().empty() ||!potential.getVecRmImproper().empty() )
            {

                cout <<"\nStarting remove request! \n\n";

                sys.removeBonds(potential.getVecRmBond());
                sys.removeAngle(potential.getVecRmAngle());
                sys.removeImproper(potential.getVecRmImproper());
                sys.printSummary();


                potential.removePot();
                sys.setParameters(&potential);
            }



            vector<pair<int,int>> vecSwapImDi=potential.getVecSwapImDi();

            if(!vecSwapImDi.empty())
            {
                cout <<"\nStarting moving Impropers into diherals! \n\n";

                sys.swapImproperDihedral(vecSwapImDi);
                sys.setParameters(&potential);

            }

            //Must be last, calling setParameters after adding addOPLS() can add bonds that should not be there

            if(opls)
            {
                sys.addOPLS();
                sys.update();
            }

            sys.printSummary();





        }

        //Potential is set up, now write the wanted files

        cffStream ffStream(potential);
        size_t found = inFile.find_last_of(".");

        string outFile=inFile.substr(0,found);

        if (parse.has("-latex"))
        {
           ffStream.writeLatex(outFile);



        } else if(parse.has("-lmp"))
        {

            ffStream.writeLammps(outFile);

            cdatawriter dataWriter;

            dataWriter.write(&sys,outFile);


        }else
        {

            cxmlwriter xml;

            ffStream.writeHoomd(outFile);




            if (parse.has("-body"))
            {
                 xml.write(&sys,outFile,true);
            }else
            {
                 xml.write(&sys,outFile,false);
            }


        }

    }catch(exception & e)
    {
        std::cerr << "Error : " << e.what() << '\n';
    }



    return 0;
}

