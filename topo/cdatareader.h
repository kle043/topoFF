#ifndef CDATAREADER_H
#define CDATAREADER_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdlib.h>
#include "csystem.h"
#include "FF/readinput.h"
using namespace std;

class cdataReader
{
public:
    cdataReader(csystem * sys,string file,readInput * inp);

private:
    vector<double> vecMasses;
    vector<string> vecNames;



};

#endif // CDATAREADER_H
