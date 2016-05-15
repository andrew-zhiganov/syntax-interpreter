#include <string>

using namespace std;

string Message(int exitCode){
    switch(exitCode){
        case 0: {return "The program is correct";}
        case 1: {return "var expected";}
        case 2: {return "identifier expected";}
        case 3: {return "duplicate declaration";}
        case 4: {return "expected max length of identifier to be 11";}
        case 5: {return "wrong identifier";}
        case 6: {return ", or : expected";}
        case 7: {return "integer expected";}
        case 8: {return "; expected";}
        case 9: {return "begin expected";}
        case 10: {return "unknown identifier";}
        case 11: {return "= expected";}
        case 12: {return "illegal symbol";}
        case 13: {return "missing ( or )";}
        case 14: {return "end expected";}
        case 15: {return "illegal expression";}
        case 16: {return "after end";}
    }
}