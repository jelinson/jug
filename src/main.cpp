#include <string>
#include <QDir>
#include <QDebug>
#include "routefinder.h"
#include "grip.h"
#include "geometry.h"
#include "utils.h"
#include "pathproblem.h"
#include "climber.h"
#include "climberspecs.h"
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
        *inPath = "../img/input/test4.JPG";
}

int main(int argc, char* argv[])
{
#if TEST_MODE
    Geometry::testNormals();
#else
    std::string inPath, outPath;
    processArgs(argc, argv, &inPath, &outPath);

    if (DEBUG_LEVEL != QUIET)
        qDebug() << "Loading image" << inPath.c_str();

    cv::Mat img;
    bool b = jug::loadImage(inPath, img);
    if (!b)
        qFatal("Aborting");

    if (DEBUG_LEVEL != QUIET)
        qDebug() << "Analyzing route";

    RouteFinder rf;
    Route route = rf.find(&img);
    route.analyzeGrips();
    //route.visualize();
    jug::clearImages();

    Physics* engine = new Physics;
    ClimberSpecs spec;
    Climber c(engine, spec);

    if (DEBUG_LEVEL != QUIET)
        qDebug() << "Searching for a path";

    Path solution = c.climb(route);
    return 0;
#endif
}
