#include <QCoreApplication>
#include "routefinder.h"

int main (int argc, char **argv)
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    RouteFinder rf;
    rf.find("../img/test_red.JPG");
    rf.showRoute();
    return 0;
}
