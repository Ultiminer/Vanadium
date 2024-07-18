#include "config.h"
#include "compiler.h"



int main(int argc, char**argv)
{
    assert(argc==2, "compiler takes only one argument");
    std::string pathArg=argv[1];
    assert(pathArg.find(".vnd")!=std::string::npos,"compiler only takes .vnd files");
    parse(pathArg.c_str());
    

    return 0;
}