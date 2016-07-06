#include "commandlineparser.h"

commandLineParser::commandLineParser(int iargc, char *iargv[]):argc(iargc),argv(iargv)
{

}

void commandLineParser::search()
{
    for (int i =0;i<argc;i++)
    {
        string cmd = argv[i];

        //cout<<cmd<<endl;


        if(cmd.at(0)=='-')
        {

            if(i+1<argc)
            {
                string cmd2 = argv[i+1];

                if(cmd2.at(0)!='-')
                {

                    vecOptions.push_back(argument(argv[i],argv[i+1]));
                    i++;
                }else
                {

                    vecOptions.push_back(argument(argv[i]," "));

                }
            }else
            {


                vecOptions.push_back(argument(argv[i]," "));


            }


        }else
        {
            std::size_t found;
            for (itSearch=vecSearchString.begin();itSearch!=vecSearchString.end();itSearch++)
            {
                found = cmd.find((*itSearch));


                if (found!=std::string::npos)
                {
                    //cout <<"found "<<*itSearch<<" "<<cmd<<endl;


                    vecOptions.push_back(argument(*itSearch,argv[i]));
                    break;

                }

            }

            if (found==std::string::npos)
            {
                //cout<<cmd<<" end\n";
                if(!vecOptions.empty())
                {
                    (vecOptions.end()-1)->vecValues.push_back(cmd);
                }
            }

        }

    }

}

void commandLineParser::addArguments(int iargc, char *iargv[])
{
    argc=iargc;
    argv=iargv;

}

void commandLineParser::addSearchString(string s)
{
    vecSearchString.push_back(s);

}

bool commandLineParser::has(const string &s)
{
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        if (itOpt->szCMD ==s)
        {
            return true;
        }
    }

    return false;
}

int commandLineParser::getInt(const string &s, int i)
{
    double value;
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        if (itOpt->szCMD ==s)
        {
            value= atoi(itOpt->vecValues.at(0).c_str());
        }
    }

    return value;

}

int commandLineParser::getNValues(const string &s)
{
    int value=0;
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        if (itOpt->szCMD ==s)
        {
            value++;
        }
    }

    return value;
}

double commandLineParser::getDouble(const string &s,int i)
{
    double value;
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        if (itOpt->szCMD ==s)
        {
            value= atof(itOpt->vecValues.at(i).c_str());
        }
    }

    return value;

}

string commandLineParser::getString(const string &s, int i)
{
    string value;
    int count=0;
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        if (itOpt->szCMD ==s)
        {
            if (count==i)
            {
                value= itOpt->vecValues.at(0);
                return value;
            }else count++;
        }
    }

    return value;

}

void commandLineParser::printArguments()
{
    for (itOpt=vecOptions.begin();itOpt!=vecOptions.end();itOpt++)
    {
        cout<<itOpt->szCMD<< " ";
        for(int i=0;i<itOpt->vecValues.size();i++)
        {
           cout<<itOpt->vecValues.at(i)<<" ";
        }
        cout<<endl;
    }


}
