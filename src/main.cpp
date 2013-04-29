#include <string>
#include <QDir>
#include <QDebug>
#include "routefinder.h"
#include "grip.h"
#include "geometry.h"
#include "utils.h"
#include "pathproblem.h"
#include "climberstate.h"
#include "searcher.h"

#define TEST_MODE 0

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
        *inPath = "../img/input/test1.JPG";
}

int main(int argc, char* argv[])
{
#if TEST_MODE
    Geometry::testNormals();
#else
    std::string inPath, outPath;
    processArgs(argc, argv, &inPath, &outPath);

    cv::Mat img;
    bool b = jug::loadImage(inPath, img);
    if (!b)
        qFatal("Aborting");

    RouteFinder rf;
    Route route = rf.find(&img);
    cv::destroyAllWindows();

    PathProblem<ClimberState> p;
    Searcher<ClimberState> s;
    s.bfs(&p);

    route.analyzeGrips();
    route.visualize();
    return 0;
#endif
}
