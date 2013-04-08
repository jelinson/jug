#include <string>
#include "routefinder.h"

void processArgs(int argc, char* argv[], std::string* inPath, std::string* outPath)
{
    if (argc > 1) {
        *inPath = argv[1];
        if (argc > 2)
            *outPath = argv[2];
        else
            *outPath = "../img/output";
    }
    else
        *inPath = "../img/input/test4.JPG";
}

int main(int argc, char* argv[])
{
    std::string inPath, outPath;
    processArgs(argc, argv, &inPath, &outPath);

    RouteFinder rf;
    rf.find(inPath, true);
    return 0;
}
