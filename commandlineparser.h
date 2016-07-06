#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;


class argument {
public:
    argument(string sz1,string szVal){szCMD=sz1;nValues=0;vecValues.push_back(szVal);}
    string szCMD;
    int nValues;
    vector<string> vecValues;
};
class commandLineParser
{
public:
    commandLineParser(int iargc, char * iargv[]);
    commandLineParser(){;}
    void search();
    void addArguments(int iargc, char * iargv[]);
    void addSearchString(string s);
    bool has(const string & s);
    int getInt(const string &s, int i=0 );
    int getNValues(const string &s);
    double  getDouble(const string &s, int i =0);
    string  getString(const string &s, int i =0);
    void printArguments();

private:
   int argc;
   char ** argv;
   vector<string> vecSearchString;
   vector<string>::iterator itSearch;
   vector<argument> vecOptions;
   vector<argument>::iterator itOpt;
};

#endif // COMMANDLINEPARSER_H
