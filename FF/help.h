#ifndef HELP_H
#define HELP_H
#include <string>
using namespace std;
class help
{
public:
    help(string n) {message="HELP CALLED: "+n;}
    const string & what(){return message;}

private :
    string message;

};

#endif // HELP_H
